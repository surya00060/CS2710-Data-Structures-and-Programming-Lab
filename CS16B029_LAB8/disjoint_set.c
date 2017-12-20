//This program has function defenitions for function and structures defined in disjoint.h .

#include"disjoint_set.h"					// Including the header file .

void Link_Set( dsu *x , dsu *y );

void Make_Set( dsu *x , int element )		//Make_Set creates a new disjoint set with given element . 
{
	x -> value = element ;					// Stores the given element into data structure .
	x -> rank = 0 ;							// Makes the rank of the set to be 0 .
	x -> leader = x ;						// Makes itself as the leader .
}

dsu* Find_Set( dsu *x )						//Find_Set finds the set to which the given element belongs . (ie Returns the leader pointer ) .
{
	if( x != x -> leader )					// If x isn't the leader of its set then we call the function recursively to find the leader of the set and also do Path Compression .
		x -> leader = Find_Set( x -> leader );	// Recursive call .

	return x ->leader ;						// Returns the leader of the set .
}

void Union_Set( dsu *x , dsu *y )			// Union_Set finds the set to which the elements belong and does Union Operation ammong them . 
{
	Link_Set( Find_Set(x) , Find_Set(y) );	// Union_Set() calls Link_Set to do union operation .
}

void Link_Set( dsu *x , dsu *y )			// To do Union Operation among two sets.
{
	if( x -> rank > y -> rank )				// If the rank of leader of x is greater than rank of leader of y 
		y -> leader = x ;					// then x becomes the leader.
	else
		x -> leader = y ;					// else y becomes the leader.

	if( x -> rank == y -> rank )			// If rank of both leaders are same then rank of y increases as y becomes the leader .
		(y -> rank)++ ;
	
}	


