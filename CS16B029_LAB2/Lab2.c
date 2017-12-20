#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000												/* MAXSIZE is the maximum size of the invisible array or ADT in bytes . #defines replaces MAXSIZE with 1000000 during
																		compilation .So MAXSIZE can be used as a variable throughtout the program. */

int N ;																// N is the global variable which stores the total number of operations (Requests + Free) as requested by the users.

int Alloted[MAXSIZE][2] , Free[MAXSIZE][2] ;						// Alloted[MAXSIZE][2] is the alloted list  which contains STARTING ADDRESS and MEMORY of alloted spaces.
																	// Free[MAXSIZE][2] is the free list which contains STARTING ADDRESS and MEMORY of free spaces.

int Free_space , Alloted_space ;									// Free_space and Alloted_Space contains total free spaces and alloted spaces at any time. Free_space +Alloted_space=MaXSIZE.
																			


int GarbageCollector( int memory )									/* 	GarbageCollector takes requested memory as arguments and modifies the allocated and free list and returns the index of the 
																		alloted list where the memory is allocated. ADT or the invisible array is modified such that all alloted spaces are moved up 
																		and  free spaces are moved down ie. Alloted spaces and Free Spaces are not lying inbetween each other. This is implemented by 
																		modifying Free[][] and Alloted[][] */							
{
	int i , j ;														// For Loop variables. In this block all the free blocks go to bottom and alloted spaces to the top of list. 

	for ( i = 0 ; i < N ; ++i )										// Iterating Free[][].
	{
		if( Free[i][0] != -1 )										// Finding  non empty elements in the free list Free[][].
		{
			for ( j = 0 ; j < N ; ++j )								// Iterarting Alloted[][].
			{
				if( Alloted[j][0] > Free[i][0] )					// If the starting memory address of the alloted list is more than free list (ie.There is alloted block after  a free block )
																	// then all the elements starting address in Alloted list are moved up and free elements are moved down.
				{
					Alloted[j][0] -= Free[i][1] ;
				}
			}
			Free[i][0] = -1 ;										// Emptying the Free[][].
		}
	}
	Free[0][0] = MAXSIZE - Free_space ;								// All free spaces are stored in Free[0][0] with starting index as MAXSIZE - Free_space and memory as Free_space.
	Free[0][1] = Free_space ;

	if( Free_space >= memory )										// Allocating the memory to modified list.
	{
		for( j=0 ; j < N ; j++ )									// Iterarting Alloted[][].
		{

			if( Alloted[j][0] == -1 )								//  Checking whether the element is empty.
			{
				Alloted[j][0] = Free[0][0] ;						// Alloting the requested memory by copying the starting address from Free[][] to Alloted[][]
				Alloted[j][1] = memory ;							// Assigning the requested memory to alloted list Alloted[][].
																					
				Free_space 		-= memory ;							// Increamenting total alloted space and decreamenting total free space by requested memory.
				Alloted_space 	+= memory ;

				if(Free[0][1] == memory)
				{
					Free[0][1] -= memory ;							// Modifying the space in free list free[][] after allocating requested memory.											
					Free[0][0] = -1 ;								// If the requested memory is equal to the memory of element in the Free[][] then that element is emptied.
				}
				else
				{
					Free[0][1] -= memory ;							// Modifying the space in free list free[][] after allocating requested memory.
					Free[0][0] += memory ;							// Otherwise the Staring position of that element in free list is modified by request memory. 
				}
				//printf( "ALLOTED\n" );
				return j ;											// Returns the index as returned by the  GarbageCollector() .
				
			}					
		}
	}
}

int Request_Memory( int memory )						/* The function which takes memory as an argument and returns the index of alloted list. This function checks whether the given memory 
														   can be alloted to the user. If the memory is greater than total free space then it returns -1. If the memory is available in free 
														   list as a single block it alloctes and returns the index . Otherewise it calls Garbage Collector function. */
{
	if( memory > Free_space )
		{
			printf( "Memory not available to allot\n" );	// If the requested memory is more than the total free space then the function returns -1.
			return -1 ;
		}

	int i,j;											// For Loop variables

	for( i = 0 ; i < N ; ++i )							// Iterating Free[][]
	{
		if( Free[i][0] != -1 )							// Finding an non empty element in the free list Free[][].
		{
			if ( Free[i][1] >= memory )					// Checking whethere Free space in the element of free list is suffient for requested memory.
			{
				for( j = 0 ; j < N ; ++j )				// Iterarting Alloted[][].
				{

					if( Alloted[j][0] == -1 )			// Finding an empty element in alloted list Alloted[][] to allot requested memory.
					{
						Alloted[j][0] = Free[i][0] ;	// Copying the starting address of the slot from Free[][] to Alloted[][].
						Alloted[j][1] = memory ;		// Assigning the requested memory to alloted list Alloted[][].

						Free_space 		-= memory ;		// Increamenting total alloted space and decreamenting total free space by requested memory.
						Alloted_space 	+= memory ;

						if( Free[i][1] == memory )		// If the requested memory is equal to the memory of element in the Free[][] then that element is emptied.
							{
								Free[i][1] -= memory ;	// Modifying the space in free list free[][] after allocating requested memory.
								Free[i][0] = -1 ;
							}
						else
							{
								Free[i][1] -= memory ;	// Modifying the space in free list free[][] after allocating requested memory.
								Free[i][0] += memory ;	// Otherwise the Staring position of that element in free list is modified by request memory. 
							}

						//printf( "ALLOTED\n" );
						return j ;						// Returns the index of alloted list Alloted[][] where the requested memory is alloted.
					}					
				}
			}
		}
	}

	return GarbageCollector( memory ) ;					// Returns the index as returned by the  GarbageCollector() .


}

