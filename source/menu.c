#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

#include <coreinit/screen.h>
#include <coreinit/cache.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>
#include <whb/log.h>
#include <whb/proc.h>
#include <vpad/input.h>
#include <menu.h>

int showMainMenu() 
{
	// Declare the variable that will be returned
	int retVal1 = 0;
	//Draw to the screen
	OSScreenPutFontEx(SCREEN_TV, 0, 0, "StocksU Dashboard");
	OSScreenPutFontEx(SCREEN_TV, 0, 1, "--------------------------------------");
	OSScreenPutFontEx(SCREEN_TV, 0, 2, "Please choose a option:");
	
	OSScreenPutFontEx(SCREEN_DRC, 0, 0, "StocksU Dashboard");
	OSScreenPutFontEx(SCREEN_DRC, 0, 1, "--------------------------------------");
	OSScreenPutFontEx(SCREEN_DRC, 0, 2, "Please choose a option:");
}