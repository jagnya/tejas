/************* UDP SERVER CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
void *create_server(void *vnode)
{
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;
  int node = (int) vnode;
  unsigned long int ALIVE_KEY = 1 << node ;
  unsigned long int ALIVE_KEY1;
  char str[10];
  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT(node));
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  printf("node:%d",PORT(node));
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

     sscanf(buffer,"%s:%lu",str,&ALIVE_KEY1);
     if(ALIVE_KEY != ALIVE_KEY1)
     {
       ALIVE_KEY = ALIVE_KEY1;
       /* MIS_MATCH Call graph */
       create_graph(node,ALIVE_KEY);
    }
     
     printf("Received from client : %s\n",buffer);
     snprintf(buffer, 1024 , "ALIVE:%lu", ALIVE_KEY); 
     printf("Send %s",buffer);
    /*Send uppercase message back to client, using serverStorage as the address*/
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }
}
