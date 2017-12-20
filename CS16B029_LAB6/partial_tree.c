// This program has Function Defentions for Function Declared in the header partial_tree.h .


#include "partial_tree.h"								// To include the header partial_tree.h

struct node* Insert( struct node **root , int element )	// Insert() inserts the given element into BST and returns the node where element is stored . 
														// It takes address of root of BST( pointer to pointer ) and elemnt to be inserted as arguments . Returns the node where element is addedd .
														// Root of BST is passed by address . So any inserions in TREE will be directly reflected in root in main program .
{	
	
	struct node *temp = NULL ;								// A new node which contains the value of elemnt to be added .

	temp = (struct node*)malloc( sizeof( struct node ) ) ;	// Allcating space using malloc .
	temp -> value = element ;								// Storing the elemnet into node .
	temp -> deleted = 0 ;									// Marking the elemnt as NOT DELETED . DELETED : 1 otherwise 0 .
	temp -> left = temp -> right = temp -> parent = NULL ;	// Initailising left , right and parent as NULL for new node .

	struct node **temp1 = root ;							// A temporary pointer to node for iterating through BST .

	if( *root == NULL )										// If root is NULL (ie there is no tree )
	{
		*root = temp ;										// Then new node is pointed to root 
		return *root ; 										// And root is returned .
	} 

	while( *temp1 != NULL )									// Otherwise we iterate through BST unless 
	{
		temp -> parent = *temp1 ;							// Modifing the parent of new node as temporary node for each iteration .

		if( (*temp1) -> value > element )					// If the value of element is less than elemnt in BST then iterate in LEFT SubTree .
			temp1 = &(*temp1) -> left ;

		else if ( (*temp1) -> value < element )				// If the value of element is more than elemnt in BST then iterate in RIGHT SubTree .
			temp1 = &(*temp1) -> right ;

		else   												// If the elemnet is  already present in tree then return the address where it is present .
			return *temp1 ;
	}
	*temp1 = temp ;											// Adding new node to BST .

	return *temp1 ;											// Returning the address of the node present in tree .
}

struct node* Search( struct node *root , int element )	// Search() takes the root of BST and element to be searched as arguements and returns the node where that element is present . 
{														//It returns NULL if the element is not present or if it is marked DELETED		
	
	while( root != NULL )								// Checking root is not NULL
	{
		if( root -> value == element && root -> deleted != 1 )	// If the element is present and not marked deleted the return the node . 
			return root ;
		else
		{
			if( root -> value > element )				// If the elemnt is less than value of node then Serach in Left Subtree .
				root = root -> left ;
			else 										// Else Search in Right subtree .
				root = root -> right ;
		}
	}

	return NULL ;									// Return NULL if not present or marked Deleted . 									
}

void Delete( struct node *root )					// Delete() is used to mark the given node as deleted . It takes the node to be marked for deleted as an argument.
{
	root -> deleted = 1 ;							// It changes the node's deleted value to be 1. Deleted = 1 ; Not Deleted = 0 ;
}

void DestroyTree ( struct node *root )				// DestroyTree() is a Recursive function which is used to FREE the memory allocated by malloc to all the nodes in BST.
													// It takes input as node and removes all the nodes associated with it and FREES the allocated memory .
{
	if( root != NULL )								// Checking Whether the node is FREE or FULL . 
	{												
		DestroyTree( root -> left );				// If not NULL then FREE the Left Subtree  .
		DestroyTree( root -> right );				// If not NULL then FREE the Right Subtree .
		free( root );								// If not NULL then FREE itself .
	}
}

int CountNodes( struct node *root )					// CountNodes() recussive function which counts the number of nodes below the given node including itself .													
{
	if( root == NULL )								// If there is no node then return 0 .
		return 0; 
	
	else
		return CountNodes( root->left ) + CountNodes( root->right ) + 1 ;	// Otherwise return the no of nodes in LEFT Node , Right Node and itself .

}

