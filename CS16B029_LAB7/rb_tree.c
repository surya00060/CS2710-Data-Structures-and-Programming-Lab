//This program has function defenitions for function and structures defined in rb_tree.h .
//The main objective of the assignment is to create a  Red Black Tree and do dictionary operations .
//

#include"rb_tree.h"						// Including the header file .

tree* Intialise()						// Intialise() allocates space (malloc) to Tree T and returns the pointer to allocated memory . It also create a Nil pointer for every Tree intialised.
										// Nil is node of tree which stores NULL(Junk) value and is colored black . All NULL pointers are now pointed/replaced to Node Nil . 
										// Children of any Leaf and parent of root is Nil pointer . Using Intialise many Red Black Trees can be created in same program .
										// Intialise() returns the pointer of Tree T.
{
	tree *NewTree;										// Declaring a variable NewTree of data type Structure Tree to store the root and Nil pointer . 
	node *temp ;										// A temporary node temp to allocate memory for Nil pointer . 

	NewTree = (tree*)malloc( sizeof( tree ));			// Using malloc to allocate memory to Tree T .

	temp = NewTree -> Nil = (node*)malloc(sizeof(node));	// Using malloc to allocate memory to Tree T's Nil Node .
	temp -> parent = temp -> left = temp -> right = temp ;	// Nil node's left , right and parent poinrs to itself .
	temp -> color = BLACK ;									// Nil node is colored BLACK .
	temp -> value = -1 ;									// Nil stores some negative or junk value

	NewTree -> root = NewTree->Nil ;						// Making Tree T's root same as Tree T's Nil for intialising .(ie) To make the Root Nil .

	return NewTree ;										// Returning the NewTree after allocating space and initialising root and Nil pointer .
}

void RightRotate( tree *t , node *y )				// RightRotate() rotates the given Node towards rightside in tree t .(ie) It moves the given node y into right subtree and makes node x from 
													// Left Subtree as its parent . This makes the parent of x to be parent of y , parent of y to be x and modifies the left and right subtrees
													// to follow the Binary Search Property . The rotation doesnot modify the coloring of the nodes .  
{
	node* x = y -> left ;							// Node x the left child of y . 

	y -> left = x -> right ;						// Making the right children of x as left children of y . 

	if( x -> right != t->Nil )						// If x's right children is not Nil then making the parent of it to be y .
		x -> right -> parent = y ;
	
	x -> parent = y -> parent ;						// Making x's parent to be parent of y .
	
	if( y -> parent ==  t->Nil )					// If y's parent is Nil (ie) y is the root of tree 
		t->root = x ;								// then making the x as the root of tree .
	
	else if( y == y -> parent -> right )			// if y is right children of its parent
		y -> parent -> right = x ;					// then making x as the right children . (ie) modifying the pointer from parent of x to x .
	
	else
		y -> parent -> left = x ;					// else making x as the left children .

	x -> right = y ;								// Making y as right children of x .
	y -> parent = x ;								// Makining x as parent of y .
	
}

void LeftRotate( tree *t , node* x )				// LeftRotate() rotates the given Node towards leftside in tree t .(ie) It moves the given node x into Left Subtree and makes node y from 
													// Rightt Subtree as its parent . This makes the parent of y to be parent of x , parent of x to be y and modifies the left and right subtrees
													// to follow the Binary Search Property . The rotation doesnot modify the coloring of the nodes .  
													// LeftRotate() code is same as RightRotate with x and y interchanged . 
{
	node* y = x -> right ;							// Node y the right child of x .

	x -> right = y -> left ;						// Making the left children of y as right children of x . 
	
	if( y -> left != t -> Nil )						// If y's left children is not Nil then making the parent of it to be x .
		y -> left -> parent = x ;

	y -> parent = x -> parent ;						// Making y's parent to be parent of x .
	
	if( x -> parent ==  t->Nil )					// If x's parent is Nil (ie) x is the root of tree 
		t ->root = y ;								// then making the y as the root of tree .

	else if( x == x -> parent -> left )				// if x is left children of its parent
		x -> parent -> left = y ;					// then making y as the left children . (ie) modifying the pointer from parent of x to x .
	else
		x -> parent -> right = y ;					// else making y as the right children .
	
	y -> left = x ;									// Making x as left children of y .
	x -> parent = y ;								// Makining y as parent of x .
	
}

node* Search( tree *t , int element )	// Search() takes the Tree T and element to be searched as arguements and return the pointer to the element if it is present in Red Black Tree T .
										// The function uses BST property to search for the elemnt from root to leaf . If the element is not present it returns Nil .
{
	node *temp = t->root;				// A temporary node to store the root of tree and iterate to reach till the element is found .
	
	while( temp != t->Nil )				// Iterate till temporary node becomes Nil .
	{
		if( temp -> value == element )	// If temporary node is the required node then return the address to it .
			return temp ;
		
		else if ( temp -> value > element )	// If the value of element is less than current node then Search in Left SubTree , 
			temp = temp -> left ;
		
		else
			temp = temp -> right ;			// Else search in Right SubTree .
	}

	return t->Nil ;							// If not found return the Nil pointer .
}

