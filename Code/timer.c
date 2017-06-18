/*
 * Team: Unicorn
 * Authors: Jagnya Datta tripathy, Gnanaprakash
 * Purpose: To Send the heartbeat.
 * Dated: 17/06/2017
 * Language:  C
 */
#include "global.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int HB_failure;
static int HB_retry = 1;
long unsigned int get_localalivekey()
{
  return 15; //4 nodes present
}
void Send_Heartbeat()
{
	unsigned long int ALIVE_MAP = get_localalivekey();
	printf("\nSending Alive map %lu",ALIVE_MAP); 
	my_val ++;
	if(my_val > 6)
	{
		HB_failure = 1;
	}
}
void receive_heartbeat(void *arg)
{
   
}
void *threadheartbeat(void *arg)
{
   while(!HB_failure)
    {
        call_function();
        sleep(3);
    }
    return 0;
}
int main()
{
     pthread_t tid;
     pthread_create(&tid, NULL, &threadheartbeat, NULL);
     pthread_join(tid,NULL);
     
}
