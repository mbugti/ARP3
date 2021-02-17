#include "handshake.h"
#include "bitvector.h"
#include "addresstable.h"

//--------------------------------------
//  UTILS FOR STARTING HANDSHAKE
//--------------------------------------

// check if a node is the starting point for the handshake
// 1 if the node is the starting one; otherwise, 0
int hsh_imfirst( char* my_ip )
{
    if( my_ip == NULL )
        return 0;
    
    return ( iptab_get_ID_of( my_ip ) == __HS_START_NODE_ID );
}

// initialize the handshake message
void hsh_init( handshake_t* hsm )
{
    // set the actual version
    strcpy( hsm->version, __ARPNET_VER_ID );

    // set the bitvector
    bv_init( &hsm->available_nodes, iptab_len() ); 
}

//--------------------------------------
//  HANDSHAKE FIRST STEP
//--------------------------------------

// perform the checking of the version; if the version is correct, mark the node as available
// the function returns 1 if the version is ok; 0 otherwise
int hsh_check_availability( node_id my_id, handshake_t* hsm )
{
    // check if the IDs correspond
    if( strcmp( __ARPNET_VER_ID, hsm->version ) != 0 )
        return 0;

    // the node is available
    bv_mark( &hsm->available_nodes, my_id );

    return 1;
}

//--------------------------------------
//  HANDSHAKE SECOND STEP
//--------------------------------------

// update the address table with the informations within the handshake message
void hsh_update_iptab( handshake_t* hsm )
{
    for( int i=0; i<iptab_len(); i++ )
        if( !bv_marked( &hsm->available_nodes, i ) ) iptab_set_unavailable( i );
}