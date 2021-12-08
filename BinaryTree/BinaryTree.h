#ifndef ANTISOUND_BYNARYTREE_H
#define ANTISOUND_BYNARYTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    void* data;

    struct Node* parent;
    struct Node* left;
    struct Node* right;

}binaryTree_t;

/*
 * initializes struct of Node
 * returns pointer to binaryTree_t
 */
binaryTree_t* binaryTree_initializeNode();

/*
 * creats newNode with data
 * returns pointer to binaryTree_t
 */
binaryTree_t* binaryTree_newNode(void* data);

/*
 * adds newNode to binary tree
 */
bool binaryTree_addNewNode(binaryTree_t* node, void* data);

/*
 * finds request data by node
 * returns pointer to node
 */
binaryTree_t* binaryTree_getNode(binaryTree_t* node, int id);

/*
 * returns request data by node
 */
void* binaryTree_getData(binaryTree_t* node, int id);

/*
 * returns height of binaryTree
 */
int binaryTree_height(binaryTree_t* node);

/*
 * checks balance of node
 * returns true in case if node balanced, otherwise returns false
 */
bool binaryTree_isBalanced(binaryTree_t* node);

/*
 * definds new node and turns subnodes left to right
 * returns new node
 */
binaryTree_t* binaryTree_turnLeftToRight(binaryTree_t* root);

/*
 * definds new node and turns subnodes right to left
 * returns new node
 */
binaryTree_t* binaryTree_turnRightToLeft(binaryTree_t* root);

/*
 * finds imbalanced nodes and balances
 * return true in case balancing completed
 */
bool binaryTree_balancingSubNodes(binaryTree_t* node);

/*
 * balances node
 * return balansed node
 */
binaryTree_t* balancingNode(binaryTree_t* node);


/*
 * remove node
 * return true in case if node deleted, otherwise returns false
 */
bool binaryTree_removeNode(binaryTree_t* root, int id);

/*
 * returns the closest possible node by value on the left side of main root
 */
binaryTree_t* binaryTree_getCloseMaxRightValue(binaryTree_t* node);

/*
 * returns the closest possible node by value on the right side of main root
 */
binaryTree_t* binaryTree_getCloseMaxLeftValue(binaryTree_t* node);

/*
 * returns new node
 */
binaryTree_t* binaryTree_getNewNode(binaryTree_t* node);

int binaryTree_max(int a, int b);

/*
 * removes left sub-node of parent of node
 * returns true in case success, otherwise false
 */
bool binaryTree_removeParentLeftNode(binaryTree_t* node);

/*
 * removes right sub-node of parent of node
 * returns true in case success, otherwise false
 */
bool binaryTree_removeParentRightNode(binaryTree_t* node);

/*
 * removes root node
 * returns true in case success, otherwise false
 */
bool binaryTree_removeRoot(binaryTree_t* node);

/*
 * establishes new connections between the parents of a new node right
 */
binaryTree_t* binaryTree_getNodeRightSide(binaryTree_t* node);

/*
 * establishes new connections between the parents of a new node right
 */
binaryTree_t* binaryTree_getNodeLeftSide(binaryTree_t* node);


binaryTree_t* binaryTree_getResponse(binaryTree_t* responses, char* searchKey);

//=============================================================================================================

bool binaryTree_testInitializeNode();

bool bynaryTree_testGetNode(binaryTree_t* node, int id);

#endif // ANTISOUND_BYNARYTREE_H