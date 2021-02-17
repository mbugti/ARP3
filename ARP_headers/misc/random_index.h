#include <stdlib.h>


/**********************************************//**
* Function to return a random number in the range
* [min, max] requested
*
* Inside the function the values generated are made
* a little more uniformely distributed by discarding
* the values produced by 'rand()' which fall in the
* area between the last integer multiple of 'range'
* and RAND_MAX, which would make their 'modulo' 
* values slightly more frequent then the remaining
* ones.
*
* Arguments
*	min - lower bound in the range
*	max - upper bound in the range
*
* Return
*	random - random value in the range [min, max]	
**************************************************/
int rdmindex(int min , int max);