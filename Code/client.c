/************* UDP CLIENT CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
void *create_client(void *vnode)
{
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  unsigned long int ALIVE_KEY=2;
  socklen_t addr_size;
  int node = (int) vnode;
  ALIVE_KEY = 1 << node;
  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT(node));
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  printf("Print node:%d ",PORT(node));
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  while(1){
    //fgets(buffer,1024,stdin);
    snprintf(buffer, 1024 , "ALIVE:%lu", ALIVE_KEY);
    
    nBytes = strlen(buffer) + 1;
    
    /*Send message to server*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    sleep(4);
    /*Receive message from server*/
                nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

    printf("Received ALIVE_KEY: %s\n",buffer);

  }

  return 0;
}
