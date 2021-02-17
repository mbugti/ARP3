#ifndef _STATISTICS_H_
#define _STATISTICS_H_

// the type of the message reserved to saving the statistics
typedef struct stat_message
{
    float tot_bitrate;
    float fly_bitrate;
}
stat_t;

/**********************************************//**
* Simple initialization of the message, proforma
*
* Arguments
*   st_msg - pointer to the message to initialize 
*
**************************************************/
void stat_message_init(stat_t *st_msg);

/**********************************************//**
* Fill the tot_bitrate field in the passed message
*
* Arguments
*   st_msg - pointer to the message in which to set
*			the bitrate
*	tot_bitrate - total bitrate value computed
*
**************************************************/
void stat_message_set_totBitrate(stat_t *st_msg, float tot_bitrate);

/**********************************************//**
* Fill the fly_bitrate field in the passed message
*
* Arguments
*   st_msg - pointer to the message in which to set
*			the bitrate
*	fly_bitrate - total fly-time bitrate value 
+			computed
*
**************************************************/
void stat_message_set_flyBitrate(stat_t *st_msg, float fly_bitrate);

// ----------------- DEPRECATED -----------------
/**********************************************//**
* A way of retrieving RURZserver infos
*
* Return values are stored in the pointed arguments.
*
* Arguments
*   *strIP - pointer to the string in which the
*			IPv4 address of the server will be saved
*	*p_portno - pointer to the int in which the
*			port number of the server will be saved
*
**************************************************/
// void stat_get_serverInfo(char* strIP, int* p_portno);
// ----------------- DEPRECATED -----------------

/**********************************************//**
* A way for retrieving RURZ server infos.
* RURZ is assumed to communicate through port 5080,
* so you don't need to know anything other than 
* his address.
* 
* return:
*   it returns the IP address of RURZ server.
**************************************************/
char* stat_get_RURZ_addr();

#endif