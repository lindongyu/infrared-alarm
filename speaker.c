#include "iostm8s003f3.h"
#include "speaker.h"
#include "delay.h"
#include "time.h"

unsigned char speaker=0,flag_speaker_on=0,flag_speaker_off=0,somebody=0;


void speaker_on(void)
{
  flag_speaker_on=1;
  flag_speaker_off=0;
  
    if(flag_mode==2)
  {
    somebody=1;
      while(flag_mode==2)
      {
  TIM1_CCR1H=10/256;
  TIM1_CCR1L=50%256;
   TIM1_CCMR1 |=0X60;//为PWM1模式
          
          Delay_ms(100);
          
  TIM1_CCR1H=10/256;
  TIM1_CCR1L=0%256;
   TIM1_CCMR1 |=0X60;//为PWM1模式
          
          Delay_ms(100);
      }
  }
  
  else if( (flag_mode==1)||(flag_mode==5) )
  {
      while( ((flag_mode==1)||(flag_mode==5)) && (flag_speaker_on ==1) )
      {
      TIM1_CCR1H=10/256;
      TIM1_CCR1L=1%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
          
         Delay_ms(100);
          
          TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
          
          delay_ms(1000);
      }
  }

    TIM1_CCR1H=0/256;
  TIM1_CCR1L=0%256;
   TIM1_CCMR1 |=0X60;//为PWM1模式
}  
void speaker_off()
{
  flag_speaker_off=1;
  flag_speaker_on=0;
          TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
          TIM1_CCMR1 |=0X60;//为PWM1模式
}
  
void work_gongzuo(void)
{
    TIM2_CR1 |= 0x01;		//cen使能定时器
}


void work_anzhuang(void)
{
    TIM2_CR1 |= 0X01;
    speaker_on();
}


 
