// This Program contains main program which uses the Structure declared rb_tree.h and Functions Defined in rb_tree.c to create Red Black Trees and nodes in it .
// In this program we perform dictionary operations such as Insertions , Deletions and Searh Operations in Red Black Tree .
// We measure the time take for Insertion and Deletion for different number of operations and plot it .
// We need to prove Time Complexity is Log(N) for random operations .

#include"disjoint_set.h"							// To include the header disjoint_set.h

#define N 100										// To create the maximum number of elements/sets .

void Print_Set( dsu *Set[] , int No_Of_Sets )		// To print the Sets and elements present in the set .
{
	int i , j , count ;
	
	dsu *temp ;

	for( i = 0 ; i < No_Of_Sets ; ++i )				// To do Path Comprssion before printing.
	{
		temp = Find_Set( Set[i] );
		
	}

	for( i = 0 ; i < No_Of_Sets ; ++i )				// Printing after Path Compression is done .
	{
		count = 0 ;
		printf("Set %d \nElements :" , i +1 );
		for( j = 0 ; j < No_Of_Sets ; ++j )
		{
			if( Set[j] -> leader == Set[i] )
				{
					printf(" %d,", Set[j]-> value );
					count++;
				}
		}
		if( count == 0 )
			printf(" NIL");
		printf("\n\n");
	}
}


int main()											// main() where the exexution of the program starts .
{
	int i , count , choice , find , exit , flag ;	// Loop varaibles and flag .

	srand(time(NULL));								// For Random number generation .
	
	dsu *Set[N];									// Array of dsu data type to store the Sets.

	for( i = 0 ; i < N ; ++i )						// Allocating Space to all Disjoint Set by malloc
		Set[i] = (dsu*)malloc(sizeof(dsu));

	count = 0 ;										// Flag intialisations .
	exit = 0 ;
	flag = 0 ;

	while( count < 100 && exit == 0 )				
	{
		printf("Enter a number for the specific Operation\n\t1.Make Set\n\t2.Find Set\n\t3.Union Set\n\t4.Exit\n");
		scanf("%d", &choice);

		switch(choice)								// Switch case to give users the option to choose which operation to perform .
		{
			case 1 :								// Make_Set and Prints the the Sets .
				Make_Set( Set[count] , count + 10 );	
				count++;
				Print_Set( Set , count );
				break ;
			
			case 2 :								// Gets an elemnet from user and prints which Set it belongs to . 
				if( count >= 1 )
					{
						printf("Enter an element to find which set it belongs\n");
						scanf("%d",&find);

						for( i = 0 ; i < count ; ++i )	
						{
							if( Set[i] -> value == find )
							{
								printf("%d belongs to Set %d\n", find , (Set[i] -> leader -> value) - 9 );
								flag = 1 ;
								break;
							}
						}
					}
				break;

			case 3 :								// Prints the Set before and After Union Operation .It does Union on two random Sets .
				if( count >= 2 )
				{
					printf("Before Union \n");
					Print_Set( Set , count );
					Union_Set( Set[ rand()%count ] , Set[ rand()%count ] );
					printf("After Union \n");
					Print_Set( Set , count );
				}
				break;
			case 4 :								// Exit .
				exit = 1 ;

		}
	}
	

	return 0;
}