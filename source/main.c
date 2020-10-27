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

int main(int argc, char** argv) {
	
	int current_page = 1;
	int back_colour = 0x00000000;
	int theme_num = 1;
	int n_points = 0;
	int d_points = 0;
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

/*  Buffers*/
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
		if (status.trigger & VPAD_BUTTON_X) 
		{
			// change theme
			if (theme_num == 1) 
			{
				theme_num = 2;
				back_colour = 0x00ff0000;
			}
			else if (theme_num == 2) {
				theme_num = 1;
				back_colour = 0x00000000;
			}

		}
		
		if (status.trigger & VPAD_BUTTON_A) 
		{
			if (current_page == 2) 
			{
				if (d_points != 10) 
				{
					d_points++;
				}
				
				else if (d_points == 10) 
				{
					d_points = 0;
				}
			}
		}
		
		
		
    /*  Clear each buffer*/
        OSScreenClearBufferEx(SCREEN_TV, back_colour);
        OSScreenClearBufferEx(SCREEN_DRC, back_colour);
		
		if (current_page == 1) 
		{
			OSScreenPutFontEx(SCREEN_TV, 0, 0, "Coats Family Point Counter TV");
			OSScreenPutFontEx(SCREEN_TV, 0, 1, "Press A to add a point to D");
			OSScreenPutFontEx(SCREEN_TV, 0, 2, "Press B to add a point to N");
			OSScreenPutFontEx(SCREEN_TV, 0, 3, "Press X to change theme");
			OSScreenPutFontEx(SCREEN_TV, 0, 4, "Press + to toggle pages");
			
			OSScreenPutFontEx(SCREEN_DRC, 0, 0, "Coats Family Point Counter Gamepad");
			OSScreenPutFontEx(SCREEN_DRC, 0, 1, "Press A to add a point to D");
			OSScreenPutFontEx(SCREEN_DRC, 0, 2, "Press B to add a point to N");
			OSScreenPutFontEx(SCREEN_DRC, 0, 3, "Press X to change theme");
			OSScreenPutFontEx(SCREEN_DRC, 0, 4, "Press + to toggle pages");
		}
		

    /*  Flush all caches*/
        DCFlushRange(tvBuffer, tvBufferSize);
        DCFlushRange(drcBuffer, drcBufferSize);

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