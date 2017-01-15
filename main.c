#include "iostm8s003f3.h"
#include "time.h"
#include "delay.h"
#include "exti.h"
#include "search.h"
#include "speaker.h"

void main() 
{
  
  delay_init();
    GPIO_PWM_INIT();
  TIM1_Config();   // 5khz pwm 
  TIM2_Config();
  GPIO_KEY_Init();
  
  ITC_SPR2 |= 0XFF;   // 11
  ITC_SPR3 &= 0XBF;   //  76=> 10
  ITC_SPR4 &= 0XF7;   // 32 => 01
  ITC_SPR6 &= 0X7F;   //76 => 01
  
  
   asm("RIM");	//¿ªÆô×ÜÖÐ¶Ï 
  TIM1_CR1 |= 0X01;
    TIM4_CR1 |= 0X01;
   // TIM2_CR1 |= 0X01;
    speaker =0 ;
    tmp = 0;
  while(1)
  {
     switch_search(); 
   }
}