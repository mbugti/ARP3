#include <string.h>
#include "connection.h"

/**
 * initialize server connection without accept a client
 */
int net_server_init( )
{
	
	//structures server address
	struct sockaddr_in serv_addr;
	int sockfd;
	int ret;

    int portno = ARPNET_STD_PORTNO;
	
	// Creating socket file descriptor 
    if((ret = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        // perror("ERROR in creating socket"); 
		return ret;
    } 
    sockfd = ret;
    //initialize socket address structure
	memset((char *)&serv_addr, 0, sizeof(serv_addr)); // bzero() deprecated
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    //attaching socket to the port passed as parameters 
    if ((ret = bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))) < 0) {
		// perror("ERROR on binding");
		close(sockfd);
		return ret;
	}
	
    //listen for connections with max 5 connection
    if((ret = listen(sockfd, 5)) <0){
		// perror("ERROR on listen"); 
		close(sockfd);
        return ret; 
	}
	return sockfd;
}

/**
 * function to accept a client
 **/
int net_accept_client(int sockfd, struct sockaddr_in* p_cli_addr){
	
	int newsockfd, 	 	//file descriptor result of accept
		clilen;			//client address size
	
	//accept a connection
    if( p_cli_addr == NULL )
    {
        // no informations about the client are needed
        newsockfd = accept(sockfd, NULL, NULL);
    }
    else
    {
        // return also the informations about the client
        clilen = sizeof(*p_cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) p_cli_addr, &clilen);
    }
   
    /*if (newsockfd < 0) 
    {
         // perror("ERROR on accept");
		 // notice the possible errore value is propagated through newsockfd
    }*/
    
    return newsockfd;
} 


/**
 * function to connect client to server specifying IP address and port num
 */
int net_client_connection(char *IPaddr) 
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
	server = gethostbyname(IPaddr); // obsolete; see -> man gethostbyname
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


/*
 *  function for accepting a connection with timeout
 */
int net_accept_client_timeout(int sockfd, struct timeval* timeout, struct sockaddr_in* cli_addr)
{
    // preserve the given timeout
    struct timeval tbackup;
    if( timeout != NULL ) tbackup = *timeout;
    
    // select on the file descriptor
    fd_set fdset;
    FD_ZERO( &fdset );
    FD_SET( sockfd, &fdset );
    int retval = select(  sockfd + 1, &fdset, NULL, NULL, timeout );

    // in any case, restore the previous timeout
    if( timeout != NULL ) *timeout = tbackup;

    // inspect the return value
    if( retval < 0 )
    {
        // error! close the function with -1
        return -1;
    }
    else if( retval == 0 )
    {
        // timeout is expired! close with 0
        return 0;
    }
    else
    {
        // you can accept the connection
        return net_accept_client( sockfd, cli_addr );
    }
}



/*
 *  connection to a node, given also a maximum timeout.
 */
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
