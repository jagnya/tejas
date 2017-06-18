/*
 * Team: Unicorn
 * Authors: Jagnya Datta tripathy, Gnanaprakash
 * Purpose: To Fetching data from "input" file.
 * Dated: 17/06/2017
 * Language:  C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h" 
int **fetch_datafile(int *max_node)
{
	FILE *fptr;
	char filename[]="input";
	int src_node=0 , dst_node=0;
        int **node_Array;
        int node[64][64] = {0};
	/*  open the file for reading */
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}
	while(!feof(fptr)){
		fscanf(fptr, "%d ", &src_node);
		fscanf(fptr, "%d ", &dst_node);
		if(src_node < MAX_NODE || dst_node < MAX_NODE)
		{
			if(*max_node < src_node || *max_node < dst_node)
				*max_node = (src_node > dst_node) ? src_node : dst_node;
			fscanf(fptr, "%d", &node[src_node][dst_node]);
		}
		else
		{
			/* Skiping the node */
			fscanf(fptr, "%d ", &dst_node);
		}
	}
        node_Array = (int **)malloc((*max_node) * sizeof(int *));
        for (src_node=0; src_node<= *max_node; src_node++)
        {
          node_Array[src_node] = (int *)malloc((*max_node) * sizeof(int));
        }
        for(src_node=0;src_node <= *max_node;src_node++)
        {
          for (dst_node=0;dst_node<= *max_node; dst_node++)
          {
              node_Array[src_node][dst_node] = node[src_node][dst_node];
          }
        }
	fclose(fptr);
        return node_Array;
}
