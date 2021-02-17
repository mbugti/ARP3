#ifndef _ADDRESSTABLE_SIMPLE_H_
#define _ADDRESSTABLE_SIMPLE_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define __IP_TABLE_LEN 4

#define __NOD_AVAILABLE 1
#define __NOD_NOT_AVAILABLE 0

typedef uint8_t node_id; // essentially a char, 8bit without sign (0-255)

// the entry of the address table
typedef struct iptab
{
    char ip_addr[15];     /* IP address as cahr vector */
    short ip_avail;       /* 1 if IP address is available for connection */
}
iptab_addr_t;

// ------------------------
//  BASIC OPERATIONS
// ------------------------

// the table is an 'extern' array of (string) IP addresses
extern iptab_addr_t __ip_table[ __IP_TABLE_LEN ];

// the number of available nodes
extern int __ip_table_available_nodes;

/****************************************************************************
* get the total lenght of the table
*
* Return
*	  __IP_TABLE_LEN - It's the length of the IP_table,
                       the total number of nodes;
*****************************************************************************/
int iptab_len();


/****************************************************************************
* Return the IP address (as string) of a specified node.
*
* Inside this function there is a check on n, if it's greater than the IP_table 
* size or if the version of header is not the last released, the function return NULL.
*
* Arguments
*	n - Id number of a node;
*
* Return
*	An IP address as string only if the given node is available
*   otherwise, NULL is returned.
****************************************************************************/
char* iptab_getaddr(node_id n);


/****************************************************************************
* Return the ID of a certain node given its IP address.
*
* Inside this function there is a research in the IP_table to find the correspondent
* ID of the node, the there is a chek on this number to control that the node has the 
* last header version released, if it's correct return the ID otherwise -1.
*
* Arguments
*	ip - IP address of a node;
*
* Return
*	res - The ID of the node, or -1 if the node has not the last released version;
****************************************************************************/
int iptab_get_ID_of(char* ip);



/****************************************************************************
* Return the ID of the next available node(growing order) in the IP_table.
*
* Arguments
*	my - ID of the current node;
*
* Return
*	n - The ID of the next node;
****************************************************************************/
node_id iptab_get_next( node_id my );



// ----------------------------- DEPRECATED -----------------------------
// get the ID of the previous node in the table (in order)
/****************************************************************************
* Return the ID of the previous available node(growing order) in the IP_table.
*
* Arguments
*	my - ID of the current node;
*
* Return
*	n - The ID of the previous node;
****************************************************************************/
//node_id iptab_get_prev( node_id my );
// ----------------------------- DEPRECATED -----------------------------


// ------------------------
//  OPS ON "AVAILABLE" FLAG
// ------------------------

/****************************************************************************
* Return the number of available addresses in the IP_table.
*
* Return
*	__ip_table_available_nodes - Number of available addresses in the IP_table;
****************************************************************************/
int iptab_len_av();


/****************************************************************************
* Check if the IP address of a given node is available.
*
* Inside the function there is a check on the ID of node passed, it should be a   
* positive number greater than zero and lower than the IP_table length.
*
* Arguments
*	 n - ID of a node;
*
* Return
*	 1 - if the IP address correspondent to the given ID of the node is available;
*    0 - otherwise
****************************************************************************/
int iptab_is_available(node_id n);


/****************************************************************************
* Set unavailable the IP address correspondent to the given ID of the node 
*
* Inside the function there is a check on the ID of node passed, it should be a   
* positive number greater than zero and lower than the IP_table length.
* Set the correspondent IP address unavailable and decrement the number of available
* IP addresses.
*
* Arguments
*	 n - ID of a node;
*
* Return
*	 0 - correspondent IP address set unavailable;
*    -1 - if the passed n is not valid to identify a node
****************************************************************************/
int iptab_set_unavailable(node_id n);


/****************************************************************************
* Set available the IP address correspondent to the given ID of the node 
*
* Inside the function there is a check on the ID of node passed, it should be a   
* positive number greater than zero and lower than the IP_table length.
* Set the correspondent IP address available and increment the number of available
* IP addresses.
*
* Arguments
*	 n - ID of a node;
*
* Return
*	 0 - correspondent IP address set available;
*    -1 - if the passed n is not valid to identify a node
****************************************************************************/
int iptab_set_available(node_id n);


/****************************************************************************
* Set all IP addresses at default status "available" 
*
* Inside the function all IP addresses are set to "available" and the number 
* of total available nodes is set to the total amount of Ip addresses in the IP_table
****************************************************************************/
void iptab_reset_flags();

#endif
