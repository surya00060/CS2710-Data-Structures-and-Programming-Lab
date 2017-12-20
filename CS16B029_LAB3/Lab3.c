#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define N 1											// N is the initial size of dynamic Array

int SIZE = N , Elements = 0 ;						// SIZE is Maximum Size of the dynamic Array. Elements is the number of filled elements in the array. Intially array is empty .

int* insert( int *A )								/* insert() is used to  insert an element into dynamic array. The function takes pointer of array as an arguement and returns pointer 
														after inserting. After inserting if the array becomes full , array is doubled its size. */
{
	int i ;											// Loop Variable .
	
	A[ Elements ] =  1;						// Adding an element to array A .
	Elements++ ;									// Increasing the number of elements in the array A.			
	
	if( SIZE == Elements )							// If the array A becomes full after insertion then a new array Ar of twice size of A is created and all elements of A are copied into Ar.
	{
		SIZE *= 2 ;									// SIZE is doubled.

		int *Ar ;
		Ar = (int *) malloc( sizeof(int) * SIZE ); 	// Creating a new arry Ar and using mallloc() for dynamic allocation.
		
		for( i = 0 ; i < Elements ; ++i )			// Copying elements from array A to array Ar .
		{
			Ar[i] = A[i] ;
		}

		free( A ) ;									// Freeing the memory allocated to array A .
										
		return Ar ;									// Returning new array Ar after doubling the size of array .
	}

	return A ;										// Returning array A after insertion.
}


int* delete( int *A )								/* delete() is used to delete an element in dynamic array.The function takes pointer of array as an arguement and returns pointer 
														after deletion. After deleting if the array becomes 1/4th ,array is halved its size. */ 

{
	int i ;											// Loop Variable
	A[ Elements ] = -1;												// We are not deleting the element from memory we just decrease the number of elements in it. We free the whole array from memory only when elements<size/4.
	--Elements ;									// Decresing the number of elements in the arry A .								

	if( Elements <= SIZE/4 )						// If the array A becomes one fourth after deletion then a new array Ar of half the size of A is created and all elements of A are copied into Ar.
	{
		SIZE = SIZE/2 ;								//	SIZE is halved

		int *Ar ;
		Ar = (int *) malloc( sizeof(int) * SIZE );	// Creating a new arry Ar and using mallloc() for dynamic allocation.

		for( i = 0 ; i < Elements ; ++i )			// Copying elements from array A to array Ar .
		{
			Ar[i] = A[i] ;
		}

		free( A ) ;									// Freeing the memory allocated to array A .
		
		return Ar ;									// Returning array Ar after halving the size of array and copying the elements in A.
	}
	
	return A ;										// Returning array A after deletion.
}
	

int main( int argc , char* argv[ ] )					// Using Command Line arguements to receive inputs from user. 
														// Input Format : n1 , n2 ; n1 is the base and n2 is the power.
{

	clock_t start , end ;								// Variabes used to measure time for each insertions and deletions .
	srand( time( NULL ) ) ;								// Used to generate random numbers
	
	double time , total_time ;							// time is used measure time for each operation. total_time is used to calculate total time for each number of operations .
	int i , insertions , deletions ;					// i is Loop Variable . inserations used to measure number of insertions .deletions used to measure number of deletions.
	int n1 , n2 , coin ;								// n1 , n2 Input variables from user . Coin for tossing biased coin.										
	
	if( argc != 3 )
	{
		printf( "Input Format: ./a.out n1 n2 \nn1: base ; n2 : power\n" );
		return 0;
	}
	n1 = atoi( argv[1] );								// Receiving the input from user. n1 is the base  and n2 is the power .
	n2 = atoi( argv[2] );
	
	int *A ;											// Creating a new arry A of SIZE N and using mallloc() for dynamic memory allocation.
	A = (int *) malloc( sizeof(int) * SIZE );

	FILE *out ;											// Creating a File pointer
	out = fopen( "graph.txt" , "w" );					// Opening the file "graph.txt" in write mode.

	printf("\nNo of Operations\tTime Per Operation\tTime\n");

	for( i = pow( n1 , n2 ) ; i < pow( n1 , n2 + 10 ) ; i *= n1 )	// Iterating for different number of total operations.  
	{
		total_time = 0 ; insertions = 0 ; deletions = 0 ;			// Intialising time , insertions , deletions to be zero for each number of total opeartions.
		start 	= clock() ;	
		while( insertions + deletions < i )				// Iteraring for number of operations less than i .
		{	
			
			coin = rand() % 5 ;							// Tossing of a  biased coin . 60% for insertions and 40% for deletions.

			if( coin == 0 || coin == 1 || coin == 2 )	// If coin equals to 0,1,2 then insertion happens.
			{
				//start 	= clock() ;						// Start time for insertion operation .	
				A 	= insert( A ) ;						// Calling insertion function.
				//end 	= clock() ;						// End time for insertion operation.

				insertions++ ;							// Counting the number of insertions happened.
				
				//time 		 = (double) (end-start) ;				
				//time 		/= CLOCKS_PER_SEC ;			// Converting the time into seconds	.
				//total_time 	+= time ;					// Adding the time  for i operations.
			}
			
			else  if ( ( coin == 3 || coin == 4 ) && insertions > deletions )	//If coin equals 3,4 then deletion happens and also checking insertions greater than deletions.
			{
				//start 	= clock() ;						// Start time for deletion operation .
				A 	= delete( A ) ;						// Calling deletion function.
				//end 	= clock() ;						// End time for deletion operation.

				deletions++ ;							// Counting the number of deletions happened.
				
				//time 		 = (double) (end-start) ;				
				//time 		/= CLOCKS_PER_SEC ;			// Converting the time into seconds	.
				//total_time 	+= time ;					// Adding the time  for i operations.
			}

				
		}

		end 	= clock() ;	
		time 	= (double) (end-start) ;
		time 	/= CLOCKS_PER_SEC ;

		fprintf( out , "%d\t%0.15f\t%f\n" , i , time/i , time ) ;	// Writing the outputs to file "graph.txt".
		
		printf( "%d\t\t%0.15f\t\t%f\n" , i , time/i , time ) ;		// Printing number of operations , average time per operation and time .

	}	
	
	fclose( out ) ;																// Closing the File .
	
	return 0 ;
}