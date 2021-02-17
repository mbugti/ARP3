#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <time.h>
#include <sys/time.h>
#include "../bitvector/bitvector.h"
#include "../addresstable/addresstable.h"
#include "../misc/random_index.h"

// format of the message shared with the nodes of the network
typedef struct message
{
	node_id id;				/* the ID of the sender node */
	node_id turnLeader;		/* the ID of the actual turn leader */
	struct timeval recvd;	/* time instant in which the sender received the previous message */
	struct timeval sent;	/* time instant in which this message was sent */
	bitvector_t vis_set;	/* flags for visited nodes */
}
message_t;

/************************************************************************//**
* Initilize a given message.
*
* Inside this function all fields of the message are initialized to default values. 
* Default value -1 for ID of the sending node and ID of the turn leader.
* Default value 0 for sending and receiving times
*
* Arguments
*	msg - The message to be initialized;
*
****************************************************************************/
void msg_init( message_t* msg );


/************************************************************************//**
* Set receiving time in a given message.
*
* Arguments
*	msg - The message within modify the receiving time;
*
****************************************************************************/
void msg_set_recv( message_t* msg );


/************************************************************************//**
* Set sending time in a given message.
*
* Arguments
*	msg - The message within modify the sending time;
*
****************************************************************************/
void msg_set_sent( message_t* msg );


/************************************************************************//**
* Set ID of sending node and ID of the turn leader in a given message.
*
* Arguments
*	msg - The message within modify ID of sending node and turn leader;
*	id - ID of the sending node;
*	turn_leader - Id of the current turn leader;
*
****************************************************************************/
void msg_set_ids( message_t* msg, node_id id, node_id turn_leader );


/************************************************************************//**
* Check if a node was already visited.
*
* Inside this function there is a check on n and then a bv_marked() is performed 
* in order to check if a node is already visited.
*
* Arguments
*	msg - msg to check;
*	n - ID number of a node;
*
* Return
*	1 - if the given node is already visited 
*	0 - if the given node is  not already visited 
* 	-1 - if ID of the node is not valid
*
****************************************************************************/
int msg_visited( message_t* msg, node_id n );


/************************************************************************//**
* Return how many nodes were already visited.
*
* Inside the function, for each node, a "message_visited()" is performed in order
* to chek if a single node was already visited or not.
*
* Arguments
*	msg - msg to check;
*
* Return
*	n_visited - number of visited nodes
*
****************************************************************************/
int msg_numberVisited( message_t* msg);


/************************************************************************//**
* Mark a a given node as visited in the message.
*
* Inside the function there is a chek on n and then a "bv_mark()" is performed 
* in order to mark the node as marked in the right field of the message.
*
* Arguments
*	msg - msg to check;
*	n - ID of the node to mark
*
****************************************************************************/
void msg_mark( message_t* msg, node_id n );


/************************************************************************//**
* Check if there are unvisited nodes.
*
* Inside this function a bv_all_marked() is performed in order to check if there 
* are unvisited nodes.
*
* Arguments
*	msg - The message to check
*
* Return
*	0 - There is at least one node not visited yet
*	1 - All nodes are visited.
*
****************************************************************************/
int msg_all_visited( message_t* msg );


/************************************************************************//**
* Choose randomly an unvisited node, without marking the returned index within the message.
*
* Inside this function a bv_all_marked() is performed in order to check if there available node,
* otherwise return -1.
* Then a vector idx is filled with all unvisited nodes, performing "bv_marked()" and 
* "iptab_is_available()". 
* Finally a random node is chosen among the element of this vector.
*
* Arguments
*	msg - The message within to choose the next node 
*
* Return
*	idx[n] - ID of the randomly chosen node (or an error code)
*	
****************************************************************************/
int msg_rand( message_t* msg );


/************************************************************************//**
* Return the value in the field "turnLeader" of the message passed as 
* argument
*
* Arguments
*	msg - The message we are interested in
*
* Return
*	turnLeader - ID of the current Turn Leader
*	
****************************************************************************/
node_id msg_get_turnLeader( message_t* msg );


/************************************************************************//**
* Get receiving time in a given message.
*
* Arguments
*	msg - The message from which to get the receiving time;
*
****************************************************************************/
struct timeval msg_get_recv( message_t* msg );


/************************************************************************//**
* Set sending time in a given message.
*
* Arguments
*	msg - The message from which to get the sending time;
*
****************************************************************************/
struct timeval msg_get_sent( message_t* msg );

#endif
