/*
 * Team: Unicorn
 * Authors: Jagnya Datta tripathy, Gnanaprakash
 * Purpose: 
 * Dated: 17/06/2017
 * Language:  C
 */
#define MAX_NODE 64
#define MAX_PEER 2
#define PORT(x) 8000+x
int **fetch_datafile(int *max_node);
void *threadheartbeat(void *arg);
void Send_Heartbeat(void);
void updateGraph(int **node_graph, long unsigned alive_key,int source_node,int node_max);
void *create_server(void *vnode);
void *create_client(void *vnode);
void create_graph(int node,unsigned long int ALIVE);
