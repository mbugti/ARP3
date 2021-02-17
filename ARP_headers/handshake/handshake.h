#ifndef _HANDSHAKE_H_
#define _HANDSHAKE_H_

#include <string.h>
#include "../bitvector/bitvector.h"
#include "../addresstable/addresstable.h"
#include "version.h"

// ID of the statring node of the handshake
#define __HS_START_NODE_ID 0

// the message to be shared during the handshake
typedef struct {
    char version[__ARPNET_VER_ID_LEN];
    bitvector_t available_nodes;
}
handshake_t;



//--------------------------------------
//  UTILS FOR STARTING HANDSHAKE
//--------------------------------------
/**********************************************//**
* Function to check if a node is the starting node for the handshake
*
* Arguments
*	my_ip - the ip address of the node
*
* Return
*       1 if the node is the starting one; otherwise, 0
**************************************************/
int hsh_imfirst( char* my_ip );



/**********************************************//**
* Function to initialize the handshake message
* sets the version to the current up-to-date version and initializes the available nodes bitvector
*
* Arguments
*	hsm - pointer to the handshake message
*
**************************************************/
void hsh_init( handshake_t* hsm );


//--------------------------------------
//  HANDSHAKE FIRST STEP
//--------------------------------------

/**********************************************//**
* Function to perform checking of the version of the node; 
* if the version is correct, mark the node as available in the bitvector
* An unmarked node is considered as unavailable
* Only the node that receives the message can mark itself as available.
*
* Arguments
*	my_id - the id of the current node
*	hsm - pointer to the handshake message
*   
* Return
*       1 if the version is ok; 0 otherwise
**************************************************/
int hsh_check_availability( node_id my_id, handshake_t* hsm );




//--------------------------------------
//  HANDSHAKE SECOND STEP
//--------------------------------------

/**********************************************//**
* Function to update the address table with the information of available and unavailable nodes contained in the handshake message
*
* Arguments
*	hsm - pointer to the handshake message
**************************************************/
void hsh_update_iptab( handshake_t* hsm );

#endif
