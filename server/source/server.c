#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <X11/Xlib.h>
#include <fcntl.h>
#include "mouse.h"

void listenOn(int port){
  int serverfd,clientfd;
  struct sockaddr_in server,client;
  char messageBuffer[4096];
  serverfd = socket(AF_INET,SOCK_DGRAM,0);
  if(serverfd < 0){
    printf("Error creating socket");
    return;
  }
  printf("Created socket\n");
  bzero(&server,sizeof(server));
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  if(bind(serverfd, (struct sockaddr *)&server,sizeof(server)) < 0){
    printf("Couldn't bind\n");
    return;
  }
  printf("Listening on port %d\n",port);
  for(;;){
    clientfd = recv(serverfd,messageBuffer,sizeof(messageBuffer),0);
    if( clientfd > 0){
      if(strlen(messageBuffer) > 0){
        parseMessage(messageBuffer);
        memset(messageBuffer, 0, sizeof(messageBuffer));
      }
    }
    else{
      printf("Couldn't recieve. Clientfd was %d\n",clientfd);
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
