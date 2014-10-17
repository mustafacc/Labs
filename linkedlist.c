/*
 * File:            linkedlist.c
 * Purpose:         Implements the linked list functions whose prototypes
 *                  are declared in the linked_list.h header file
 * Authors:         Matthew Shew and Mustafa Hammood
 * Student Numbers: 48854146 and 29834124	
 * CS Accounts:     i7z9a and x0n8
 * Date:            Add the date here
 */
 
/* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

/*
 Main function drives the program.  Every C program must have one
 main function.  A project will not compile without one.

 In our program, the main function does nothing.  That's because
 our program doesn't do anything.  We're just implementing a linked
 list and testing it using our unit tests.

 PRE:    NULL (no pre-conditions)
 POST:	 NULL (no side-effects)
 RETURN: IF the program exits correctly
		 THEN 0 ELSE 1
 */
int main ( void )
{
	//**************************************************************************************
	//*******************************Intializing...*************************************
	struct airplane test_airplane_one = { 100, "Vancouver", "Toronto", 1, 900, 36000, 350 };
	struct airplane test_airplane_two = { 200, "Toronto", "Halifax", 2, 800, 26000, 280 };
	struct airplane test_airplane_three = { 300, "Vancouver", "Dubai", 3, 700, 3900, 400 };

	struct node * test_list = create_linked_list();
	struct node * test_node = create_linked_list();

	test_node = prepend_node( test_node, create_node(test_airplane_three) );
	test_list = prepend_node( test_list, create_node(test_airplane_one) );
	test_list = prepend_node( test_list, create_node(test_airplane_two) );
	//**************************************************************************************
	//**************************************************************************************

	printf( "**********************************\n");
	printf( "Testing print_node...\n" );
	print_node( test_node );	//Testing print_node
	printf( "**********************************\n" );
	printf( "**********************************\n" );
	printf( "\n\n" );

	printf( "**********************************\n");
	printf( "Testing print_list...\n" );
	print_list( test_list );	//Testing print_list
	printf( "**********************************\n");
	printf( "**********************************\n");
	printf( "\n\n" );

	/* The system command forces the system to pause */
	system(  "pause");
	return 0;
}

/*
 Returns a pointer to a new, empty linked list of struct node.
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a new, empty linked list of struct node (NULL)
 */
struct node * create_linked_list()
{
	struct node *pointer;

	pointer = NULL;

	return pointer;

	// or just return null;
}

/*
 Returns a dynamically allocated struct node that contains the specified
 struct airplane.  The node's next pointer doesn't point to anything
 e.g., it is equal to NULL.
 PARAM:     plane, a struct airplane
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a dynamically allocated struct node a) that contains
            the specified struct airplane, and b) whose next pointer points to NULL
 */
struct node * create_node(struct airplane plane)
{
	
	struct node *pointer;
	pointer = (struct node*)malloc(sizeof(struct node));
	pointer->plane = plane;
	(pointer)->next = NULL;
	return pointer;
	
}

/*
 Prepends a struct node passed as a parameter to the list passed as a
 parameter, and returns a pointer to the result.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     new_node is a pointer to a struct node
 PRE:       new_mode is not null
 POST:      The specified struct node is added to the beginning of the list
            and its next pointer points to the node that used to be first
 RETURN:    A pointer to a linked list which contains all of the nodes
            of the list passed as a parameter, plus a prepended node
 */
struct node * prepend_node(struct node * list, struct node * new_node)
{
		new_node->next = list;
		return new_node;	
}


//****************************************************************************
//*************************Take home assignment*******************************
//****************************************************************************
//***************************VVVVVVVVVVVVVVV**********************************

/*
 Deletes the first struct node in the specified list, and returns a pointer to
 the shortened list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL
 POST:      The list passed as a parameter has one fewer node, and the dynamically
            allocated memory which contained that removed node has been freed
 RETURN:    IF the list is empty
            THEN NULL
            ELSE a pointer to the shortened list
 */
struct node * delete_node(struct node * list)
{
	struct node *pointer;		//The pointer to return

	pointer = list;

	if( !list )					//If the list is empty, return NULL
	{
		return NULL;
	}			
								//Else, a pointer to the shortened list
	pointer = list->next;		//Assign pointer to next node
	free(list);					//Delete the node
	return	pointer;
	

	
}

/*
 Returns the number of nodes in the specified linked list of struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    The length of the specified list, an int
 */
int get_length(struct node * list)
{
	int length = 0;
	struct node *pointer = list;

	if( pointer == NULL )		//IF list is empty (all NULL), return 0
	{
		length = 0;
		return length;
	}

	if( pointer->next == NULL )	//IF list has a single node
	{
		length = 1;
		return length;
	}
								//IF list has more than one
								//Check if next node is NULL, if not add 1 to length and
								//Go to next node
	while( pointer != NULL )	
	{
		length++;
		pointer = pointer->next;
	}

	return length;

}

/*
 Deletes an entire list.  This function iterates along a list and deallocates the
 memory containing each struct node.  
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The memory containing all of the nodes in the list has been freed
 RETURN:    an empty list (NULL)
 */
struct node * delete_list(struct node * list)
{
	while( list != NULL )
		list = delete_node( list );

	return NULL;
}