void RB_Insert( tree *t , int element )	//RB_Insert() takes tree T and element to be inserted as arguements and inserts the element into Red BLack Tree and calls the function
										//RB_Insert_Recolor to recolor the node caused due to the insertion of red node whenb parent of inserted node is also red .
										//Inserted node is always RED if not it violates the RED Black Tree Property . 
{
	node *z = (node*) malloc( sizeof(node));  	// Creating a new node for the element to be inserted .
	z -> value = element ;						// Copyng the element to be inserted .
	z -> color = RED ;							// Making the color of node to be RED .
	z -> right = z -> left = z -> parent = t->Nil ;	// Making the parent , left and right node to be Nil .

	node *y = t->Nil;							// Temporary pointer for storing the parent while iterating from root to leaf .
	node *x = t->root ;							// Temporary pointer for root to iterate till the leaf of Red Black Tree .

	while( x != t->Nil )						// Checking whther the temporary variable reached the leaf
	{
		y = x ;									// Updating the parent for each iteration .
		if( element < x -> value )				// Following Binary Search Property 
			x = x -> left ;
		else if( element > x -> value )
			x = x -> right ;
		else 									// If the element is already found , Do nothing .
			return;
	}	
	
	z -> parent = y ;							// Parent pointer of the node to be inserted .

	if( y == t->Nil )							// If y is Nill then z is the root of tree T .
		t->root = z ;
	else if( element < y -> value )				// else following Binary Search Property .
		y -> left = z ;
	else 
		y -> right = z ;

	z -> left = t->Nil ;						// Making the left and right of new inserted node as Nil .
	z -> right = t->Nil ;
	z -> color = RED ;							// Inserted node is always RED in color .
	RB_Insert_Recolor(t,z);  					// Calling RB_Insert_Recolor to fixup color changes due to insertion of Red Node .
}

void RB_Insert_Recolor( tree *t , node * x )	// This function recolors the node and fix up the tree so that tree T follows RB properties .It is called by RB_Insert().
												// Inserted node is always Red in color . If the parent of inserted node is black then there is no violation in Red Black Tree Properties .
												// If the parent of inserted node is Red , then there is 2 consecutive red node which violates the red Black Property .
												// Since the inserted node is Red and parent is also Red , the grandparent of the inserted node is Black .
{												// Case 1 : parent is Black in color .
	while( x -> parent -> color == RED )		// Case 2 : Parent of inserted node is Red in color . Grandparent is Black in color .
	{
		node *y = t->Nil ;					

		if( x -> parent == x -> parent -> parent -> left )	// Case:2.1 If parent of x is the left Children of grandparent of x 
		{
			y = x -> parent -> parent -> right ;			// Then right children of grandparent of x is the uncle of x which is y .				
	
			if( y -> color == RED )							// Case: 2 . 1 . 2  If the Uncle is Red in color 					
			{
				x -> parent -> color = BLACK ;						// Then Recolor the parent , uncle and grandparent .
				y -> color = BLACK ;
				x -> parent -> parent -> color = RED ;
				x = x -> parent -> parent ;							// Make the grandparent as x and recursively undergo the RB_Insert_Recolor till there is color balncd
			}
			else 											// Case: 2.1.1 If the Uncle's color is BLACK 
			{
				
				if( x == x -> parent -> right )				// Case: 2.1.1.1 If x is right children
				{
					x = x -> parent ;						// Make x as its parent and Left Rotate about new x . And it becomes Case:2.1.1.2
					LeftRotate( t , x ) ;	
				}
				x -> parent -> color = BLACK ;				// Case: 2.1.1.2 If x is left Children 
				x -> parent -> parent -> color = RED ;			
				RightRotate( t , x -> parent -> parent );	// Recolor and do Right Rotation .
			}					
		}
		else 												// Same as the above cases with left and right interchanged .
		{
			y = x -> parent -> parent -> left ;					
	
			if( y->color == RED )
			{
				x -> parent -> color = BLACK ;
				y -> color = BLACK ;
				x -> parent -> parent -> color = RED ;
				x = x -> parent -> parent ;
			}
			else 
			{
				
				if( x == x -> parent -> left )
				{
					x = x -> parent ;
					RightRotate( t ,x ) ;
				}
				x -> parent -> color = BLACK ;
				x -> parent -> parent -> color = RED ;
				LeftRotate( t , x -> parent -> parent );
			}					
		}
	}
	t->root -> color = BLACK ;								// Root of the Tree T is Black in color . 
}

