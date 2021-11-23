#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../Item/Item.h"
#include "../BinaryTree/BinaryTree.h"

binaryTree_t* binaryTree_initializeNode()
{
    binaryTree_t* node = malloc(sizeof(binaryTree_t));

    node->data  = NULL;

    node->parent = NULL;

    node->left = NULL;

    node->right = NULL;

    return node;
}

binaryTree_t* binaryTree_newNode(void* data)
{
    binaryTree_t* newNode = binaryTree_initializeNode();

    newNode->data = data;

    return newNode;
}

bool binaryTree_addNewNode(binaryTree_t* node, void* data)
{
    item_t* newData = data;

    binaryTree_t* getedNode = binaryTree_getNode(node, newData->id);
    
    item_t* getedItem = getedNode->data;

    if(getedNode == node && getedNode->data == NULL)
    {
        getedNode->data = data;
        
        return;
    }

    if(newData->id < getedItem->id)
    {
        getedNode->left = binaryTree_newNode(data);

        getedNode->left->parent = getedNode;
    }

    if(newData->id > getedItem->id)
    {
        getedNode->right = binaryTree_newNode(data);

        getedNode->right->parent = getedNode;
    }

    return true;
}

binaryTree_t* binaryTree_getNode(binaryTree_t* node, int id)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->data == NULL)
    {
        return node;
    }

    item_t* item = node->data;

    if(item->id == id)
    {
        return node;
    }

    if(id < item->id && node->left != NULL)
    {
        node = binaryTree_getNode(node->left, id);
    }

    if(id > item->id && node->right != NULL)
    {
        node = binaryTree_getNode(node->right, id);
    }

    return node;
}

void* binaryTree_getData(binaryTree_t* node, int id)
{
    binaryTree_t* getedNode = binaryTree_getNode(node, id);

    return getedNode->data;
}

int binaryTree_height(binaryTree_t* node)
{
    if(node == NULL)
    {
        return -1;
    }

    return 1 + binaryTree_max(binaryTree_height(node->left), binaryTree_height(node->right));
}

bool binaryTree_isBalanced(binaryTree_t* node)
{
    if(node == NULL)
    {
        return true;
    }

    if(abs((binaryTree_height(node->left)) - (binaryTree_height(node->right))) <= 1 && binaryTree_isBalanced(node->left) && binaryTree_isBalanced(node->right))
    {
        return true;
    }
    
    return false;
}

bool binaryTree_balancingSubNodes(binaryTree_t* node)
{
    if(node == NULL)
    {
        return true;
    }
      
    binaryTree_balancingSubNodes(node->left);

    binaryTree_balancingSubNodes(node->right);
   
    node->left = balancingNode(node->left);

    node->right = balancingNode(node->right);

    return true;
}

binaryTree_t* binaryTree_turnRightToLeft(binaryTree_t* root)
{
    binaryTree_t* oldRoot = root;

    binaryTree_t* newRoot = oldRoot->right;

    if(oldRoot->parent != NULL)
    {
        newRoot->parent = oldRoot->parent;
    }
    else
    {
        newRoot->parent = NULL;
    }

    oldRoot->parent = newRoot;

    oldRoot->right = newRoot->left;

    newRoot->left = oldRoot;

    return newRoot;
}

binaryTree_t* binaryTree_turnLeftToRight(binaryTree_t* root)
{
    binaryTree_t* oldRoot = root;

    binaryTree_t* newRoot = oldRoot->left;
    
    if(oldRoot->parent != NULL)
    {
        newRoot->parent = oldRoot->parent;
    }
    else
    {
        newRoot->parent = NULL;
    }

    oldRoot->parent = newRoot;

    oldRoot->left = newRoot->right;

    newRoot->right = oldRoot;

    return newRoot;
}

binaryTree_t* balancingNode(binaryTree_t* node)
{
    if(binaryTree_isBalanced(node) == false)
    {
        int rightHeight = binaryTree_height(node->right);

        int leftHeight = binaryTree_height(node->left);

        int subLeftHeight = binaryTree_height(node->right->left);

        if(rightHeight > leftHeight && subLeftHeight == -1)
        {
            node = binaryTree_turnRightToLeft(node);
        }

        if(rightHeight > leftHeight && subLeftHeight != -1)
        {
            node->right = binaryTree_turnLeftToRight(node->right);

            node = binaryTree_turnRightToLeft(node);

            binaryTree_balancingSubNodes(node);
        }

        int subRightHeight = binaryTree_height(node->left->right);

        if(leftHeight > rightHeight && subRightHeight == -1)
        {
            node = binaryTree_turnLeftToRight(node);
        }

        if(leftHeight > rightHeight && subRightHeight != -1)
        {
            node->right = binaryTree_turnRightToLeft(node->right);

            node = binaryTree_turnLeftToRight(node);

            binaryTree_balancingSubNodes(node);
        }
    }
    
    return node;
}

