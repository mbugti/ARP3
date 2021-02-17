#include "initstep.h"

/* (starting node) initialization of the votation message
	simply put the 0 node as the voted one, the node calling
	this function should always call vote_do_votation immediately
	after to insert its choice
*/
void vote_init( votation_t* msg )
{
    msg->voted_node = 0;
}


/* votation function: it generates a random node_id among the
	existing ones, adds it to the previous value inserted and 
	computes the modulo by the number of nodes (table length).
	Since we have a sum of *len* values between 0 and *len*,
	all modulo *len* (performing the modulo at the end or at each
	step is mathematically equivalent, but by doing it at each step
	we can spare space)
*/
void vote_do_votation( votation_t* msg )
{
	int len = iptab_len();
    node_id n = rdmindex(0, len);
    msg->voted_node = (msg->voted_node + n) % len;
}

// which is the lucky node?
node_id vote_getWinner( votation_t* msg )
{
	/*
		// OLD VERSION
		return msg->voted_node
	*/
    // get the "nominal" winner
	node_id winner = msg->voted_node;
	node_id check = winner;
	
	// then take the next until the winner is an available node
	// if possible
	while( ! iptab_is_available( winner ) )
	{
		winner = ( winner + 1 ) % iptab_len();
		if( winner == check )
		{
			winner = -1;
			break;
		}
	}

	// then return it, or return -1
	return winner;
}