void Free_Memory( int index )							/* A function to free memory. The function takes index of alloted list  and free the memmory associated with alloted list index. 
														   It adds the memory to free list and removes it from alloted list by assigning to -1	*/
{
	int i;

	if( Alloted[index][0] == -1 )							// If the index in alloted list is empty then returning back to main. 
		return ;

	for( i = 0 ; i < N ; ++i )								// To find the free slot in the array Free[][] from 0 to MAXSIZE-1.
	{
		if( Free[i][0] == -1 )								// Checking if the slot is free in the array Free[][].
		{
			Free[i][0] = Alloted[index][0] ;				// Copying the details from alloted list Alloted[][] to free list Free[][].
			Free[i][1] = Alloted[index][1] ;

			Alloted[index][0] = -1 ;						// Removing the freed memory from alloted lisr Alloted[] by assigning -1.

			Free_space 		+= Alloted[index][1] ;			// Increamenting the total free space and decreamenting the total alloted space by freed memory. 
			Alloted_space  	-= Alloted[index][1] ;

			//printf( "FREED\n" ); 						
			return ;
		}
	}
}
 
void Bubblesort( int a[][2] ,int N )								// Function to sort the alloted list and free list. The list is sorted in increasing order of Starting memory location.
{
	int i , j , temp1 , temp2 ;										// Loop Variables and temporary variables. 

	for( i = 0 ; i < N ; ++i )
	{
		for( j = 0 ; j< N-1 ; ++j )
		{
			if( a[j][0] > a[j+1][0] )								// Comparing two elements staring address.
			{
				temp1 		= a[j][0] 	; temp2 	= a[j][1] ;		// Swapping two elements in list .
				a[j][0] 	= a[j+1][0] ; a[j][1] 	= a[j+1][1] ;
				a[j+1][0] 	= temp1 	; a[j+1][1]	=temp2;
			}
		}
	}
}


int main()
{
	int i , j , k = 0 ;									// Loop Variables.

	Free_space 		= MAXSIZE ;							// Intializing the total free space to be MAXSIZE and total alloted space to be 0.
	Alloted_space 	= 0 ;
	
	printf( "Enter the value of N : " );				// Requesting the value of global variable n which denotes the total no of operations
	scanf( "%d" , &N );									

	for( i = 0 ; i < N ; ++i )							// Intialising the alloted list and free list as empty with -1. Using -1 to mean empty.
		Free[i][0] = Alloted[i][0] = -1 ;
	
	Free[0][0] =  0 ; 									// Intialising the the starting free index  as 0 and memory as MAXSIZE in free list Free[][].
	Free[0][1] = MAXSIZE ;
	
	int index[N] , input[1][2] ;						// index[MAXSIXE] stores the index of alloted list returned by Request function. input[1][2] stores the input given by the user for each iteration of n. 

	int count = 0 ;										// count variable to count how many times Memory Request is succesful.

	for( i = 0 ; i < N ; ++i )							// Iterations over n . Each time a value is read from user and memory is requested or freed .
	{
		scanf( "%d %d", &input[0][0] , &input[0][1] );	// Reading the values from user.

		if( input[0][0] == 1 )							// If input[0][0] is 1 , Memory is requested else memory is freed.  
		{
			index[count] = Request_Memory( input[0][1] );		// Memory is requested and index  is stored in index[] if it is not-1.
			if( index[count] != -1 )
				count++ ;
		}

		else if ( input[0][0] == 2 )
		{
			Free_Memory( index[ input[0][1] ] );						// Memory is freed.
			count--;
		}
	}
	
	Bubblesort( Alloted , N ) ;		Bubblesort( Free , N ) ;			// Sorting Alloted List and Free List .
	
	if( count == 0 )													// To check whether Alloted list is empty or not .
	{
		printf("Alloted List is empty\n" ) ;
	}

	else
	{ 
		printf( "Alloted List \n" );									// Printing Alloted List in the Format : Index ; Starting Adress ; Memory size.
		printf( "Index\tStartingAddress\tMemory Size\n" );
		for( i = 0 ; i < N ; ++i )
		{
			if( Alloted[i][0] != -1 )									// Printing only  non empty elements . k is varaibale to print the index correctly because sort fuction sorts with -1 as addresss and not empty .
			{
				printf("%d\t\t%d\t\t%d\n", k , Alloted[i][0] , Alloted[i][1] );
				k++ ;
			}
		}
	}

	if( Free_space ==0 )
	{
		printf( " Free List is empty \n" );
	}
	else
	{
		printf("Free List \n");												// Printing Free List in the Format : Index ; Starting Adress ; Ending Address.
		printf("Index\tStartingAddress\tEndingAddress\n" );
		for( i = 0, k = 0; i < N  ; ++i)
		{
			if( Free[i][0] != -1 )											// Printing only  non empty elements . k is varaibale to print the index correctly because sort fuction sorts with -1 as addresss and not empty .
		
			{
				printf("%d\t\t%d\t\t%d\n", k , Free[i][0] , Free[i][1] + Free[i][0] - 1 ); 
				k++ ;
			}
		}
	}	
	return 0 ;
}
