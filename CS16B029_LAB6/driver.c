// This Program contains main program which uses the Structure declared partial_tree.h and Functions Defined in partial_tree.c to create Partial Rebuilding Tree .
// In this program we do Amortized Analysis on Insertion and Deletion Operations of Partial Rebuilding Binary Search Tree .
// We measure the time take for Insertion and Deletion for different number of operations and plot it .
// We need to prove Amortized cost is Log(N) for random Inserations and Deletion .

#include "partial_tree.h"										// To include the header partial_tree.h

#define MaxSize 10000											// To limit the maximum value of random number generated .

float alpha = 0.5 ;												// The value of alpha for alpha-Balanced BST .

int main()
{
	clock_t start , end ;										// Variabes used to measure time for each insertions and deletions .					
	
	srand( time( NULL ) ) ;										// Used to generate random numbers					
	
	double time ;												// time is used measure time for each 2^i operations .								
	
	int insertions , deletions , deleted_nodes  ;				// inserations used to count number of insertions ; deletions used to count number of deletions ; deleted_nodes used to count no of nodes marked for deletion 
	int total_nodes , i ;										// total nodes used to store the total no of nodes returned by function CountNodes. 
	int coin , element ;										// Tossing Coin to select insertion or deletion ; Element generated by rand() for insertion or deletion .

	FILE *out ;													// Creating a File pointer					
	out = fopen( "graph.txt" , "w" );							// Opening the file "graph.txt" in write mode.	
	
	for(  i = pow( 2 , 10 ) ; i<= pow( 2, 18 ) ; i*=2 )			// Iterating for different number of total operations.  
	{
		time = 0 ; insertions = 0 ; deletions = 0 ;  deleted_nodes = 0 ; // Intialising time , insertions , deletions , deleted_nodes  to be  zero for each value of i .
		
		struct node *root = NULL ;										// Declaring a new node of tree . 
		
		start 	= clock() ;												// Start time for  operation .	

		while( insertions + deletions <= i )							// Iteraring for number of operations less than i .
		{
			coin = rand()%2 ;											// Tossing of a coin . Doing 50% insertion and 50% Deletion .
		
			if( coin == 1  )											// If coin equals to 1 then insertion happens.
			{
				element = rand()%MaxSize ;								// Generating a random number for insertion .

				struct node *temp = Insert( &root , element );			// Inserting the random number into BST .
				insertions++ ;											// Incrementing the number of insertions .
				Insert_Rebuild( &temp , alpha );						// Checking whether the BST is alpha-balanced from leaf to root .
			}
			
			else if ( coin == 0 && insertions > deletions )				// If coin equals 0 then deletion happens and also checking if insertions greater than deletions .
			{
				element = rand()%MaxSize;								// Generating a random number for deletion .
	
				struct node *temp  = Search( root , element );			// Searching whether the random number is present in BST .
				
				if( temp != NULL )
				{
					Delete( temp );										// If present then that element is marked "Deleted" .
					deletions++ ; deleted_nodes++ ;						// Incrementing the number of deletions and deleted nodes .
					total_nodes = CountNodes( root );					// Calculating total number of nodes present in BST .

					if( deleted_nodes > 0.5 * total_nodes )				// If the no of nodes marked for deletion is greater than half times the total number of nodes Rebuild the tree at node root .
					{
						root = Delete_Rebuild( root , total_nodes , deleted_nodes );	// Rebuilding the entire BST by removing deleted elemnts .
						deleted_nodes = 0 ;												// Making no of Deleted nodes as Zero after rebuilding . 
					}
				}
			}
			
			end 	= clock() ;															// End time for deletion operation .
			time 	= (double) (end-start) ;											// Calculating time for each operation .
			time 	/= CLOCKS_PER_SEC ;													// Converting the time into seconds	.
		}
	
	DestroyTree(root);																	// Freeing the memory allocated using malloc .
	fprintf( out , "%d\t%.10f\n" , i  , time/i ) ;										// Writing the outputs to file "graph.txt".

	}
	
	fclose( out ) ;																		// Closing the File .
	
	return 0;
}

