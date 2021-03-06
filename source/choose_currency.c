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
#include <choose_currency.h>

VPADStatus status;
VPADReadError error;
bool vpad_fatal = false;

int showCurrencyDialog(int cursPos, int aPressed) {
	// Declare the variable that will be returned
	int retVal = 0;
	// Draw to screen
	// Message to be displayed always:
	OSScreenPutFontEx(SCREEN_TV, 0, 0, "Welcome to StocksU!");
	OSScreenPutFontEx(SCREEN_TV, 0, 1, "Please choose a currency:");
	OSScreenPutFontEx(SCREEN_TV, 0, 2, "--------------------------------------");
	
	OSScreenPutFontEx(SCREEN_DRC, 0, 0, "Welcome to StocksU!");
	OSScreenPutFontEx(SCREEN_DRC, 0, 1, "Please choose a currency:");
	OSScreenPutFontEx(SCREEN_DRC, 0, 2, "--------------------------------------");

	// Drawing to the screen depending on where the "cursor" is
	if (cursPos == 1) {
		OSScreenPutFontEx(SCREEN_TV, 0, 3, "<Pound Sterling>");
		OSScreenPutFontEx(SCREEN_TV, 0, 4, "US Dollar");
		OSScreenPutFontEx(SCREEN_TV, 0, 5, "EU Euro");
		
		OSScreenPutFontEx(SCREEN_DRC, 0, 3, "<Pound Sterling>");
		OSScreenPutFontEx(SCREEN_DRC, 0, 4, "US Dollar");
		OSScreenPutFontEx(SCREEN_DRC, 0, 5, "EU Euro");
	}
	if (cursPos == 2) {
		OSScreenPutFontEx(SCREEN_TV, 0, 3, "Pound Sterling");
		OSScreenPutFontEx(SCREEN_TV, 0, 4, "<US Dollar>");
		OSScreenPutFontEx(SCREEN_TV, 0, 5, "EU Euro");
		
		OSScreenPutFontEx(SCREEN_DRC, 0, 3, "Pound Sterling");
		OSScreenPutFontEx(SCREEN_DRC, 0, 4, "<US Dollar>");
		OSScreenPutFontEx(SCREEN_DRC, 0, 5, "EU Euro");
	}
	if (cursPos == 3) {
		OSScreenPutFontEx(SCREEN_TV, 0, 3, "Pound Sterling");
		OSScreenPutFontEx(SCREEN_TV, 0, 4, "US Dollar");
		OSScreenPutFontEx(SCREEN_TV, 0, 5, "<EU Euro>");
		
		OSScreenPutFontEx(SCREEN_DRC, 0, 3, "Pound Sterling");
		OSScreenPutFontEx(SCREEN_DRC, 0, 4, "US Dollar");
		OSScreenPutFontEx(SCREEN_DRC, 0, 5, "<EU Euro>");
	}
	OSScreenPutFontEx(SCREEN_DRC, 0, 6, "--------------------------------------");
	OSScreenPutFontEx(SCREEN_DRC, 0, 6, "Press A to select.");
	OSScreenPutFontEx(SCREEN_TV, 0, 6, "--------------------------------------");
	OSScreenPutFontEx(SCREEN_TV, 0, 6, "Press A to select.");
	
	switch (aPressed) 
	{
		case 1: 
		{
			retVal = 1;
			break;
		}
		case 0: 
		{
			retVal = 0;
			break;
		}
	}
	return retVal;
}