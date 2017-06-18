#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "global.h"
long unsigned int ALIVE_KEY;
#define true 1
#define false 0
static int max_node = 0;

unsigned int isBitValueSet(long unsigned value, unsigned int index)
{
	long unsigned val = (0x01 << index);
	if(value & val)
		return true;
	else
		return false;
}

void setBitValue(long unsigned *value, unsigned int index)
{
	long unsigned  val = (0x01 << index);
	*value = (*value) | val;
	return;
}

/* Find the node with the minimum cost and not present in MST */
int minKey(int key[], long unsigned mstSet)
{
	// Initialize min value
	int min = INT_MAX, min_index = -1 ;
	int v=0;

	for (v = 0; v < max_node; v++)
	{
		if ((!isBitValueSet(mstSet,v)) && key[v] < min)
			min = key[v], min_index = v;
	}
	return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printNetworkNodes(int parent[], int n, int **graph)
{
	int i=0;
	printf("Edge Weight\n");
	for(i = 1; i < n; i++)
	{
		if((parent[i] != -1) && (graph[i][parent[i]]>0))
			printf("%d - %d %d \n", parent[i], i, graph[i][parent[i]]);
		if((parent[i] != -1) && (graph[parent[i]][i] >0))
			printf("%d - %d %d \n", parent[i], i, graph[parent[i]][i]);
	}
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int **graph, unsigned long int first)
{
	int parent[max_node]; // Array to store constructed MST
	int key[max_node]; // Key values used to pick minimum weight edge in cut
	long unsigned mstSet = {0}; // To represent set of vertices not yet included in MST
	int i=0, v=0, count=0;
	// Initialize all keys as INFINITE
	for (i = 0; i < max_node; i++)
        {
                key[i] = INT_MAX;
        }
	// Always include first 1st vertex in MST.
	key[0] = 0;	 // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST

	// The MST will have N vertices
	for (count = 0; count < max_node-1; count++)
	{
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		int u = minKey(key, mstSet);
		// Add the picked vertex to the MST Set
		setBitValue(&mstSet, u);

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (v = 0; v < max_node; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if ((u!=-1)&&(!isBitValueSet(mstSet, v)) && graph[u][v] && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];

	}
	// print the constructed MST

	  printNetworkNodes(parent, max_node, graph);
}


void updateGraph(int **graph, long unsigned alive_key,int source_node,int node_max)
{
	int i=0, j=0;
        max_node = node_max;
	for(i=0; i<max_node; i++)
        {
          for(j=0; j<max_node; j++)
          {
             if(graph[i][j] != 0)
             printf("v[%d][%d]=%d\n",i,j,graph[i][j]);
          }
        }
	for(i=0; i<max_node; i++)
	{
		if(!isBitValueSet(alive_key, i))  
		{
			for(j=0; j<max_node; j++)
			{
				graph[j][i] = 0;
				graph[i][j] = 0;
			}
		}
	}
	for(i=0; i<max_node; i++)
        {
          for(j=0; j<max_node; j++)
          {
             if(graph[i][j] != 0)
             printf("v[%d][%d]=%d\n",i,j,graph[i][j]);
          }
        }
	primMST(graph, alive_key);
        free(graph);
}

void create_graph(int node, unsigned long int ALIVE)
{
    int **nodeArray;
    int max_node=0;
    printf("\n Graphing technique from node");
    nodeArray = fetch_datafile(&max_node);
    updateGraph(nodeArray,ALIVE,node,max_node);
}
