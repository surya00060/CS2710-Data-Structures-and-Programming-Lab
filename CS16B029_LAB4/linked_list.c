#include"linked_list.h"

struct node* CreateStack( int ar[] , int N )	// Function creates a stack and returns Head pointer . It takes no of elemnets and elemnts to be added as argument.
												// The function stores the first element of array as the TOP of stack and last element of array of BOTTOM of stack. 
{
	int i = N - 1 , count = 0 ; 								// Variable i to access the integer array from reverse . Variable Count to store exactly N elements in a stack.
											
	struct node *Head = NULL ;									// Creating the Head pointer and intialising with NULL .

	while( count < N )											// Iterating till count is less than N .		
	{
		struct node *temp ;								
		temp = (struct node *) malloc( sizeof(struct node) );	// Creating a temporary node of Struct Node data type and allocating space dynamically using malloc .

		temp -> element = ar[i--];								// Storing the element of array to node temp.
		temp -> next	= Head;									// Storing the address of Head  Pointer in node temp's self referential part.
		Head			= temp ;								// Moving the Head pointer to the inserted node .
		count++ ; 
	}
	return Head ;												// Returns the Head pointer from which all the elements of stack can be accessed .
}

void PrintStack( struct node *Head )					// Function which prints the contents of stack when Head pointer is passed as argument.

{
	struct node *temp ;									// Creating temporary node temp and asssigning it to top of Stack. 
	temp = Head ;

	while( temp != NULL )								// Iterating till temp becomes NULL.
	{
		printf( "%d\t" , temp -> element );				// Printing the element stored in stack from top to bottom.
		temp = temp -> next ;							// Changing the temp to next node in Stack.
	}

	printf( "\n" );
}

void CreateArrayStack( struct node *a[] , struct node *Head , int N)	// Function which stores the address of each node of stack in a array(a) of size N.
{
	struct node *temp ;
	temp = Head ;								// Creating temporary node temp and asssigning it to top of Stack. 
	
	for( int i = 0 ; i < N ; ++i )				// Iterating over N iterations .
	{
		a[i] = temp ;							// Assigning the address of each node to array(a[i])
		temp = temp -> next ;					// Changing the temp to next node in Stack.
	} 

}

void PrintArrayStack( struct node *a[] , int N )	// Function which prints the contents of node of stack when invoked through array(a) instaed of Head pointer .
{
	for ( int i = 0 ; i < N ; ++i )					// Iterating over N iterations .
	{
		printf( "%d\t" , a[i]->element );			// Prnting the element of node associated with a[i] .
	}
	
	printf( "\n" );

}


