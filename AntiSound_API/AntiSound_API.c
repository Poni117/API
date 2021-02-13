#include "AntiSound_API.h"
#include "../AntiSound_HTTP/AntiSound_HTTP.h"
#include "../AntiSound_Handler/AntiSound_Handler.h"
#include "../AntiSound_BinaryTree/AntiSound_BinaryTree.h"
#include "../AntiSound_Item/AntiSound_Item.h"
#include "../AntiSound_Constructor/AntiSound_Constructor.h"
#include "../AntiSound_FIFO/AntiSound_FIFO.h"
#include "../AntiSound_Threads/AntiSound_Threads.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

bool antiSound_api_newServer()
{
    int serverSocket = antiSound_api_copySocket();

    binaryTree_t* root = antiSound_binaryTree_initializeNode();

    binaryTree_t* messages = antiSound_binaryTree_initializeNode();

    fifo_t* fifo = antiSound_fifo_initializeFifo();

    pthread_t thread;
    pthread_create(&thread, NULL, antiSound_threads_checkFifo, fifo);
    pthread_detach(thread);
    
    while(true)
    {
        int clientSocket = accept(serverSocket, NULL, NULL);

        char buffer[1000] = "\0";
        recv(clientSocket, buffer, sizeof(buffer), 0);

        datas_t* datas = antiSound_http_initializeDatas();
        datas->request = antiSound_http_parseRuqest(antiSound_api_removeCorrector(buffer));

        datas->root = root;
        datas->response = antiSound_handler_initializeResponse();

        if(strcmp(datas->request->path, "tasks") == 0)
        {
            char* key = antiSound_constructor_generateKey();

            antiSound_api_sendKey(clientSocket, key);

            printf("antiSound_fifo_push[%d]\n", antiSound_fifo_push(fifo, datas));

            char* message = antiSound_handler_collectResponse(datas->response);
    
            antiSound_api_addtask(messages, message, key);

            if(antiSound_binaryTree_isBalanced(root) == false)
            {
                antiSound_binaryTree_balancingSubNodes(root);
                root = balancingNode(root);
            }

            if(antiSound_binaryTree_isBalanced(messages) == false)
            {
                antiSound_binaryTree_balancingSubNodes(messages);
                messages = balancingNode(messages);
            }
        }

        if(strcmp(datas->request->path, "message") == 0)
        {
            antiSound_handler_messageHandler(clientSocket, datas->request, messages);
        }

        close(clientSocket);
    }

    return true;
}

char* antiSound_api_removeCorrector(char* requestData)
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

int antiSound_api_copySocket()
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

void* antiSound_api_processRequest(request_t* request, response_t* response, binaryTree_t* root)
{

    antiSound_handler_tasksHandler(request, response, root);

 

    return NULL;
}

bool antiSound_api_sendKey(int clientSocket, char* key)
{
    datas_t* datas = antiSound_http_initializeDatas();
    datas->response  = antiSound_handler_initializeResponse();
    datas->response->status = "HTTP/1.1 200 OK\n";

    datas->response->body = antiSound_constructor_addLayout(antiSound_constructor_decodeItemToJson("id", key), "{%s}");

    char* message = antiSound_handler_collectResponse(datas->response);

    send(clientSocket, message, strlen(message), 0);

    free(datas->response->body);
    free(datas->response);
    free(datas);

    return true;
}

void antiSound_api_addtask(binaryTree_t* responses, char* message, char* key)
{
    messege_t* messages = antiSound_http_initializeMesseges();
    messages->key = atoi(key);
    messages->message = message;

    antiSound_binaryTree_addNewNode(responses, messages);
}

void* antiSound_handler_messageHandler(int clientSocket, request_t* request, binaryTree_t* messages)
{
    body_t* body = antiSound_http_getBodyParamter(request, "id");

    binaryTree_t* node = antiSound_binaryTree_getResponse(messages, body->name);
    messege_t* response = node->data;

    char* message = response->message;
    
    send(clientSocket, message, strlen(message), 0);

    antiSound_binaryTree_removeNode(node, atoi(body->name));

    return NULL;
}

