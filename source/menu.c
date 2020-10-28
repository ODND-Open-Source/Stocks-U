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
	
	// Drawing to the screen depending on where the "cursor" is
	if (cursPos == 1) {
		OSScreenPutFontEx(SCREEN_TV, 0, 3, "<Company List>");
		OSScreenPutFontEx(SCREEN_TV, 0, 4, "Wallet");
		OSScreenPutFontEx(SCREEN_TV, 0, 5, "Buy Stock");
		OSScreenPutFontEx(SCREEN_TV, 0, 6, "Sell Stock");
		
		OSScreenPutFontEx(SCREEN_DRC, 0, 3, "<Company List>");
		OSScreenPutFontEx(SCREEN_DRC, 0, 4, "Wallet");
		OSScreenPutFontEx(SCREEN_DRC, 0, 5, "Buy Stock");
		OSScreenPutFontEx(SCREEN_DRC, 0, 5, "Sell Stock");
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
}