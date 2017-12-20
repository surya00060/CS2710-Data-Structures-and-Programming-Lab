#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void Mergewithoutarray( int ar[] , int a , int mid , int b )	// Mergewithoutarray() gets two sub arrays as input which are already sorted . It sorts the element using a temporary variable .
{
	
	int  Left1 = a ,  Right1 = mid , Left2 = mid + 1 , Right2 = b , temp ;	// Left1 : Leftmost index of left subarray Right1: Rightmost index of right subarray . temp : temporary variable .
																			// Left2 : Leftmost index of right subarray Right2:	Rightmost index of right subarray .

	while( Right2 >= Left2 )												// Checking whether Right2 is greater than Left2 .
	{
		Right1 = mid ;														// Assigning Right1 = mid for each iteration of Right2 (ie. Iterating from Right1 to  Left1 ).

		if ( ar[ Right2 ] < ar[ Right1 ] )									// If the element in FirstSub Array is greater than the element ar[Right2] ,
		{
			temp = ar[ Right1 ] ;											//  then  element is stored in temp variable ,

			while( --Right1 >= Left1 && ar[ Right1 ] > ar[ Right2 ] )		// And we are finding any element in left subarray that are greater than the element ar[Right2]
				{
					ar[ Right1 + 1 ] = ar [ Right1 ] ;						// If so then we move the elements in Leftsubarray such that no elemnet is greater than ar[Right2] in Leftsubarray
				}

			ar[ ++Right1 ] = ar[ Right2 ];									// Then storing the element ar[Right2] in its correct position . 
			ar[ Right2 ] = temp ;											// Storing the temp in ar[Right].
			
			Right2--;														// Right2 is decremented .
		
		}

		else 																// If the element in FirstSub Array is smaller than the element ar[Right2] , then Right2 is decremented .
		{
			Right2--;
		}
	}
}

void Merge( int ar[] , int a , int mid , int b )		// Merge() gets two sub arrays as input which are already sorted . It stores the elements of two subarrys array into a sorted temporary
														//  array temp and copies it back to original array . 
{
	int  Left1 = a , Right1 = mid , Left2 = mid + 1 , Right2 = b ;		// Left1 : Leftmost index of left subarray Right1: Rightmost index of right subarray .
																		// Left2 : Leftmost index of right subarray Right2:	Rightmost index of right subarray .		
	int temp[ b - a + 1 ] , i = 0 ;						// Temporary variable of size b-a+1.  i : Variable to access array temp.
	
	while( Left1 <= Right1 && Left2 <= Right2 )			// Checking if both Left1 and Left2 are less than their respective bounds .
	{	
		if( ar[ Left1 ] <= ar[ Left2 ])					// If the elemnet in first sub array is smaller than the other , smallest element is stored in temp array .
		{
			temp[ i++ ] = ar[ Left1++ ];				// After storing in temp array i , Left1 are incremented .
		}
		else 											// Otherwise 
		{	
			temp[ i++ ] = ar[ Left2++ ];				// After storing in temp array i ,Left2 are incremented .
		}
	}
	
	while( Left1 <= Right1 )							// The remaining elemnts of the left subarray are  copied into temp 
	{
		temp[ i++ ] = ar[ Left1++ ];					// After Storing i , Left1 are incremented .
	}

	while( Left2 <= Right2 )							// The remaining elemnts of the right subarray are copied into temp 
	{	
		temp[ i++ ] = ar[ Left2++ ];					// After storing i ,Left2 are incremented .
	}

	for( i = a ; i <= b ; ++i )							// Copying the elements from temp to ar
	{
		ar[i] = temp[i-a] ;
	}
}


