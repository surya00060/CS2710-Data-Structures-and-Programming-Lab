// The main objective of the assignment is to construct a Red Black Tree and do Insertion , Deletion and Search Operations .
// This Header File contains the Structure Defenition of Red Black Tree and Node and Declaration of Function associated with it . 

#include<stdio.h>				// Header file for Input / Output Operations .
#include<math.h>				// Header file for Mathematical functions .	
#include<stdlib.h>				// Header file for Random function .
#include<time.h>				// Header file for System Clock .

#define RED 0					// Defining RED as 0 .
#define BLACK 1					// Defining BLACK as 1. 

typedef struct node 			// Structure Node represent a node in a tree . It has two data fields and three address fields (self refrentials pointer ).
{
	int value ;					// To store the value of a node .
	int color ;					// To store the color of the node . whether RED or BLACK . 0 = Red . 1 = Black .

	struct node *parent ;		// Pointer to the Parent node .
	struct node *left 	;		// Pointer to the left subtree .
	struct node *right 	;		// Pointer to the right subtree .

}node;							// Using typedef to rename struct node* as node .					

typedef struct tree 			// Structure Tree represents a RED BLACK Tree . It has two datatypes of structure Node to store the Root and Nil pointer of each Red Black Tree .
{
	struct node *root ;			// Root to store the root of a RB Tree .
	struct node *Nil ;			// Nil replaces all the NULL in BST . Nil is node where all the leaves and parent of root points to .

}tree;							// Using typedef to rename struct tree as tree .

tree* Intialise();				// Intialise() allocates space to Tree( ie. Nil and root pointer ) and returns the pointer to alloted memory . We can create many RB Trees using this function .  

void RightRotate( tree *t , node *y );// RightRotate() moves the node in left subtree above and node in right subtree below .

void LeftRotate( tree *t , node *x ); // LeftRottae() does the reveerse process of RightRotated() .

void RB_Insert( tree *t , int element );// RB_Insert() inserts the given element as a node into a Red Black Tree and Calls the function RB_Insert_Recolor() to recolor or fixup changes in the tree . 

void RB_Insert_Recolor( tree *t , node *x );// RB_Insert_Recolor() fixes the colors in the tree to make the tree follow Red Black Properties . 

node* Search( tree *t , int element );		// Function which searches the element required and returns the pointer to the element in Red Black Tree T .

node* FindMin( tree *t , node * root );		// Function to find the minimum element below a given node in Red Black Tree T . 

void RB_Delete( tree *t , int element );	// RB_Delete() deletes the element in Red Black Tree and fixes if any black node is deleted because deletion of Red node wont affect the black height .

void RB_Delete_Recolor( tree *t , node *x); // RB_Delete_Recolor() fixes the color change due to deletion of black node .

int height(node *root );					// A Function which takes node as arguement and returns the height of the input node . 	

void PrintLevel( node *root, int level );	// A recursive function which prints all nodes present in the  same level .

void LevelOrder(tree *t);					// A function which calls Print() to print all nodes in a Red Black Tree T  .

void DestroyTree(tree *t);					// A function which destroys the Tree allocated using Intialiser .

void DestroyAllNodes( node *t , node *Nil );// A function which frees all the nodes in tree without affecting the tree pointer .
