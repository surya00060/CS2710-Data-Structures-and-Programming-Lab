// The main objective of the assignment is to create a Disjoint Set Union Data Structure and do operarations like Make_Set , Find_Set , Union_Set .
// This Header File contains the Structure Defenition of Disjoint Set Union and Declaration of Function associated with it . 

#include<stdio.h>				// Header file for Input / Output Operations .
#include<math.h>				// Header file for Mathematical functions .	
#include<stdlib.h>				// Header file for Random function .
#include<time.h>				// Header file for System Clock .

typedef struct dsu 				// Structure dsu is a disjoint element in the set. It has two data fields and a leader pointer .
{
	int value ;					// To store the value of a node .
	int rank ;					// To store the rank .
	struct dsu *leader ;		// Pointer to the Parent node .

}dsu;							// Using typedef to rename struct dsu as dsu .		

void Make_Set( dsu *x , int element ); 	// Make_Set creates a new disjoint set with given element . 

dsu* Find_Set( dsu *x );				// Find_Set finds the set to which the given element belongs . (ie Returns the leader pointer )

void Union_Set( dsu *x , dsu *y );		// Union_Set finds the set to which the elements belong and does Union Operation ammong them . 
			


