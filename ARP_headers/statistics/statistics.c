#include "statistics.h"
#include <string.h>
#include <stdio.h>

char* RURZ_IP_STR = "0.0.0.0";
// int RURZ_PORTNO = -1;

// initialize stat message
void stat_message_init(stat_t *st_msg){
	st_msg->tot_bitrate = 0.0;
	st_msg->fly_bitrate = 0.0;
}
// set the bitrate computed on the total time (sending of first message by Turn Leader, receival of last message from Turn Leader)
void stat_message_set_totBitrate(stat_t *st_msg, float tot_bitrate){
	st_msg->tot_bitrate = tot_bitrate;
}
// set the bitrate computed 
void stat_message_set_flyBitrate(stat_t *st_msg, float fly_bitrate){
	st_msg->fly_bitrate = fly_bitrate;
}

// ----------------- DEPRECATED -----------------
/*
void stat_get_serverInfo(char* strIP, int* p_portno){
	strncpy(strIP, RURZ_IP_STR, 16);
	*(p_portno)= RURZ_PORTNO;
}
*/
// ----------------- DEPRECATED -----------------

char* stat_get_RURZ_addr()
{
	return RURZ_IP_STR;
}