node* FindMin( tree *t , node * temp )	// FindMin() takes tree T and node as arguements and returns minimum elemnet under the given node in tree T which lies to left of the given node .
										// The leftmost element in right Subtree is minimum element in the right subtree by the property of Binary Search Tree . Red Black Tree
										// also follows the BST property .
{
	if( temp != t->Nil )				// Checking whether the given node is Nil .
	{	
		while( temp ->left != t->Nil )	// Checking the leftmost element in the given Tree is Nill . 
			temp = temp -> left;		// If not Nil then moving towards Left Subtee .
	return temp ;						// If Minimum element is found return the pointer to that element .
	}
	return t->Nil ;						// Else return Nil if not found .
}

void RB_Transplant( tree *t , node *u , node *v) 	//RB_Transplant() takes Tree T and two nodes u and v as input arguements . It swaps the node u with v .(ie) It replaces node u with v .
													//It swaps the node u with node v and changes its parent pointers also in tree T .This function will be called by RB_Delete. 
{
	if( u -> parent == t->Nil )						// If the node to be replaced is root, 
		t->root = v ;								// then making the v to be root of the tree
	
	else if( u == u -> parent -> left )				// if u is the left children then making left children of u's parent as v .
		u -> parent -> left = v ;
	
	else
		u -> parent -> right = v ;					// Else making v as the right children.

	v -> parent = u -> parent ;						// Also making parent of v as parent of u .
}

void RB_Delete( tree *t , int element )			//RB_Delete() deletes the node from Red Black Tree and fixes the color changes . It calls RB_Delete_Recolor to fixup changes . It takes the lement to 
												// be deleted as arguement and tree T . In deletion there are only two cases . Deleting a node with no children(Leaf) or with one children.
												// A node to be deleted with two children can be reduced to one of the cases above . 
{
	node *z = Search( t, element );				// Finding the node to be deleted by searching whethere the element is present in tree T or not .
	
	if( z == t->Nil )							// If not present then no deletion happens .
		return ;
	
	node *x ;									// Temporary node  
	node *y = z ;								// Temporary node pointing to the element to be deleted .

	int y_color = y -> color ;					// Storing the color of element .

	if( z -> left == t->Nil )					// If the left child of the node is Nil	
	{
		x = z -> right ;
		RB_Transplant( t , z , z -> right );	// Calling Transplant() to replace z by z's right children . 
	}
	else if( z -> right == t->Nil )				// If right child of the node is Nil
	{
		x = z -> left ;
		RB_Transplant( t, z , z -> left );		// Calling Transplant() to replace z by z' left children .
	}
	else 										// If node to be deleted has two children
	{
		y = FindMin( t , z -> right );			// Then we swap the node to be deleted with Least element or LeftMost Child in right SubTree to follow the Binary Search Property . y has now only one children
												// or no children .
		
		y_color = y -> color ;					// Storing the color of least element in right subtree .
		
		x = y -> right ;						// Making x as right child of y .
		
		if( y -> parent == z )					// If y is children of z 
			x -> parent = y ;					

		else
		{
			RB_Transplant( t, y , y -> right ); // Else transplanting y and its right children .
			y -> right = z -> right ;
			y -> right -> parent = y ;
		}
		RB_Transplant( t, z , y );				// Calling transplant to to swap the element to be de;eted by its replacement .
		y -> left = z -> left ;					// Storing the left children of z in y .
		y -> left -> parent = y ;				// Modifying the parent pointer
		y -> color = z -> color ;				// Modifying the color pointer .
	}
	if( y_color == BLACK )						// If the color of the node to be deleted in BLACK we call RB_Delete_Recolor to fix up the tree.
			RB_Delete_Recolor( t , x);
}


