#include "message.h"

// initialize the message
void msg_init( message_t* msg )
{
    msg->id = -1;
    msg->turnLeader = -1;

    msg->recvd.tv_sec = 0;
    msg->recvd.tv_usec = 0;

    msg->sent.tv_sec = 0;
    msg->sent.tv_usec = 0;

    bv_init( &msg->vis_set, iptab_len() );
}

// set receiving time time
void msg_set_recv( message_t* msg )
{
    gettimeofday( &(msg->recvd), NULL );
}

// set the sending time
void msg_set_sent( message_t* msg )
{
    gettimeofday( &(msg->sent), NULL );
}

// set id and turn leader
void msg_set_ids( message_t* msg, node_id id, node_id turn_leader )
{
    msg->id = id;
    msg->turnLeader = turn_leader;
}

// check if a node was already visited
// EDIT: now returns -1 if index is out of bound
int msg_visited( message_t* msg, node_id n )
{
    if( n > iptab_len() || n < 0 )
        return -1;

    if( bv_marked( &msg->vis_set, n ) )
        return 1;
    else
        return 0;
}

// returns the number of visited nodes
int msg_numberVisited( message_t* msg)
{
	int n_visited = 0;

	for(node_id i=0; i<iptab_len(); i++)
    {
			n_visited+=msg_visited(msg, i);
			// +1 if node 'i' has been visited, +0 else
			// don't check for error since indexes are
			// always well defined in this loop
	}
	return n_visited;
}

// mark a node as visited
void msg_mark( message_t* msg, node_id n )
{
    if( n > iptab_len() || n < 0 ) return;
    bv_mark( &msg->vis_set, n );
}

// check if there are unvisited nodes
int msg_all_visited( message_t* msg )
{
    return bv_all_marked( &msg->vis_set );
}

// choose randomly an unvisited node, without marking the returned index in the message
int msg_rand( message_t* msg )
{
    if( bv_all_marked( &msg->vis_set ) ) return -1;

    const int len = iptab_len();
    node_id idx[len];
    int max = 0;

    // initialize the mapping (probably useless, just for reliability of the returned value)
    for( int k=0; k<len; k++ ) idx[k] = -1;

    // search for available indices and count them
    // EDIT: now it is checked if the node is available
    for( int j = 0, k=0; k<len; k++ )
        if( !bv_marked( &msg->vis_set, k ) && iptab_is_available( k ) )
        {
            idx[j] = (node_id) k;
            max++;
            j++;
        }

    // get the random index
    int n = 0;
    if( max > 1 )
        n = rdmindex(0, max-1);

    return idx[n];
}
// get the turnLeader field
node_id msg_get_turnLeader( message_t* msg ){
	return msg->turnLeader;
}

// get receiving time time
struct timeval msg_get_recv( message_t* msg )
{
    return msg->recvd;
}

// get the sending time
struct timeval msg_get_sent( message_t* msg )
{
    return msg->sent;
}