struct node* Rebuild( struct node * root , int ar[][2] , int a , int b )// Rebuild() construct a new BST from a sorted array and returns the root of reconstructed tree .
																		// It takes a node , sorted array , indicies of sorted array as arguments and returns the root of rebuilt tree .
																		// Sorted array contains 2 columns . 1 column is the value of the elements and other columns is for whether the 
																		// element is deleted or not . 
{
	if( a > b )																// If left index is greater than the right index then return NULL .
		return NULL ;
	
	int mid = (a + b)/2 ;													// Calculating the mid point of indices .

	struct node *temp = (struct node*) malloc ( sizeof( struct node ) ) ;	// Creating a new node and allocating memory to it by malloc . 
	temp -> value = ar[ mid ][0];											// Copying the value of element from arr[mid][0].
	temp -> deleted = ar[mid][1] ;											// Marking whether the node is DELETED or not .
	temp -> parent = root  ;												// Assigning the parent pointer to temp node .
	
	temp -> left  = Rebuild( temp , ar  , a , mid -1 ); 					// Recursive calling Rebuild function to build Left subtree .
	temp -> right = Rebuild( temp , ar  , mid +1 , b );						// Recursive calling Rebuild function to build Right subtree .

	return temp ;															// Returning the BST .
}

void Inordertransversal( struct node *root , int ar[][2] , int *index , int flag  ) // Inordertravelsal() recursive function whuch gives the elemnts in BST in sorted order . The sorted elements
																					// are stord in a array which is passed by calling function . The function takes a flag as an argument .
																					// If FLAG == 0 Insertion FLAG == 1 Deletion 
																					// In Insertion the marked elemnts for deleted also needs to be considered while In Deletion the marked 
																					// elemnts should not be present . Insert is passed by address to increment the position of array . 
{
	if( flag == 0 )																	// Inordertransversal for Insertion .
	{
		if( root == NULL )															// If the node is empty return NULL .
			return;
	
		Inordertransversal( root -> left , ar , index , flag);						// Calling Inorder Travelsal() for Left Node or Subtree .

		ar[ *index ][0] = root -> value ;											// Storing the value of node in array .
		ar[ *index ][1] = root -> deleted ;											// Storing the wheter the node is Marked for deletion or not .
		( *index )++ ;																// Incrementing the value of index .

		Inordertransversal( root -> right , ar , index , flag );					// Calling Inorder Travelsal() for Right Node or Subtree .

	}
	else if ( flag == 1 )															// Inordertransversal for Deletion .		
	{
		if( root == NULL )															// If the node is empty return NULL .
			return;
	
		Inordertransversal( root -> left , ar , index , flag );						// Calling Inorder Travelsal() for Left Node or Subtree .

		if( root -> deleted != 1 )													// Checking the whether node is Deleted or Not .
		{
			ar[ *index ][0] = root -> value ;										// Storing the value of node in array .
			ar[ *index ][1] = root -> deleted ;										// Storing the wheter the node is Marked for deletion or not .
			( *index )++ ;															// Incrementing the value of index .
		}
	
		Inordertransversal( root -> right , ar , index , flag );					// Calling Inorder Travelsal() for Right Node or Subtree .
	}
}

