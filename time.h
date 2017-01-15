#ifndef __TIME_H_
#define __TIME_H_
#include "iostm8s003f3.h"

extern char flag_time, HOURS;
extern char flag_mode;
extern unsigned int hours,minutes, seconds, msec,Hours,Minutes_5,Seconds_10;

void  GPIO_PWM_INIT(void);
void TIM1_Config(void);
void TIM2_Config(void);
#endif