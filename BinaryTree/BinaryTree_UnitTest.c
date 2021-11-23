 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Item/Item.h"
#include "../BinaryTree/BinaryTree.h"

bool antiSound_binaryTree_testInitializeNode()
{
    bool isNodeInitialzed = false;

    bool isDataInitialized = false;

    bool isParentInitialized = false;

    bool isLeftInitialized = false;

    bool isRightInitialized = false;

    binaryTree_t* inializedNode = binaryTree_initializeNode();

    if(inializedNode->data == NULL)
    {
        isDataInitialized = true;
    }

    if(inializedNode->parent == NULL)
    {
        isParentInitialized = true;
    }

    if(inializedNode->left == NULL)
    {
        isLeftInitialized = true;
    }

    if(inializedNode->right == NULL)
    {
        isRightInitialized = true;
    }

    if(isDataInitialized == true || isParentInitialized == true || isLeftInitialized == true || isRightInitialized == true)
    {
        isNodeInitialzed = true;
    }

    if (isNodeInitialzed == false)
    {
        printf("< antiSound_binaryTree_testInitializeNode >\n");

        printf("isNodeInitialzed[%d]\n", isNodeInitialzed);

        printf("-------------------------\n");
    }
}

bool antiSound_bynaryTree_testGetNode(binaryTree_t* node, int id)
{
    bool isNodeExist = false;

    binaryTree_t* getedNode = antiSound_bynaryTree_getNode(node, id);

    if(getedNode != NULL)
    {
        isNodeExist = true;
    }

    if(isNodeExist == false)
    {
        printf("< antiSound_bynaryTree_testGetNode >\n");

        printf("isNodeExist[%d]\n", isNodeExist);

        printf("-------------------------\n");
    }
}
