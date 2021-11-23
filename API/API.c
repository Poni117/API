#include "API.h"
#include "../HTTP/HTTP.h"
#include "../Handler/Handler.h"
#include "../BinaryTree/BinaryTree.h"
#include "../Item/Item.h"
#include "../Constructor/Constructor.h"
#include "../FIFO/FIFO.h"
#include "../Threads/Threads.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

bool api_newServer()
{
    int serverSocket = api_copySocket();

    binaryTree_t* root = binaryTree_initializeNode();

    binaryTree_t* messages = binaryTree_initializeNode();

    fifo_t* fifo = fifo_initializeFifo();

    pthread_t thread;

    pthread_create(&thread, NULL, threads_checkFifo, fifo);

    pthread_detach(thread);
    
    while(true)
    {
        int clientSocket = accept(serverSocket, NULL, NULL);

        char buffer[1000] = "\0";

        recv(clientSocket, buffer, sizeof(buffer), 0);

        datas_t* datas = http_initializeDatas();

        datas->request = http_parseRuqest(api_removeCorrector(buffer));

        datas->root = root;

        datas->response = handler_initializeResponse();

        if(strcmp(datas->request->path, "tasks") == 0)
        {
            char* key = constructor_generateKey();

            api_sendKey(clientSocket, key);

            printf("antiSound_fifo_push[%d]\n", fifo_push(fifo, datas));

            char* message = handler_collectResponse(datas->response);
    
            api_addtask(messages, message, key);

            if(binaryTree_isBalanced(root) == false)
            {
                binaryTree_balancingSubNodes(root);

                root = balancingNode(root);
            }

            if(binaryTree_isBalanced(messages) == false)
            {
                binaryTree_balancingSubNodes(messages);

                messages = balancingNode(messages);
            }
        }

        if(strcmp(datas->request->path, "message") == 0)
        {
            handler_messageHandler(clientSocket, datas->request, messages);
        }

        close(clientSocket);
    }

    return true;
}

char* api_removeCorrector(char* requestData)
{
    int i = 0;

    int j = 0;
    
    char buffer[1000] = "\0";

    while (i < strlen(requestData))
    {
        if (requestData[i] != '\r')
        {
            buffer[j] = requestData[i];
            j++;
        }
        i++;
    }
    
    char* alteratedRequest = calloc(strlen(buffer) + 10, sizeof(char));

    strncpy(alteratedRequest, buffer, strlen(buffer));

    return alteratedRequest;
}

int api_copySocket()
{
    bool isServerExist = false;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in setConnect;

    setConnect.sin_family = AF_INET;

    setConnect.sin_port = ntohs(8090);

    setConnect.sin_addr.s_addr = inet_addr("127.0.0.1");

    int bindStatus = bind(serverSocket, (const struct sockaddr *) &setConnect, sizeof(setConnect));

    if(bindStatus != -1)
    {
        isServerExist = true;
    }
    else
    {
        return bindStatus;
    }
    
    printf("isServerExist[%d]\n", isServerExist);

    listen(serverSocket, 1);

    return serverSocket;
}

void* api_processRequest(request_t* request, response_t* response, binaryTree_t* root)
{
    handler_tasksHandler(request, response, root);

    return NULL;
}

bool api_sendKey(int clientSocket, char* key)
{
    datas_t* datas = http_initializeDatas();

    datas->response  = handler_initializeResponse();

    datas->response->status = "HTTP/1.1 200 OK\n";

    datas->response->body = constructor_addLayout(constructor_decodeItemToJson("id", key), "{%s}");

    char* message = handler_collectResponse(datas->response);

    send(clientSocket, message, strlen(message), 0);

    free(datas->response->body);

    free(datas->response);

    free(datas);

    return true;
}

void api_addtask(binaryTree_t* responses, char* message, char* key)
{
    messege_t* messages = http_initializeMesseges();

    messages->key = atoi(key);

    messages->message = message;

    binaryTree_addNewNode(responses, messages);
}

void* handler_messageHandler(int clientSocket, request_t* request, binaryTree_t* messages)
{
    body_t* body = http_getBodyParamter(request, "id");

    binaryTree_t* node = binaryTree_getResponse(messages, body->name);

    messege_t* response = node->data;

    char* message = response->message;
    
    send(clientSocket, message, strlen(message), 0);

    binaryTree_removeNode(node, atoi(body->name));

    return NULL;
}