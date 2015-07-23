#pragma once
#include <X11/Xlib.h>
void getMouseCoords(Display* dpy,Window window,int* resX,int*resY);
void moveMouse(Display* dpy, Window window,int x, int y);
void sendClick(Display* dpy,int button);
