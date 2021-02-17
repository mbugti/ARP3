
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



int main()
{
    printf( "GRANDI ORECCHIE PER ASCOLTARE MEGLIO...\n" );
    int mysock = net_server_init(  );
    printf("(mysock=%d) ", mysock); printf( "(errno=%d) ", errno ); fflush(stdout); perror("server init");
    if( mysock < 0 ) return 0;
    
    /*
    printf( "waiting 2 seconds...\n" );
    sleep(5);
    */

    printf( "accept...\n" );
    // sleep(5);
    int clsock = net_accept_client( mysock, NULL );
    printf("(clsock=%d) ", clsock); printf( "(errno=%d) ", errno ); fflush(stdout); perror("accept client");

    // printf( "doing some stuff...\n" );
    char msg[50];
    memset( msg, 0, 50 );
    int returnval = read( clsock, msg, 50 );
    printf( "return value [%d]\n", returnval );
    if( returnval > 0 )
        printf( "MSG[%s]\n", msg );

    printf( "closing...\n" );
    close( clsock );
    close( mysock );

    return 0;

}