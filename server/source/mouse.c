#include <stdlib.h>
#include <X11/Xlib.h>
#include <time.h>
#include <X11/extensions/XTest.h>
void getMouseCoords(Display* dpy,Window window, int* resX, int*resY){
  Window returnWindow;
  int winX,winY;
  unsigned int maskReturn;
  XQueryPointer(dpy,window,&returnWindow,&returnWindow,resX, resY,&winX,&winY,&maskReturn);
}
void moveMouse(Display* dpy,Window window,int x,int y){
  XSelectInput(dpy, window, KeyPressMask);
  XWarpPointer(dpy,None,window,0,0,0,0,x,y);
  XFlush(dpy);
}
void sendClick(Display* dpy,int button){
  XTestFakeButtonEvent(dpy, button, True, CurrentTime);
  XTestFakeButtonEvent(dpy, button, False, CurrentTime);
  XFlush(dpy);
}
