#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include "client.h"
int main(){
	gfxInitDefault();
	consoleInit(GFX_TOP,NULL);
	SOC_Initialize((u32*)memalign(0x1000, 0x48000), 0x48000);
	printf("Homebrew hype train\n");
	sendData(8081);
	while (aptMainLoop())
	{

		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	SOC_Shutdown();
	gfxExit();
	return 0;
}
