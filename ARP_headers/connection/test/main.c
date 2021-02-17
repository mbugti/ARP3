
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>
#include <sys/select.h>

#define     ARPNET_STD_PORTNO     5080
#define     IP_DUMMY    "157.98.168.1"
#define     IP_LOCAL    "127.0.0.1"

int net_client_connection_timeout(char* ip_addr, struct timeval* timeout);


int net_client_connection(char* ip_addr) 
{
	
	//socket file descriptor
	int sockfd, ret;

    int portno = ARPNET_STD_PORTNO;

	//structures for socket connection
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    //create socket
    if ((ret = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        //perror("ERROR opening socket");
        return ret;
	}
	sockfd = ret;
	//get IP address
	server = gethostbyname(ip_addr); // obsolete; see -> man gethostbyname
    if (server == NULL) 
    {
        // printf("ERROR, no such host\n");
        return -1;
    }
    
    //setting data for socket connection
	memset((char *)&serv_addr, 0, sizeof(serv_addr)); // bzero() deprecated
	//bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
	memcpy((char *)&serv_addr.sin_addr.s_addr, (char *) server->h_addr, server->h_length); // bcopy() deprecated
    //bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    
    //connection
    if ((ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0) 
    {
        // perror("ERROR in connecting");
        return ret;
	}
        
    return sockfd;  
}



int main()
{
    struct timeval timeout = { 5, 0 };
    int sockfd;
    printf( "timeout { %ld, %ld }\n", timeout.tv_sec, timeout.tv_usec );

    /*
        INSTRUCTION FOR RUNNING THIS TEST
        1.  before starting, enable the server!
        2.  then, launch this program and see what happens!
    */

    printf( "Trying and write to a dummy address..\n" );
    sockfd = net_client_connection_timeout( IP_DUMMY, &timeout );
    if( sockfd == 0 )
    {
        printf( "timeout! " ); fflush( stdout ); perror( "timeout expired" );
    }
    else if( sockfd < 0 )
    {
        printf( "(errno=%d) ", errno ); fflush( stdout ); perror( "error on client connection timeout" );
    }
    else
    {
        char msg[100] = "da grandi orecchie derivano grandi responsabilità.";
        printf( "write to the server: [%s] \t returned[%d]\n", msg, (int) write( sockfd, msg, 100 ) );
        close( sockfd );
    }

    printf( "trying to connect to codename GRANDIORECCHIE...\n" );
    sockfd = net_client_connection_timeout( IP_LOCAL, &timeout );
    if( sockfd == 0 )
    {
        printf( "timeout! " ); fflush( stdout ); perror( "timeout expired" );
    }
    else if( sockfd < 0 )
    {
        printf( "(errno=%d) ", errno ); fflush( stdout ); perror( "error on client connection timeout" );
    }
    else
    {
        char msg[100] = "da grandi orecchie derivano grandi responsabilità.";
        printf( "write to the server: [%s] \t returned[%d]\n", msg, (int) write( sockfd, msg, 100 ) );
        close( sockfd );
    }
        
    return 0;
}






int net_client_connection_timeout(char* ip_addr, struct timeval* timeout)
{
    // preserve the previous timeout structure
    struct timeval tback = {0, 0};
    if( timeout != NULL )
        tback = *timeout;

    //socket file descriptor and port
	int sockfd;
    int portno = ARPNET_STD_PORTNO;
    int returnval;

	//structures for socket connection
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    //create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        //perror("ERROR opening socket");
        return sockfd;
	}

    // set the socket as non blocking
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	//get IP address
	server = gethostbyname(ip_addr); // obsolete; see -> man gethostbyname
    if (server == NULL) 
    {
        // printf("ERROR, no such host\n");
        return -1;
    }
    
    //setting data for socket connection
	memset((char *)&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
	memcpy((char *)&serv_addr.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    // initialise the connection
    returnval = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if( (returnval < 0) && (errno != 0) && (errno != EINPROGRESS) )
    {
        // the connection has failed.
        return -1;
    }

    // waiting for the socket to be ready
    fd_set fdset;
    FD_ZERO( &fdset );
    FD_SET( sockfd, &fdset );
    returnval = select( sockfd+1, NULL, &fdset, NULL, timeout );

    // in any case, restore the given timeval structure
    *timeout = tback;

    if( returnval < 0 )
    {
        //something goes south...
        return -1;
    }
    else if( returnval == 0 )
    {
        // timeout expired (it happens when the connection isn't available)
        return 0;
    }
    else
    {
        // connection successfully established!
        return sockfd;
    }
}