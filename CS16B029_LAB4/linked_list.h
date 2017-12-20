#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node							// Self Referential Structure 					
{
	int element;					// Element stores integer .
	struct node *next;				// Pointer to store the address of next node .
};


struct node* CreateStack( int ar[] , int N ) ; 	// Function creates a stack using linked list and returns Head pointer . It takes Number of elemnets and elemnets to be added in array  as arguments.

void PrintStack( struct node *Head ) ;	// Function which prints the contents of each node of stack when Head pointer is passed as argument.

void CreateArrayStack( struct node *a[] , struct node *Head , int N) ;	// Function which stores the address of each node of stack in a array(a) of size N.

void PrintArrayStack( struct node *a[] , int N ) ;	// Function which prints the contents of each node of stack when called through array(a) instaed of Head pointer .




