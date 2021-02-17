#include "bitvector.h"

// inizialization of the bit vector
int bv_init( bitvector_t* bv, int len )
{
    if( len < 1 )
        return -1;
    if( bv == NULL )
        return -1;

    bv->len = len;
    RIGHT_BITMASK( bv->v, bv->len );

    return 0;
}

// it sets all the bits of the vector to zero
void bv_clear( bitvector_t* bv )
{
    RIGHT_BITMASK( bv->v, bv->len );
}

// check if a node is marked as visited
// unmarked(1) - marked(0)
int bv_marked( bitvector_t* bv, BITVECT_64BIT pos )
{
    return ( !( (1u<<pos) & bv->v ) || pos<0 || pos>=bv->len );
}

// mark a node as visited
void bv_mark( bitvector_t* bv, BITVECT_64BIT pos )
{
    bv->v &= ~(1u<<pos);
}

// check if at least one node is available
int bv_all_marked( bitvector_t* bv )
{
    unsigned int bmask = 0; RIGHT_BITMASK( bmask, bv->len );
    return !( bmask & bv->v );
}
