// Name : Surya S
// Roll No : CS16B029  

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define N 8								// N as power of 2 .
#define MaxSize 20						// Maximum size for random number .


// Data Structure used : Max Heap by Array Implementation . 
// Temporay array is Max Heap of the array with partial sums as elements.  
// Was able to implement Only Add Function in Log(N) steps . Not able to implement PreSum in Log(N) steps.

int PreSum( int ar[] , int temp[] , int t )					
{
	int i = 0 ; 
	if( t%2 != 0 )
	{

	}
	int sum = 0 ;
	for ( i = 0 ; i <= t ; ++i )
		sum += ar[i] ;

	return sum ;
}

void Add( int a[] , int temp[] , int k  , int  p )				// Modifies both the original and temporary array .
{
	if( k < N )													// To prevent Segmentation fault .
	{
		a[k] = a[k] + p ;  										// Modifying in orignial array . 

		int i  = 1 ;											// Modifies the (temporary array) heap from the root to leaf .
																// Since the the number of nodes in path is Log(N) from root to leaf . This Function has T(N) = O(Log(N)) . 
		int number  = N ;
	
		while( number != 1 )									// Each Iteration number becomes half implies Log(N) iterations .
		{
			temp[i] += p ;

			if( k < number/2  )
			{
				i = 2 * i ; 
				number =  number/2 ;		
			}

			else 
			{
				i = 2 * i + 1 ;
				number = number/2 ;
				k = k - number ;
			}

		}
	}

}

int main()
{
	srand(time(NULL));
	double time ;
	clock_t start , end ;

	

	int ar[N] ; int temp[N] ;
	
	int i , j , choice = -1 ;

	for( i = 0 ; i < N ; i++ )
		ar[i] = i + 1 ;
// Creating Temporary array similar to Maximum Heap. If i is the root then 2*i and 2*i + 1 are the child .
// First Index is  0 . The Next index has the root of heap . Then other elements are its children . 
	for( i = N/2 , j = 0  ; i <= N ; ++i , j++ )
	{
		temp[i] = ar[ 2*j ] + ar[ 2*j + 1 ] ;
	}
	
	for( i = (N/2) - 1 ; i > 0 ; --i )
	{
		temp[i] = temp[ 2 *i ] + temp[ 2 * i + 1 ];
	}

	ar[0] = 1 ;
	temp[0] = 0 ;

	/*FILE *out ;										// Creating a File pointer					
	out = fopen( "graph.txt" , "w" );	

	for( i = pow( 2 , 10 ) ; i <= pow( 2 , 16 ) ; i*=2 )
	{
		start 	= clock() ;	
		j = 0;

		while( j < i )
		{
			Add( ar , temp , 2 , 6 );
		}
		end 	= clock() ;										// End time for deletion operation .
		time 	= (double) (end-start) ;						// Calculating time for each 2^i operation .
		time 	/= CLOCKS_PER_SEC ;								// Converting the time into seconds .
		fprintf( out , "%d\t%.10f\n" , i  , time/i  ) ;			// Writing the outputs to file "graph.txt".	
	}
	*/

	while ( choice != 0 )
	{	
		printf("Original Array : ");
		for( i = 0 ; i < N ; ++i  )
			printf("%d ", ar[i] );
		printf("\nTemporary Array or Heap : ");
		for( i = 0 ; i < N ; ++i  )
			printf("%d ",temp[i] );

		printf(" \n1 . Add\n0. Exit \n ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:	
			printf("Adds 6 to the random element  \n");
			Add( ar , temp , rand()%N , 6 );

			//case 2:

			//default:
		}

	}
	
	return 0;
}