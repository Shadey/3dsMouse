#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <3ds.h>
#include <stdlib.h>
#include <time.h>
void sendData(int port, char command[]){
  consoleInit(GFX_TOP,NULL);
  int clientfd;
  struct sockaddr_in server;
  clientfd=socket(AF_INET,SOCK_DGRAM,0);
  if(clientfd == -1){
    printf("Couldn't make socket");
    return;
  }
  bzero(&server,sizeof(server));
  server.sin_addr.s_addr = inet_addr("192.168.0.8");
  server.sin_family = AF_INET;
  server.sin_port=htons(port);
  if(sendto(clientfd,command,strlen(command),0, (struct sockaddr *)&server,sizeof(server)) < 0){
    printf("sent\n");
  }
  close(clientfd);
}
void parseInput(){
  hidScanInput();
  u32 kDown = hidKeysDown();
  if((kDown&KEY_DRIGHT) != 0){
    sendData(8081, "MOVE RIGHT");
  }
  else if((kDown& KEY_DLEFT) != 0){
    sendData(8081, "MOVE LEFT");
  }
  else if((kDown&KEY_DUP) != 0){
    sendData(8081,"MOVE UP");
  }
  else if((kDown&KEY_DDOWN) != 0){
    sendData(8081,"MOVE DOWN");
  }
}
