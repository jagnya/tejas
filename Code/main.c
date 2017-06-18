/*
 * Team: Unicorn
 * Authors: Jagnya Datta tripathy, Gnanaprakash
 * Purpose: 
 * Dated: 17/06/2017
 * Language:  C
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <unistd.h>
 #include "global.h"
 int main()
{
	int **nodeArray; //Creating a array max of 64 nodes
	int max_node=0,source_id=0,peer_node[MAX_PEER],k=0;
	pthread_t thread[MAX_NODE],c_thread[MAX_NODE];
	long unsigned int ALIVE_KEY = 0;
	int i=0,j=0;
	int node[MAX_NODE] = {0};

	nodeArray = fetch_datafile(&max_node);

	for(i=0;i<max_node;i++)
	{
                printf("Graph data: Max_node:%d",max_node);
		updateGraph(nodeArray,ALIVE_KEY,i,max_node);
		for (j=0;j<max_node;j++)
		{
			if ((k < 2) && (nodeArray[i][j]!=0 || nodeArray[j][i]!=0))
				peer_node[k++]= j;
		}
	}
	for(i=0;i<=max_node; i++)
	{
		pthread_create(&thread[i], NULL,  create_server, (void *) i);
		pthread_join(thread[i], NULL);
		for (k = 0 ; k < MAX_NODE; k++) 
		{ 
			pthread_create(&c_thread[i], NULL,  create_client, (void *) peer_node[i]);
			pthread_join(c_thread[i], NULL);
		}
	}
        pthread_exit(NULL);
	return 0;
}
