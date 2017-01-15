#include "iostm8s003f3.h"
#include "exti.h"
#include "delay.h"
#include "time.h"
#include "speaker.h"
//#include "intrinsics.h"		//中断控制头文件

int KEY1,KEY2,KEY3,KEY4, KEY_date;
unsigned char temp=0;

void GPIO_KEY_Init(void)
{
    	PC_DDR &= 0xC7;		//按键为PC3/4/5,上拉输入
	PC_CR1 |= 0x38;		//
	PC_CR2 |= 0x38;		//使能引脚中断功能

	PB_DDR_DDR4 = 0;	//触摸电容为PB4,上拉输入
	PB_CR1_C14 = 1;
	PB_CR2_C24 = 1;	       //使能引脚中断功能
        
        PD_DDR_DDR4 = 0;	//红外接收为PD4,上拉输入
	PD_CR1_C14 = 1;
	PD_CR2_C24 = 1;	       //使能引脚中断功能 
	
	//EXTI_CR1 |= 0x08;	//将PB口设置为下降沿触发模式
	EXTI_CR1 |= 0xA8;	//将PBCD口设置为下降沿触发模式
}

#pragma vector=7		//此值为中断向量号加2  PC
__interrupt void EXTI_PORTC_IRQHandler(void)
{
  if(key1==0)
  {
     Delay_ms(10);
     if(key1==0)
     {
       speaker = 1;
       flag_mode = 1;
     KEY1++;
     }
  }
   if(key2==0)
  {
     Delay_ms(10);
     if(key2==0)
     {
       speaker = 2;
       flag_mode = 2;
        KEY2++;
     }
  } 
  if(key3==0)
  {
     Delay_ms(10);
     if(key3==0)
     {
       speaker = 3;
       flag_mode = 3;
        KEY3++;
     }
  }
}
#pragma vector=6		//此值为中断向量号加2  Pb
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  if(key4==0)
  {
     Delay_ms(10);
     if(key4==0)
     {
       speaker = 4;
       flag_mode = 4;
     KEY4++;
     }
  }
}
#pragma vector=8		//  PD此值为中断向量号加2
__interrupt void EXTI_PORTD_IRQHandler(void)
{
   if(date==0)
  {
     //Delay_ms(5);
     if(date==0)
     {
           if( (flag_mode==1) || (flag_mode==5) )
          {
              TIM2_CR1 &= 0XFE;
              TIM2_CNTRH = 0X00;
              TIM2_CNTRL = 0X00;
              TIM2_CR1 |= 0X01;
           if(flag_speaker_on==0)
             {
              
                 if( flag_mode == 1 ) {speaker=5; temp=speaker;}
                 if( flag_mode == 5 ) {speaker=1; temp=speaker;}
               
              }
                
          }
            if( flag_mode==2)
          {
             TIM2_CR1 &= 0XFE;
              TIM2_CNTRH = 0X00;
              TIM2_CNTRL = 0X00; 
              TIM2_CR1 |= 0X01;
             
          }
     KEY_date++;
     if(KEY_date>=3000){KEY_date=0;}
     }
  }
}