void Insert_Rebuild(  struct node **ins_node, float alpha )		// Insert_Rebuild() takes the node at which the elemnt was inserted and checks from that node to root whther BST
																// is alpha balanced . It rebuilds the first node which  it encounters if it is  not balanced . It takes
																// address of last inserted element( Call by reference) as address and alpha as arguements . It rebuild atmost once .
{
	
	struct node **temp = ins_node ;								// A pointer to iterate from leaf to node to and rebuild the fisrt unbalanced node .		

	int i , n  ;												// i : Variable for Inordertraversal ; n : variable for  No of Nodes 
	
	while( *temp != NULL )										// Checking whether the node is present . 
	{
		n = CountNodes( *temp );								// Counting the number of nodes below the given node (*temp)
		
		if( CountNodes( (*temp) -> left) > alpha * n || CountNodes( (*temp) -> right ) > alpha * n )	// If alpha-balanced condition is not statisfied then rebuild 
		{
			int ar[n][2];										// Array ar for storing the value of element and marking whether the lement is deleted . n is no of nodes for rebuilding .
			i =0 ;												// Intialising i = 0 for Inorder Traversal .
			Inordertransversal( *temp , ar , &i  , 0 );			// Calling InorderTraversal() for the node .
			
			struct node * par = (*temp) -> parent ;				// Storing the parent of node in another temporary parent pointer .

			*temp = Rebuild( *temp , ar , 0 , n-1 );			// Calling Rebuild() to rebuild the subtree at the node .
			
			(*temp) -> parent = par ;							// Storing the parent after rebuildinf from temporary node .
			
			if( par != NULL )									// If the parent is not NULL , then Checking whether to put the rebuilt tree left or right of parent .
			{
				if( par -> value > (*temp) -> value)			// If the value of the parent is more than the root of rebuilt tree 
					par -> left = *temp ;						// Then add it to left of the parent .
				else
					par -> right = *temp ;						// Else add it to right of the parent .									
			}
			
			break;												// If succesfully rebuilt once then break  .
		}
		
		temp = &(*temp) -> parent ;								// Modifying iterating variable .
	}
}

struct node* Delete_Rebuild( struct node *root , int total_nodes , int deleted_nodes )	// Delete_Rebuild() is  used to rebuild the entire BST when the number of marked nodes is more
																						// than half the total number of nodes in BST . Delete_Rebuild() takes root of BST , total no of nodes
																						// and no of marked nodes as argument and returns the pointer of newly built tree . 
{
	int i = 0 ; 								// Intialising i = 0 for Inorder Traversal .

	int ar[ total_nodes - deleted_nodes ][2] ;	// ar[][] to store the value of nodes in BST and whether they are deleted or not .
	
	Inordertransversal( root , ar , &i , 1);	// Calling InorderTraversal() for the root of BST.

	struct node *temp = Rebuild( root , ar , 0 , total_nodes - deleted_nodes - 1 ); // Calling Rebuild() to rebuild the entire BST at the root .
	temp->parent=NULL;																// Assigning the parent to rebuilt tree .

	DestroyTree(root);																// Destroying BST to FREE space .
	
	return temp ; 																	// Returning rebuilt tree .
}


int Height( struct node *root )			// A Function which takes node as arguement and returns the height of the input node ( Including itself) . 	
{
	if( root == NULL )					// If node is NULL return height as 0 .
		return 0 ;

	else   								
		return ( Height(root -> left) > Height(root -> right) ) ?  ( Height(root -> left) + 1 ): ( Height(root -> right) + 1  ) ;	// Find the height of Left Subtree and height of Right Subtree
																																	// of the input node . The height of node is maximum
																																	// of Left and Right Subtree + 1 . 
}

void Print( struct node *root , int level )		// A recursive function which prints all nodes present in the  same level .
{	
	if( root == NULL )							// If node is NULL return 
		return ;

	if( level == 1)								// If level is 1 print the value of node and also whether it is deleted or not .
	{								
		if( root -> deleted == 1 )				// If node is marked to be Deleted then print Deleted along with value .
			printf("%d (Deleted) ", root -> value );
		
		else 									// Else print the value .
			printf("%d           ", root -> value );
	
	}
	else if( level > 1 )						// If level is more than 1 then Recursively Call itself to print all nodes in same level of BST .
	{
		Print( root -> left  , level - 1 );		
		Print( root -> right , level - 1 );
	}
}

void LevelOrder( struct node *root )			// A function which calls Print() to print all nodes in BST by Levelwise .
{
	int h = Height( root );						// Calucalating the Height of the Node from which the BST needs to be printed .

	for( int i = 1 ; i <= h ; ++i )				// Iterating from 1 to Height h .
	{
		Print(root , i );						// Calling Print() to print nodes in ith Level of BST .
		printf("\n");							// Printing New line to start printing next level in new line . 
	}
}