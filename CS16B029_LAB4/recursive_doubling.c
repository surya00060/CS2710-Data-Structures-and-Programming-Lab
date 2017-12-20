
#include"linked_list.h"

int main( int argc , char* argv[] )				// Reading Command Line Arguments from User 
{
	int N , n1 , i , j ;
	
	N = argc - 1 ;								// No of elemnts entered by user .
	int ar[N] ;									// Creating array ar of N elements .

	if( N == 0 )
		return 0;

	for( i = 0 ; i < N ; ++i)
		ar[i] = atoi( argv[ i + 1] );			// Storing the inputs received from user intoo array ar .	

	struct node *Head = NULL ;					// Creating the Head pointer and assigning it with NULL .
	struct node *a[N] ;							// Creating array a[N] of struct node datatype to store address of each node to access each node after recursive doubling .

	Head = CreateStack( ar , N );				// Calling the function CreateStack to create a stack by passing array of N integers and N as inputs.
	
	CreateArrayStack( a , Head , N );			// Calliing the function CreateArrayStack to store address of each node in each element of an array a .

	printf( "Input Linked List\n" );
	PrintStack( Head );							// Calling the function PrintStack to print contents of each node of stack by passing Head pointer alone .

	
	n1 = ( int ) ceil ( ( log(N) / log(2) ) );	// Recursive doubling Algorithm 
	
	for (i = 0 ; i < n1 ; ++i )					// Loop runs from 0 to n1 (Least Integer Function of Log(N) to base 2)
	{
		for ( j = 0 ; j < N ; ++j )				// Loop runs from 0 to N( no of nodes in array )
			{
				if( a[j] -> next != NULL )		// Checking Whether next node is NULL or not .
				{
					a[j] -> element	+= ( a[j] -> next ) -> element ;	// Summing  next elemnet in next node of Stack .
					a[j] -> next	 = ( a[j] -> next ) -> next    ;	// Moving the pointer to next node's next node .
				}
			}				
	}

	printf( "Output After Recursive Doubling \n" );
	PrintArrayStack( a , N );					// Calling the function PrintArrayStack to print contents of each node by passing array(a) and N  .

	return 0;
}