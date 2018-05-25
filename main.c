/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include <libpic30.h>
#include <timer.h>

#include "timerctrl.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

bool run_button_pressed = false;
bool mode_button_pressed = false;
uint8_t mode = _1_BLINK_SLOW;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    ChangeMode(mode);
    
    while(1)
    {        
        if (RUN_BUTTON == 0)
        {
            if (run_button_pressed == false)
            {
                RunStop();
                LATDbits.LATD0 ^= 1;
                run_button_pressed = true;
            }
        }
        else
            run_button_pressed = false;
        
        if (MODE_BUTTON == 0)
        {
            if (mode_button_pressed == false)
            {
                // change the mode
                switch(mode)
                {
                    case _1_BLINK_SLOW:
                        mode = _1_BLINK_FAST;
                        break;
                        
                    case _1_BLINK_FAST:
                        mode = _2_BLINK_SLOW;
                        break;
                        
                    case _2_BLINK_SLOW:
                        mode = _2_BLINK_FAST;
                        break;
                        
                    case _2_BLINK_FAST:
                        mode = _ALWAYS_ON;
                        break;
                        
                    case _ALWAYS_ON:
                        mode = _ALWAYS_OFF;
                        break;
                        
                    case _ALWAYS_OFF:
                        mode = _1_BLINK_SLOW;
                        break;
                        
                    default:
                        break;
                }
                
                ChangeMode(mode);
                LATD = (0x00ff & LATD) | mode<<8;
                
                mode_button_pressed = true;
            }
        }
        else
            mode_button_pressed = false;
    }
}