void Mergesort( int ar[] , int a , int b )				// A Recursive function to sort the input array . It divides the array into sub arrays recursively and sorts from the least subarray .
{
	if( a < b )											// Checking whether the starting index is less than ending index .
	{
		int mid;
		mid = ( a + b )/ 2;								// Finding the middle index .

		Mergesort( ar , a , mid );						// Calling Mergesort() recursively to divide the array from starting index to middle index .
		Mergesort( ar , mid + 1 , b );					// Calling Mergesort() recursively to divide the array from middle index to last index .
		Merge( ar , a , mid , b );						// Calling Merge() to sort and merge the two divided arrays . It uses a temporary array to merge .O(N) extra Space
														// Complexity of Merging two sorted array is O(N).
		//Mergewithoutarray( ar , a , mid , b );		// Calling Mergewithoutarray() to sort and merge the two divided arrays . It uses temporary variable to merge .O(1) extra Space
														// But Complexity of Merging two sorted arrays is O(N^2).
	}
}

void swap( int *a , int *b )							// A function to swap two integers .
{
	int temp = *a ;										// Stores the content of pointer a in temp variable .
	*a = *b ;											// Stores the content of pointer b in pointer a .
	*b = temp ;											// Stores the temp in content of pointer b
}

int FindPivot( int ar[] , int a , int b )				// FindPivot() selects a random element as a pivot and places the all elments less than the pivot to its left and all the elemnts more
														// than pivot to its right and returns the index of pivot element sorted correctly at its place (ie . Pivot element will be sorted correctly).
{
	int i , j , pivot , pivot_pos ;

	pivot_pos = a + rand()%( b - a + 1 ) ;				// Random pivot element selected using rand().
	pivot = ar[ pivot_pos ] ;							// Storing the value of that random pivot element .

	swap( &ar[a] , &ar[pivot_pos] );					// Swapping the pivot element and First element of array . Now pivot element is at the first position of the array .

	i = a ;												// Starting index for i .
	
	for( j = a + 1 ; j <= b ; ++j )						// j iterates from a + 1 to b .
	{
		if( ar[j] < pivot )								// If a[j] is less than pivot a[j] and a[i] are swapped and i is incremented.
		{
			++i;
			swap( &ar[i] , &ar[j] );	
		}
	}
	
	swap( &ar[i] , &ar[a] );							// Finally Swapping the First elements (pivot element) and an element lesser than pivot
														// Now all the elemnts less than ar[i] are less than pivot and remaining are greater than pivot .
	return i ;											// Returning the index of correctly sorted element .
}
	
void Quicksort( int ar[] , int a , int b )		// A Recursive function to sort the input array . The function first selects a random element as its pivot and places it in its correct position .
												// Then sorts the two subarrays recursively . 
{
	if( a < b )									// Checking whether the starting index is less than ending index .
	{
		int p ;									// To store the position of element that gets placed at correct place after calling Quick()
		p = FindPivot( ar , a , b );			// Calling FindPivot() which places a random element in its correct position , value less than it in its left and more than it in its right side 
												// and returns index of that element .
		Quicksort( ar , a , p - 1 );			// Calling Quicksort() recursively to sort the elements less the value ar[p] ( 0 to p-1) .
		Quicksort( ar , p + 1 , b );			// Calling Quicksort() recursively to sort the elements more the value ar[p] ( p+1 to n-1).
	} 
}

int main()
{
	int m , n , i ;								// m to decide which sorting technique to use . n number of inputs . i loop variable.
	
	scanf( "%d" , &m );							// Reading Sorting technique from user . m = 0 Mergesort m = 1 Quicksort .
	scanf( "%d" , &n );							// Reading number of inputs from user .

	int ar[n] ;									// Creating an array ar of size n to store the numbers to be sorted .
	
	for( i = 0 ; i < n ; ++i )					// Reading the inputs from user .
	{
		scanf( "%d" , &ar[i] );
	}

	srand(time(NULL));							// Using random numbers to select the pivot randomly .
	
	if( m == 0 )								// If m = 0 Calling MergeSort() to sort the input array . The function takes input as array ar , starting index and ending index .
	{
		Mergesort( ar , 0 , n-1 );
	}
	
	else										// Otherwise Calling QuickSort() to sort the input array . The function takes input as array ar , starting index and ending index .
	{
		Quicksort( ar , 0 , n-1 );
	}
	
	printf( "\nSorted Array \n" );
	for( i = 0 ; i < n ; ++i )					// Printing the sorted array .
	{
		printf( "%d\t" , ar[i] );
	}
	printf( "\n" );
}