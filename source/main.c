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
#include <sysapp/launch.h>
#include <choose_currency.h>
#include <menu.h>

int main(int argc, char** argv) {
	int current_page = 1;
	int pressedA = 0;
	int back_colour = 0x00000000;
	int cursinoPos1 = 1;
	//int theme_num = 1;
	//int n_points = 0;
	//int d_points = 0;
	//const char n_ch;
	//const char d_ch;
	//char buf[128];
	
    WHBLogCafeInit();
    WHBLogUdpInit();
    WHBLogPrint("Welcome to Daneek! Logging initialised.");

    WHBProcInit();
    OSScreenInit();
	
	VPADStatus status;
	VPADReadError error;
	bool vpad_fatal = false;

    // Alocating buffer size
    size_t tvBufferSize = OSScreenGetBufferSizeEx(SCREEN_TV);
    size_t drcBufferSize = OSScreenGetBufferSizeEx(SCREEN_DRC);
    WHBLogPrintf("Will allocate 0x%X bytes for the TV, " \
                 "and 0x%X bytes for the DRC.",
                 tvBufferSize, drcBufferSize);

/*  alocate area.*/
    void* tvBuffer = memalign(0x100, tvBufferSize);
    void* drcBuffer = memalign(0x100, drcBufferSize);

    if (!tvBuffer || !drcBuffer) {
        WHBLogPrint("Out of memory!");

        if (tvBuffer) free(tvBuffer);
        if (drcBuffer) free(drcBuffer);

        OSScreenShutdown();
        WHBProcShutdown();

        WHBLogPrint("Quitting.");
        WHBLogCafeDeinit();
        WHBLogUdpDeinit();

        return 1;
    }

/*  Buffers are all good */
    OSScreenSetBufferEx(SCREEN_TV, tvBuffer);
    OSScreenSetBufferEx(SCREEN_DRC, drcBuffer);

/*  enable OSScreen for each display */
    OSScreenEnableEx(SCREEN_TV, true);
    OSScreenEnableEx(SCREEN_DRC, true);

    while(WHBProcIsRunning()) {
		VPADRead(VPAD_CHAN_0, &status, 1, &error);
		switch (error) 
		{
			case VPAD_READ_SUCCESS: 
			{
				break;
			}
			case VPAD_READ_NO_SAMPLES: 
			{
				continue;
			}
			case VPAD_READ_INVALID_CONTROLLER: 
			{
				vpad_fatal = true;
				break;
			}
			default: 
			{
				vpad_fatal = true;
				break;
			}
		}
		
		if (vpad_fatal) break;
		
	/*	Get pressed buttons */
		if (status.trigger & VPAD_BUTTON_DOWN) 
		{
			if (cursinoPos1 = 3) {
				cursinoPos1 = 1;
			}
			else {
				cursinoPos1++;
			}
		}
		if (status.trigger & VPAD_BUTTON_UP) 
		{
			if (cursinoPos1 = 1) {
				cursinoPos1 = 3;
			}
			else {
				cursinoPos1 = cursinoPos1 -1;
			}
		}
		if (status.trigger & VPAD_BUTTON_A) 
		{
			pressedA = 1;
		}
		else 
		{
			pressedA = 0;
		}
    /*  Clear each buffer*/
        OSScreenClearBufferEx(SCREEN_TV, back_colour);
        OSScreenClearBufferEx(SCREEN_DRC, back_colour);
		
		if (current_page == 1) 
		{
			int ret1 = showCurrencyDialog(cursinoPos1, pressedA);
			if (ret1 == 1) 
			{
				current_page = 2;
			}
		}
		if (current_page == 2) 
		{
			
		}

    /*  Flush all caches*/
        DCFlushRange(tvBuffer, tvBufferSize);
        DCF`lushRange(drcBuffer, drcBufferSize);

    /*  Flip buffers*/
        OSScreenFlipBuffersEx(SCREEN_TV);
        OSScreenFlipBuffersEx(SCREEN_DRC);
    }

    WHBLogPrint("Got shutdown request!");

/*  Free the buffers */
    if (tvBuffer) free(tvBuffer);
    if (drcBuffer) free(drcBuffer);

    OSScreenShutdown();
    WHBProcShutdown();

    WHBLogPrint("Quitting.");
    WHBLogCafeDeinit();
    WHBLogUdpDeinit();

    return 1;
}