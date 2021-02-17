#include "random_index.h"

// Take a look at the link shared on Trello on this topic to better 
// understand motivations and implementation

int rdmindex(int min , int max)
{
    //if we have 30 nodes , min in 0 max is 29. The function at the end will return an integer in the range 0-29
	int range = max - min +1;
	int r;
	// this piece discards values of 'r' which would cause non-uniformity in
	// the subsequent 'modulo' operation (since RAND_MAX is generally not abort
	// multiple of our required range.
	while( (r = rand()) > (RAND_MAX - (RAND_MAX - (range-1) )%range) ){}
      
	return min + r%range;
}