bool binaryTree_removeNode(binaryTree_t* node, int id)
{
    binaryTree_t* removeNode = binaryTree_getNode(node, id);

    if(removeNode->parent == NULL)
    {
        return antiSound_binaryTree_removeRoot(removeNode);
    }

    if(removeNode->parent->left == removeNode)
    {
        return binaryTree_removeParentLeftNode(removeNode);
    }

    if(removeNode->parent->right == removeNode)
    {
        return antiSound_binaryTree_removeParentRightNode(removeNode);
    }

    return false;
}

binaryTree_t* binaryTree_getCloseMaxRightValue(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->right != NULL)
    {
        node = binaryTree_getCloseMaxRightValue(node->right);
    }

    return node;
}

binaryTree_t* binaryTree_getCloseMaxLeftValue(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(node->left != NULL)
    {
       node = binaryTree_getCloseMaxLeftValue(node->left);
    }

    return node;
}

binaryTree_t* binaryTree_getNewNode(binaryTree_t* node)
{
    if(node == NULL)
    {
        return NULL;
    }

    binaryTree_t* newNode = NULL;

    if(node->parent == NULL)
    {
        if(node->right != NULL)
        {
            newNode = binaryTree_getNodeRightSide(node);
        }
        else
        {
            newNode = binaryTree_getNodeLeftSide(node);
        }

        return newNode;
    }

    if(node->parent->right == node)
    {
        newNode = binaryTree_getNodeRightSide(node);
    }

    if(node->parent->left == node)
    {
        newNode = binaryTree_getNodeLeftSide(node);
    }

    newNode->parent = node->parent;

    return newNode;
}

int binaryTree_max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
   
    return b;
}

bool binaryTree_removeParentLeftNode(binaryTree_t* node)
{
    int leftHeight = binaryTree_height(node->left);

    int rightHeight = binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->parent->left = NULL;

        free(node);

        return true;
    }

    if(leftHeight != -1 && rightHeight != -1)
    {
        node->parent->left = binaryTree_getNewNode(node);
        
        free(node);

        return true;
    }
    
    if(leftHeight != -1 && rightHeight == -1)
    {   
        node->parent->left = node->left;

        free(node);
        
        return true;
    }

    if(leftHeight == -1 && rightHeight != -1)
    {   
        node->parent->left = node->right;

        free(node);

        return true;
    }

    return false;
}

bool antiSound_binaryTree_removeParentRightNode(binaryTree_t* node)
{
    int leftHeight = binaryTree_height(node->left);

    int rightHeight = binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->parent->right = NULL;

        free(node);

        return true;
    }

    if(leftHeight != -1 && rightHeight != -1)
    {
        node->parent->right = binaryTree_getNewNode(node);

        free(node);

        return true;
    }

    if(rightHeight != -1 && leftHeight == -1)
    {   
        node->parent->right = node->right;

        free(node);

        return true;
    }

    if(rightHeight == -1 && leftHeight != -1)
    {   
        node->parent->right = node->left;

        free(node);

        return true;
    }

    return false; 
}

bool antiSound_binaryTree_removeRoot(binaryTree_t* node)
{
    int leftHeight = binaryTree_height(node->left);

    int rightHeight = binaryTree_height(node->right);

    if(leftHeight == -1 && rightHeight == -1)
    {
        node->data = NULL;

        free(node);

        return true;
    }

    binaryTree_t* newNode = binaryTree_getNewNode(node);

    node->data = newNode->data;
    
    free(newNode);

    return true;
}

binaryTree_t* binaryTree_getNodeRightSide(binaryTree_t* node)
{
    binaryTree_t* newNode = binaryTree_getCloseMaxLeftValue(node->right);

    if(newNode->right != NULL)
    {
        newNode->parent->left = newNode->right; 
    }
    else
    {
        newNode->parent->left = NULL;
    }

    return newNode;
}

binaryTree_t* binaryTree_getNodeLeftSide(binaryTree_t* node)
{
    binaryTree_t* newNode = binaryTree_getCloseMaxRightValue(node->left);

    if(newNode->left != NULL)
    {
        newNode->parent->right = newNode->left;
    }
    else
    {
        newNode->parent->right = NULL;
    }

    return newNode;
}
