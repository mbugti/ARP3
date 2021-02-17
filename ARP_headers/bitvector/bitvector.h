#ifndef _BITVECTOR_H_
#define _BITVECTOR_H_

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

//typedef uint64_t BITVECT_64BIT; //64bit, not depending on the machine, unsigned
typedef uint64_t BITVECT_64BIT;

/**********************************************//**
* Initializing a bitvector to 1 in every position.
*
* Arguments
*	var - Bitvector to initialize; 
*   len - Dimension of the bitvector;
*
**************************************************/
#define RIGHT_BITMASK(var, len) { var = 0; for(BITVECT_64BIT j=0; j<(len); j++) var |= (1u << j); }

/**********************************************//**
* (DEPRECATED unpredictable behaviour in some occasions)
* Shifting to left the bit 1 of a given number of
* position
*
* Arguments
*   pos - Shifting position 
*
* Return
*   The function returns the bit 1 shifted to left of
*   pos positions;
**************************************************/
//define BIT(pos) (1u << pos)

// bit vector type ( just 'int' if IP_TABLE_LEN <= 32 )
typedef struct
{
    int len;            /* the real lenght of the bit vector */
    BITVECT_64BIT v;     /* '1' for available nodes, '0' for visited nodes */
}
bitvector_t;


/**********************************************//**
* Initializing the bitvector structure with a given
* length.
*
* Inside this function is set the length of the
* bitvector and there is the call of the functio
* RIGHT_BITMASK in order to sets all bit equal to 1.
*
* Arguments
*   bv - Bitvector to be initialized
*   len - Length of the bitvector
*
* Return
*   The function returns -1 if an error occurs,
*   len is a negative number or bv is NULL.
*   It returns 0 if the bitvector and its length
*   are correctly set.
*
**************************************************/
int bv_init( bitvector_t* bv, int len );

/**********************************************//**
* Clear the bitvector setting all bit to 1.
*
* Inside this function there is the execution of
* RIGHT_BITMASK, in order to set all bit to 1
*
* Arguments
*   bv - Bitvector to set to 1
*
**************************************************/
void bv_clear( bitvector_t* bv );

/**********************************************//**
* Checking if a node is marked inside the
* bitvector.
*
* Inside this function there is an error check
* on the value of the variable pos, it should be
* between zero and the length of bitvector.
* It checks if the node is been already visited just
* doing the and bit a bit between the actual
* bitvector and a variable that indicates the 
* position of the node.
*
* Arguments
*   bv - Bitvector to check the node
*   pos - Node number
*
* Return
*   The function returns -1 if an error occurs,
*   pos is a negative number or is greater than the
*   lenght of the bitvector
*   It returns 0 if the node is been already visited
*   and returns 1 if the node isn't visited yet.
*
**************************************************/
int bv_marked( bitvector_t* bv, BITVECT_64BIT pos );

/**********************************************//**
* Marks a node as visited.
*
* Inside this function a BIT() is performed, to do
* the and bit a bit between the bitvector and the 
* variable negated that indicates the position of 
* the node, in order to mark it as visited.
* 
* Arguments
*   bv - Bitvector to mark the node
*   pos - Node number
*
**************************************************/
void bv_mark( bitvector_t* bv, BITVECT_64BIT pos );

/**********************************************//**
* Checking if all bit on the bitvector are marked
*
* Inside the function there is a variable bmask
* that a bitvector with all bit set to 1, in order
* to do the and bit a bit with the bitvector to
* check.
*
* Arguments
*   bv - Bitvector to mark the node
*
* Return
*   The function returns 1 if all bit are marked and
*   0 if there is at least one bit not marked.
*
**************************************************/
int bv_all_marked( bitvector_t* bv );

#endif
