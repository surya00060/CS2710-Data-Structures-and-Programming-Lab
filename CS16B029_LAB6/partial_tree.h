// This Header File contains the Structure Defenition and Declaration of Function associated with it . 


#include<stdio.h>				// Header file for Input / Output Operations .
#include<math.h>				// Header file for Mathematical functions .	
#include<stdlib.h>				// Header file for Random function .
#include<time.h>				// Header file for System Clock .

struct node 					// Structure Node represent a node in a Binary Search Tree . It has two data fields and three address fields (self refrentials pointers ).
{
	int value ;					// To store the value of a node in tree .
	int deleted ;				// To mark the node as deleted or not . 1 = Deleted , 0 = Not Deleted .
	
	struct node *parent ;		// Pointer to the Parent node .
	struct node *left 	;		// Pointer to the Left subtree .
	struct node *right 	;		// Pointer to the Right subtree .
};


struct node* Insert( struct node **root , int element );	// Recursive function to insert a new node into Binary Search Tree .

struct node* Search( struct node *root , int element );		// Function which searches the element and returns the pointer to element in Tree .

void Delete( struct node *root );							// Function which marks the input node as Deleted . ie Deleted = 1 .

void DestroyTree ( struct node *root );						// A Recursive function which frees the memory allocated using malloc and destroys the tree .

int CountNodes( struct node *root );						// A Recursive function which counts the number of nodes  below the input node associated with it and including itself . 

struct node* Rebuild( struct node *root , int ar[][2] , int a , int b );			// A Recursive function which takes a sorted array as input and builds the array into BST .

void Inordertransversal( struct node *root , int ar[][2] , int *index , int flag );	// A Recursive function which converts a BST into sorted array without considering whether the node is deleted or not .

void Insert_Rebuild(  struct node **ins_node, float alpha );	// A Function which checks whether the nodes are alpha balanced after insertion .

struct node* Delete_Rebuild( struct node *root , int total_nodes , int deleted_nodes );		// A function which takes number of nodes and deleted nodes as arguements and rebuild the entire BST .

int Height( struct node *root );							// A Function which takes node as arguement and returns the height of the input node . 			

void Print( struct node *root , int level );				// A recursive function which prints all nodes present in the  same level .

void LevelOrder( struct node *root );						// A function which calls Print() to print all nodes in BST .


