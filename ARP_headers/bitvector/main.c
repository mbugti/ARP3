#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bitvector.h"

void print_bitvector( bitvector_t* bv );
void showbits( BITVECT_64BIT x );
void pls_in_bit( char* msg, BITVECT_64BIT n );



int main()
{
    bitvector_t bv;
    bv_init( &bv, 33 );
    print_bitvector( &bv );

    // pls_in_bit( "~(1<<2)", ~(1<<2) );

    printf( "before marking bit 2:\n" );
    /*
    pls_in_bit( " BIT(2)", 1u<<2 );
    pls_in_bit( "     BV", bv.v );
    pls_in_bit( "      &", BIT(2) & bv.v );
    */
    printf( "2nd marked? " ); //no
    bv_marked( &bv, 2 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n\n" );

    printf( "marking 2nd bit...\n" );
    // print_bitvector( &bv );
    bv_mark( &bv, 2 );
    // print_bitvector( &bv );
    printf( "\n" );

    printf( "after:\n" );
    /*
    pls_in_bit( " BIT(2)", BIT(2) );
    pls_in_bit( "     BV", bv.v );
    pls_in_bit( "      &", BIT(2) & bv.v );
    */
    printf( "2nd marked? " ); //yes
    bv_marked( &bv, 2 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    printf( "33th marked? " ); //yes
    bv_marked( &bv, 33 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    printf( "32th marked? " ); //no
    bv_marked( &bv, 32 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    printf( "-1st marked? " ); //yes
    bv_marked( &bv, -1 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    printf( "1st marked? " ); //no
    bv_marked( &bv, 1 ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    // expected: no
    printf( "all marked? " );
    bv_all_marked( &bv ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    printf( "marking all the remaining bits...\n" );
    for( int i=0; i < bv.len; i++ ) 
        bv_mark( &bv, i );

    // expected: yes
    printf( "all marked? " );
    bv_all_marked( &bv ) ? printf( "yes!" ) : printf( "no." ); 
    printf( "\n" );

    return 0;
}



void showbits( BITVECT_64BIT x )
{
    for (int i = (sizeof(BITVECT_64BIT) * 8) - 1; i >= 0; i--)
    {
        BITVECT_64BIT idx = i;
        putchar(x & (1u << idx) ? '1' : '0');
    }
}





void print_bitvector( bitvector_t* bv )
{
    printf( "BITVECTOR: LEN[%d] V[%ld] ", bv->len, bv->v );
    pls_in_bit( "V", bv->v );
}




void pls_in_bit( char* msg, BITVECT_64BIT n )
{
    printf( "%s[", msg ); showbits( n ); printf( "]\n" );
}