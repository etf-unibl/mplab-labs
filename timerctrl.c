#include "timerctrl.h"
#include <timer.h>

extern Callback pfnCallback;

void RegisterIntHandler(Callback pfncb);
void BlinkingOneSlow();
void BlinkingOneFast();
void BlinkingTwoSlow();
void BlinkingTwoFast();
void AlwaysOn();
void AlwaysOff();

void RunStop()
{
    // toggle the interrupt enable, TON bit and LED on RD0
    _T1IE ^= 1;
    T1CONbits.TON ^= 1;
}

void ChangeMode(uint8_t mode)
{
    switch (mode)
    {
        case _1_BLINK_SLOW:
            RegisterIntHandler(&BlinkingOneSlow);
            break;
            
        case _1_BLINK_FAST:
            RegisterIntHandler(&BlinkingOneFast);
            break;
            
        case _2_BLINK_SLOW:
            RegisterIntHandler(&BlinkingTwoSlow);
            break;
            
        case _2_BLINK_FAST:
            RegisterIntHandler(&BlinkingTwoFast);
            break;
            
        case _ALWAYS_ON:
            RegisterIntHandler(&AlwaysOn);
            break;
            
        case _ALWAYS_OFF:
            RegisterIntHandler(&AlwaysOff);
            break;
            
        default:
            break;
    }
}

void RegisterIntHandler(Callback pfncb)
{
    pfnCallback = pfncb;
}

void BlinkingOneSlow()
{
    static uint16_t counter = 900;
    static bool on_state = false;
    
    if (counter-- == 0)
    {
        if (on_state)
        {
            LATDbits.LATD1 = 0;    /* turn off LED on RD1 */
            on_state = false;
            counter = 900;
        }
        else
        {
            LATDbits.LATD1 = 1;    /* turn on LED on RD1 */
            on_state = true;
            counter = 100;
        }
    }
}

void BlinkingOneFast()
{
    static uint8_t counter = 0;
    
    if (counter++ >= 100)
    {
        counter = 0;
        LATDbits.LATD1 ^= 1;    /* toggle LED on RD1 */
    }
}

void BlinkingTwoSlow()
{
    static uint16_t counter = 500;
    static uint8_t blinks = 0;
    static bool on_state = false;
    
    if (counter-- == 0)
    {
        if (blinks < 2)
        {
            if (on_state)
            {
                LATDbits.LATD1 = 0;    /* turn off LED on RD1 */
                on_state = false;
                counter = 300;
            }
            else
            {
                LATDbits.LATD1 = 1;    /* turn on LED on RD1 */
                on_state = true;
                counter = 100;
                blinks++;
            }
        }
        else
        {
            LATDbits.LATD1 = 0;    /* turn off LED on RD1 */
            on_state = false;
            counter = 500;
            blinks = 0;
        }
    }
}

void BlinkingTwoFast()
{
    static uint16_t counter = 700;
    static uint8_t blinks = 0;
    static bool on_state = false;
    
    if (counter-- == 0)
    {
        if (blinks < 2)
        {
            if (on_state)
            {
                LATDbits.LATD1 = 0;    /* turn off LED on RD1 */
                on_state = false;
                counter = 100;
            }
            else
            {
                LATDbits.LATD1 = 1;    /* turn on LED on RD1 */
                on_state = true;
                counter = 100;
                blinks++;
            }
        }
        else
        {
            LATDbits.LATD1 = 0;    /* turn off LED on RD1 */
            on_state = false;
            counter = 700;
            blinks = 0;
        }
    }
}

void AlwaysOn()
{
    LATDbits.LATD1 = 1;
}

void AlwaysOff()
{
    LATDbits.LATD1 = 0;
}