/*
 Prints the data stored in a node.  For the struct airplane in the node,
 prints the fields on separate lines.  For each field, prints the field name
 and the field value.  For the pointer, prints "Link = NULL\n" if the pointer points
 to null, else prints "Link points to address xxx\n", where xxx is the pointer address
 in hexademical.
 If node_to_print is NULL, prints "The node is empty\n".
 PARAM:     node_to_print is a pointer to a (possibly null) struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about node_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_node(struct node * node_to_print)
{
	struct node *pointer = node_to_print->next;
	int i = 0;

	//****************************Printing the address*************************************
	if( node_to_print == NULL )					//If node is empty
	{
		printf( "\nThe node is empty.\n" );
	}
	if( pointer == NULL )						//If node is only a single one
	{
		printf( "\nLink = NULL\n" );
	}
	else
	{
		printf( "\nLink points to address %x\n", pointer );
	}
	//**************************************************************************************
	
	printf( "\nFlight Number is %d \n", node_to_print->plane.flight_number );

	//************************Printing city_origin********************************
	printf( "City of origin is: " );
	//Loop to print each letter of the array
	while( *(node_to_print->plane.city_origin +i) != '\0' )
	{
		printf( "%c", *(node_to_print->plane.city_origin +i));
		i++;
	}
	printf( "\n" );
	//****************************************************************************

	//*************************Printing city_destination**************************
	i = 0;	//reset counter to 0
	printf( "Destination city is: ");
	//Loop to print each letter of the array
	while( *(node_to_print->plane.city_destination +i) != '\0' )
	{
		printf( "%c", *(node_to_print->plane.city_destination +i));
		i++;
	}
	printf( "\n" );
	//*****************************************************************************

	printf( "Flight priority is: %d\n", node_to_print->plane.priority );
	printf( "Maximum speed of the flight is: %d\n", node_to_print->plane.maximum_speed_kph );
	printf( "Cruising altitude of the flight is: %d\n", node_to_print->plane.cruising_altitude );
	printf( "Flight capacity is: %d\n", node_to_print->plane.capacity );

}

/*
 Prints the data stored in all nodes in the specified list to print.
 For each node, prints the data inside the node the same way that it
 is printed by print_node.  If the list is empty, a suitable message
 is printed to standard output.
 PARAM:     node_to_print is a pointer to a (possibly empty) linked list of
            struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about list_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_list(struct node * list_to_print)
{
	if( list_to_print == NULL )
	{
		printf( "\nERROR: List is empty.\n");
	}
	while( list_to_print != NULL )
	{
		print_node( list_to_print );

		list_to_print = list_to_print->next;

		if( list_to_print != NULL )
			printf( "\n******Next Node...******\n" );
	}
}

/*
 Reverses a list. 
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The order of the nodes in the list passed as a parameter has been
            reversed
 RETURN:    a list of struct node that is the reverse of the list passed as a
            parameter
 */
struct node * reverse(struct node * list)
{
	struct node *pointer = list;

	if( list == NULL )		//Empty list
		return list;		

	if( list->next == NULL ) //List with one node, can't be reversed
		return list;
	else
	{
		while( pointer->next != NULL )
		{
			if( pointer->next == NULL )
			{
				list = pointer;
			}
			pointer = pointer->next;
		}
		return list;
	}

}

/*
 Removes every node from the list which contains an airplane destined for
 the city name passed in the second parameter.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     destination_city is a pointer to a null-terminated array of char
 PRE:       NULL (no pre-conditions)
 POST:      Any struct node in the list which contains an airplane struct
            destined for the destination_city is removed from the list, and
            the memory deallocated
 RETURN:    a list of struct node that does not contain any struct node that
            has an airplane destined for the destination_city
 */
struct node * remove_from_list(struct node * list, char * destination_city)
{
	struct node *pointer = list;
	struct node *temp = list;

	while( pointer != NULL )
	{
		if( *(pointer->plane.city_destination) == *destination_city )
		{
			temp = pointer;		
			free( pointer );
			pointer = temp;
		}
		pointer = pointer->next;
	}

	return list;
}

/*
 Returns a reference to the nth node (but does not remove it ) in the
 specified list.  If the list is too short, returns NULL.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list
            THEN a pointer to the nth node
            ELSE NULL
 */
struct node * retrieve_nth(struct node * list, int ordinality)
{
	struct node* pointer = list;
	int length = get_length(list);
	int count = 0;

	if( ordinality > length )
		return NULL;
	else
	{
		while( pointer != NULL );
		{
			if( count == ordinality )
				return pointer;
			else
			{
			count++;
			pointer = pointer->next;
			}
		}
	}
}

/*
 Inserts the specified node into the specified list of nodes at the specified
 ordinality.  For example, if ordinality = 1, this is a simple prepend_node
 operation.  If ordinality = 3, then when this function is finished, the third
 node in the list will be the node_to_insert.  If the ordinality = the length
 of the list + 1, then the node_to_insert is appended to the end of the list.
 If the ordinality > 1 + length of the list, the function returns a pointer
 to the unchanged list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 PRE:       node_to_insert is NEVER a null (it is always a correct node pointer)
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list + 1
            THEN a pointer to the list which contains the node_to_insert in the
			correct location
            ELSE a pointer to the unchanged list
 */
struct node * insert_nth(struct node * list, struct node * node_to_insert, int ordinality)
{
	// Insert your code here
}