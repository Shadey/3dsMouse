#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <X11/Xlib.h>
#include "mouse.h"
void listenOn(int port){
  int sockfd, messagefd;
  struct sockaddr_in server,client;
  socklen_t len;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  bzero(&server,sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);
  bind(sockfd,(struct sockaddr*)&server, sizeof(server));
  printf("Listening on port %d\n", port);
  for(;;){
    char messageBuffer[4096];
    len = sizeof(client);
    messagefd = recvfrom(sockfd, messageBuffer, 4096,0 , (struct sockaddr*) &client, &len);
    if(strlen(messageBuffer) > 0){
      parseMessage(messageBuffer);
      memset(messageBuffer, 0, sizeof(messageBuffer));
    }
  }
}

void parseMessage(char message[]){
  Display *dpy = XOpenDisplay(0);
  Window rootWindow = XRootWindow(dpy,0);
  int x,y;
  getMouseCoords(dpy, rootWindow,&x,&y);
  if(strcmp(message,"MOVE LEFT") == 0){
    printf("Moving to %d,%d\n",x-5,y);
    moveMouse(dpy,rootWindow,x-=5,y);
  }
  else if(strcmp(message,"MOVE RIGHT") == 0){
    printf("Moving to %d,%d\n",x+5,y);
    moveMouse(dpy,rootWindow,x+=5,y);
  }
  else if(strcmp(message,"MOVE UP") == 0){
    printf("Moving to %d,%d\n",x,y);
    moveMouse(dpy,rootWindow,x,y-=5);
  }
  else if(strcmp(message,"MOVE DOWN") == 0){
    printf("Moving to %d,%d\n",x,y-5);
    moveMouse(dpy,rootWindow,x,y+=5);
  }
  else if(strcmp(message,"RIGHT CLICK") == 0){
    printf("Right clicking\n");
    sendClick(dpy,Button1);
  }
  else if(strcmp(message,"LEFT CLICK") == 0){
    printf("Left clicking\n");
    sendClick(dpy,Button1);
  }
  else{
    printf("%s\n",message);
  }
}
