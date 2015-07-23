#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <time.h>
#include <X11/extensions/XTest.h>
#include "mouse.h"
#include "server.h"
int main(){
  listenOn(8080);
  return 0;
}
