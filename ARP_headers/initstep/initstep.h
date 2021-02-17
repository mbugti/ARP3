#ifndef _VOTATION_H_
#define _VOTATION_H_
#include "../addresstable/addresstable.h"
#include "../misc/random_index.h"

// the type of the message reserved to the votation
typedef struct votation_message
{
    node_id voted_node;
}
votation_t;




/**********************************************//**
* Function to initialize the votation message. 
* This function should be called only by the starting node (previous turn leader)
* then this node should call vote_do_votation function immediately after to insert its choice
*
* Arguments
*	msg - pointer to the votation message of type votation_t
*
**************************************************/
void vote_init( votation_t* msg );




/**********************************************//**
* votation function
* This function should be called by each node for making the votation
* It chooses randomly a node id and adds its choice to the votation message
*
* Arguments
*	msg - pointer to the votation message of type votation_t
*
**************************************************/
void vote_do_votation( votation_t* msg );





/**********************************************//**
* Function to get the winner of the votation cycle
* This function should be called only in the end of the votation cycle by the starting node (previous turn leader)
* then this node should notify the winner
*
* Arguments
*	msg - pointer to the votation message of type votation_t
*
* Return
*       the node_id of the winner node (the next turn leader)
        or -1 if no other id is available in the network (just to be safe)
**************************************************/
node_id vote_getWinner( votation_t* msg );

#endif
