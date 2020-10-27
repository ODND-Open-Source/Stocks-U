#include <coreinit/screen.h>
#include <coreinit/cache.h>
#include <whb/log_cafe.h>
#include <whb/log_udp.h>
#include <whb/log.h>
#include <whb/proc.h>
#include <vpad/input.h>
#include <choose_currency.h>
#include <draw.h>

int cur = 0;

void showCurrencyDialog() {
	int cursPos = 1
		
	/*	Get pressed buttons */
	if (status.trigger & VPAD_BUTTON_DOWN) 
	{
		
	}
	
	// Draw to screen
	
	// message to be displayed always:
	OSScreenPutFontEx(SCREEN_TV, 0, 0, "Welcome to StocksU!");
	OSScreenPutFontEx(SCREEN_TV, 0, 1, "Please choose a currency:");
	OSScreenPutFontEx(SCREEN_TV, 0, 2, "--------------------------------------");
	
	OSScreenPutFontEx(SCREEN_DRC, 0, 0, "Welcome to StocksU!");
	OSScreenPutFontEx(SCREEN_DRC, 0, 1, "Please choose a currency:");
	OSScreenPutFontEx(SCREEN_DRC, 0, 2, "--------------------------------------");
	
	// Drawing to the screen depending on where the "cursor" is
	if (cursPos == 1) {
		OSScreenPutFontEx(SCREEN_TV, 0, 0, "Welcome to StocksU!");
	}
}