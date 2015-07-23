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
	while (aptMainLoop())
	{
		sendData(8080,"Testing\n");
		gspWaitForVBlank();
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	SOC_Shutdown();
	gfxExit();
	return 0;
}
