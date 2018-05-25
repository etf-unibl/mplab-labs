/* 
 * File:   timerctrl.h
 * Author: mknezic
 *
 * Created on May 24, 2018, 1:28 PM
 */

#ifndef TIMERCTRL_H
#define	TIMERCTRL_H

#include <stdint.h>
#include <stdbool.h>

#define _1_BLINK_SLOW   0
#define _1_BLINK_FAST   1
#define _2_BLINK_SLOW   2
#define _2_BLINK_FAST   3
#define _ALWAYS_ON      4
#define _ALWAYS_OFF     5

typedef void (*Callback)();

#ifdef	__cplusplus
extern "C" {
#endif

void ChangeMode(uint8_t mode);
void RunStop();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERCTRL_H */

