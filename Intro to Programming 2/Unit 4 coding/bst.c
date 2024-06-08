#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

BSTNode* create( int v ) {
   BSTNode* n = (BSTNode*) malloc( sizeof( BSTNode ) );
   n->value = v;
   n->left = NULL;
   n->right = NULL;
   return n;
}

BSTNode* insert( BSTNode* r, BSTNode* n ) {
   if( r == NULL ) {
      return n;
   }
   
   if( n->value <= r->value ) {
      r->left = insert( r->left, n );
   }
   else {
      r->right = insert( r->right, n );
   }
   return r;
}

void preorder( BSTNode* r ) {
   if( r == NULL ) {
      return;
   }
   
   printf( "%d\t", r->value );
   preorder( r->left );
   preorder( r->right );
}

void inorder( BSTNode* r ) {
   if(r == NULL) {
      return;
   }

   inorder( r->left );
   printf( "%d\t", r->value );
   inorder( r->right );
}

void postorder( BSTNode* r ) {
   if( r == NULL ) {
      return;
   }
  
   postorder( r->left );
   postorder( r->right );
  
   printf( "%d\t", r->value );
}

BSTNode* deleteBST( BSTNode* r ) {
   if( r == NULL ) {
      return NULL;
   }

   deleteBST( r->left );
   deleteBST( r->right );
   free( r );
   return NULL;
}

BSTNode* find( BSTNode* root, int key ) {
   if( root == NULL ) {
      return NULL;
   }
   /* if key value was found */
   if( root->value == key ) {
      return root;
   }

   if( root->value > key ) {
      return find( root->left, key );
   }
   else {
      return find( root->right, key );
   }
}

BSTNode* removeNode( BSTNode* root, int key ) {
   if( root == NULL ) {
      return NULL;
   }

   if( root->value > key ) {
      root->left = removeNode( root->left, key );
   }
   else if( root->value < key ) {
      root->right = removeNode( root->right, key );
   }
   else if( root->value == key ) {
      if( root->left == NULL && root->right == NULL ) {
         free( root );
      }
      return NULL;
   }

   if( root->left == NULL ) {
      BSTNode *right = root->right;
      free( root );
      return right;
   }

   if( root->right == NULL ) {
      BSTNode *left = root->left;
      free( root );
      return left;
   }

   BSTNode* t = root->right;
   for( t = root->right; t != NULL && t->left != NULL; t = t->left ) {
      root->value = t->value;
      root->right = removeNode( root->right, t->value );
   }
   return root;
}

void traverseBST(BSTNode* r, enum BSTOrder order){
   if(order == PREORDER) preorder(r);
   else if(order == INORDER) inorder(r);
   else if(order == POSTORDER) postorder(r);
}