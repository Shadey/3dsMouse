#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include "client.h"
int main(){
	gfxInitDefault();
	consoleInit(GFX_TOP,NULL);
	SOC_Initialize((u32*)memalign(0x1000, 0x480000), 0x480000);

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		parseInput();
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	SOC_Shutdown();
	gfxExit();
	return 0;
}