void RB_Delete_Recolor( tree *t , node *x )	// This function fixes the color changes due to Deletion of Black nodes . Deletion of Red Nodes doesnot need to be fixed up this function .
{

	node *y= t->Nil ;

	while( x!= t->root && x -> color == BLACK ) // Checking if x is the root and it is colored BLACK .
	{	
		if( x == x -> parent -> left )			// Case 1: x is left child of its parent 
		{
			y = x -> parent -> right ;			// Sibling of x is the right child of its parent .
			
			if( y ->color == RED )				// Case : 1.2  Sibling of x is red in color .
			{
				y -> color = BLACK ;			// Do recoloring and LeftRotate to get the tree which reduces to Case 1.1.4 	
				x -> parent -> color = RED ;
				LeftRotate( t , x -> parent );
				y = x -> parent -> right ;
			}
			if( y ->left->color == BLACK && y->right->color == BLACK )	// Case : 1.1.4 If the children of Sibling is colored BLACK and Sibling is colored BLACK .
			{
				y -> color =  RED ;				// Recolor the sibling to fix up the tree  and make x as its parent to check the whole tree .
				x = x -> parent ;
			}
			else        						// Case 1.1 Color of Sibling is Black in color 
			{	
				if( y->right->color == BLACK )	// Case 1.1.3 Right Children of Sibling is Black in color 
				{
					y -> left -> color = BLACK;		// Recolor and do RightRotation and it reduces to case 1.1.1
					y -> color = RED ;
					RightRotate( t , y );
					y = x -> parent -> right ;
				}
				y->color = x -> parent -> color;	// Case 1.1.1 : Left Children of Sibling is black in color . Case 1.1.2 : Both Children are Red in color .
				x-> parent -> color = BLACK ;		// Do leftrotaton
				y -> right -> color = BLACK ;
				LeftRotate( t , x->parent);
				x=t->root;							// Making x as root to stop iterating .
			}
		}
		else 										// Same as above with left and right interchanged .
		{
			y = x -> parent -> left ;
			if( y -> color == RED )
			{
				y -> color = BLACK ;
				x -> parent -> color = RED ;
				RightRotate( t , x -> parent );
				y = x -> parent -> left ;
			}
			if( y -> left -> color == BLACK && y -> right -> color  == BLACK )
			{
				y -> color =  RED ;
				x = x -> parent ;
			}
			else
			{

				if( y -> left->color  == BLACK )
				{
					y -> right -> color = BLACK;
					y -> color = RED ;
					LeftRotate( t , y);
					y = x -> parent -> left ;
				}
				y->color= x -> parent -> color;
				x-> parent -> color = BLACK ;
				y -> left -> color = BLACK ;
				RightRotate( t , x->parent);
				x=t->root;
			}
		}
	}
	x->color=BLACK;							// Making the color of x to to be black when it fails the loop .(ie) making root as colored black .		
}


int Height(node* temp , node* empty)	// A Function which takes node and Nil  as arguement and returns the height of the input node ( Including itself) . 	
{
	if( temp == empty )					// If node is Nil return height as 0 .
		return 0 ;

	else   								
		return ( Height(temp -> left , empty) > Height(temp -> right , empty) ) ?  ( Height(temp -> left,empty) + 1 ): ( Height(temp -> right,empty) + 1  ) ;	// Find the height of Left Subtree and height of Right Subtree
																																	// of the input node . The height of node is maximum
																																	// of Left and Right Subtree + 1 . 
}

void Print( node *temp ,node *empty , int level )// A recursive function which prints all nodes present in the  same level .
{	
	if( temp == empty )							// If node is NULL return 
		return ;

	if( level == 1)								// If level is 1 print the value of node and also the color of node .
	{								
		if( temp -> color == RED )				// All nodes in Red Black tree os colored either red or black and they are printed along with color  .
			printf("%d (RED)   ", temp -> value );
		
		else 									
			printf("%d (BLACK) ", temp -> value );
	
	}
	else if( level > 1 )						// If level is more than 1 then Recursively Call itself to print all nodes in same level of BST .
	{
		Print( temp -> left , empty , level - 1 );		
		Print( temp -> right , empty , level - 1 );
	}
}

void LevelOrder( tree *t )						// A function which calls Print() to print all nodes in RED BLACK TREE by Levelwise with color in parenthisis .
{
	node* temp = t->root ;						// A temporary variable to store the root of tree .
	int h = Height( temp , t->Nil );			// Calucalating the Height of the Node from which the Red Black Tree needs to be printed .

	for( int i = 1 ; i <= h ; ++i )				// Iterating from 1 to Height h .
	{
		Print( temp , t->Nil , i );				// Calling Print() to print nodes in ith Level of BST .
		printf("\n");							// Printing New line to start printing next level in new line . 
	}
}

void DestroyTree( tree *t)			// DestroyTree() takes the Tree T as arguements and frees memory allocated to all nodes and also to root and Nil pointer .	
									// It calls DestroyAllNodes to destroy all nodes in tree T .
{
	DestroyAllNodes( t->root , t -> Nil );	// Calling function DestroyAllNodes to free the memory allocated to all nodes by malloc .We pass the root and Nil pointer . 
	//free( t-> root );						// Free the memory of root pointer of Tree T .
	free( t -> Nil );						// Free the memory of Nil pointer of Tree T allocated by malloc.
}

void DestroyAllNodes( node *t , node *Nil )	// DestroyAllNodes Tree t. This function is same as the one used in BST but uses extra Nil pointer as arguement . 
{
	if( t != Nil )								// Checking whether the node is Nil .
	{
		DestroyAllNodes( t -> left , Nil );		// If not Nil the free the LeftSubtree .
		DestroyAllNodes( t -> right , Nil );	// And free the Right Subtree .
		free(t);								// And free the node .
	}
}