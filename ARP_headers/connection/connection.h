#ifndef _CONNECTION_H_
#define _CONNECTION_H_

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

/**********************************************//**
* Well-known port for the Network: 5080
* Each node must use this port in order to
* communicate within the network. Please make sure
* you have this port enabled on your Azure VM.
**************************************************/
#define     ARPNET_STD_PORTNO     5080

/**********************************************//**
* Initializing the main socket in a server code.
*
* Inside this function the socket gets generated,
* a bind() is tried and, if succesful, is followed
* by a listen().
*
* You can see the portno using the constant
*       ARPNET_STD_PORT
*
* Return
*	sockfd - the file descriptor of the opened
*		and binded socket, if successful, otherwise
*		the error code associated with the first
*		error occurred in the process;
**************************************************/
int net_server_init( );


/**********************************************//**
* Performing an accept on a connect request.
*
* Inside this function an accept() is performed,
* and errors in such process checked.
*
* Arguments
*	sockfd - the file descriptor of the socket the
*		process is waiting of for a connection 
*		request;
*	p_cli_addr - a pointer to a struct where data
*		of the client will be inserted; NULL if 
*       not used
*
* Return
*	newsockfd - the file descriptor of the newly
*		opened socket where the communication with
*		the client can take place, if successful,
*		otherwise the error code associated with
*		the accept() failed call;
**************************************************/
int net_accept_client(int sockfd, struct sockaddr_in* cli_addr);


/**********************************************//**
* Trying to connect to a server which IPv4 address
* and open port number are known
*
* Inside this function a socket is opened and abort
* connection with the server indicated is 
* attempted.
*
* You can see the portno using the constant
*       ARPNET_STD_PORT
*
* Arguments
*	IPaddr - a string representing the name 
*		associated with the server;
*
* Return
*	sockfd - the file descriptor of the opened
*		socket where the communication with the
*		desired server can take place;		
**************************************************/
int net_client_connection(char *IPaddr);


/**********************************************//**
* Performing an accept on a connect request,
* considering also a time within receiving it.
* Here select() is used on your socket.
*
* Inside this function an accept() is performed,
* and errors in such process checked.
*
* Arguments
*	sockfd - the file descriptor of the socket the
*		process is waiting of for a connection 
*		request;
*   timeout - how much time the accept can wait
*       before returning; the function waits at
*       most for the given time; if NULL, the 
*       function is equivalent to the usual
*       net_accept_client(). NOTE: this function
*       doesn't alter this pointed data structure
*       differently from the usual select().
*       If the timeout is zero, the function is
*       non-blocking (select returns immediately).
*	p_cli_addr - a pointer to a struct where data
*		of the client will be inserted; NULL if 
*       not used
*
* Return
*   -1  in case of error (in this case, select()
*       returns immediately)
*   0   if the timeout is expired
*   >0  the new file descriptor from the accept()
**************************************************/
int net_accept_client_timeout(int sockfd, struct timeval* timeout, struct sockaddr_in* cli_addr);


/**********************************************//**
* Trying to connect to a server which IPv4 address;
* this considers also a maximum waiting time.
* Here select() is used on your socket.
*
* This function could be useful for you only in
* the handshake phase. Otherwise, you must be
* absolutely sure about what you're doing.
*
* Inside, a socket is opened and abort
* connection with the server indicated is 
* attempted.
*
* You can see the portno using the constant
*       ARPNET_STD_PORT
*
* Arguments
*	IPaddr - a string representing the name 
*		associated with the server;
*   timeout - how much time the accept can wait
*       before returning; the function waits at
*       most for the given time; if NULL, the 
*       function is equivalent to the usual
*       net_client_connection(). NOTE: this function
*       doesn't alter this pointed data structure
*       differently from the usual select().
*       If the timeout is zero, the function is
*       non-blocking (select returns immediately).
*
* Return
*   -1  in case of error (in this case, select()
*       returns immediately)
*   0   if the timeout is expired
*   >0  the new file descriptor from the connect()	
**************************************************/
int net_client_connection_timeout(char *ip_addr, struct timeval* timeout);

#endif