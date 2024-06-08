#ifndef BST_H
#define BST_H

enum BSTOrder { PREORDER, INORDER, POSTORDER };

typedef struct BSTNode {
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* insert( BSTNode*, BSTNode* );
BSTNode* create( int );
BSTNode* find( BSTNode*, int );
BSTNode* removeNode( BSTNode*, int );
BSTNode* deleteBST( BSTNode* );
void preorder( BSTNode* );
void inorder( BSTNode* );
void postorder( BSTNode* );
void traverseBST(BSTNode* , enum BSTOrder);

#endif