#include "iostm8s003f3.h"
#include "delay.h"
#include "exti.h"
#include "speaker.h"
#include "time.h"
#include "search.h"
void led_flash();
unsigned char tmp,mode3_flag=0,mode4_flag=0;

unsigned int TMP;


void  led_flash()
{
       TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
  Delay_ms(500);
            TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
   Delay_ms(500);

  for(TMP=0;TMP<Seconds_10;TMP++)
  {
          TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
          
         Delay_ms(100);
         
          TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
          
          Delay_ms(100);
  }
       TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
  Delay_ms(500);
            TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
   Delay_ms(500);
    for(TMP=0;TMP<Minutes_5;TMP++)
  {
          TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
          
         Delay_ms(100);
          
          TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
          
          Delay_ms(100);
  }
         TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
  Delay_ms(500);
            TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
         Delay_ms(500);
    for(TMP=0;TMP<Hours;TMP++)
  {
          TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
          
         Delay_ms(100);
          
          TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
          
          Delay_ms(100);
  }
        TIM1_CCR1H=10/256;
      TIM1_CCR1L=50%256;
       TIM1_CCMR1 |=0X60;//为PWM1模式
  Delay_ms(1000);
            TIM1_CCR1H=0/256;  
          TIM1_CCR1L=0%256;
         TIM1_CCMR1 |=0X60;//为PWM1模式
         Delay_ms(500);
   
   
}
void key_search()
{
  Delay_ms(100);
  seconds=0;
  if(flag_mode==3)
  {
      while(key4)  //如果不行就在加个if语句 在然后判断，  加标志位来退出死循环
      {
        if(key1==0)
        {
          delay_ms(20);
          if(key1==0)
          {Hours++;delay_ms(1000);}
        }
        if(key2==0)
        {
          delay_ms(20);
          if(key2==0)
          {Minutes_5++;delay_ms(1000);}
        }
           if(key3==0)
        {
          delay_ms(20);
          if(key3==0)
          {Seconds_10++;delay_ms(1000);}
        }
      }
   
     
  }
  if(flag_mode ==4)
  {
       while(key3)
      {
        if(key1==0)
        {
          delay_ms(20);
          if(key1==0)
          {Hours++;delay_ms(1000);}
        }
        if(key2==0)
        {
          delay_ms(20);
          if(key2==0)
          {Minutes_5++;delay_ms(1000);}
        }
        if(key4==0)
        {
          delay_ms(20);
          if(key4==0)
          {Seconds_10++;delay_ms(1000);}
        }
      }
      
       
      }
  
  led_flash();
if(flag_mode==3)
{
     speaker = 0;
      mode3_flag =1;
}
else if(flag_mode ==4)
{
  speaker = 2;
      mode4_flag = 1;
}
  
  //Delay_ms(100);
   seconds=0;
 }
//在开启其他模式时，记得清楚其他模式的标志位！！
void switch_search()
{
  if(speaker!=tmp)
  {
    switch(speaker)
    {
      case 1 : 
        {
          flag_mode=1 ;TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;msec=0;somebody=0;
          work_anzhuang();msec=0;  
          tmp = 1;
        }break;   //安装模式
      case 2 :
        {
          Delay_ms(100);
          flag_mode=2 ;TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;msec=0; somebody=0;    //tim2 当前值装回1000
          
          work_gongzuo();
          tmp = 2;
        }break;   //工作模式
    case 3 : 
      {
        flag_mode=3 ;TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0; Hours=0;Minutes_5=0;Seconds_10=0;hours=0;minutes=0;seconds=0;msec=0;  mode3_flag=0;mode4_flag=0;
        //按下按键3，  关闭1 2 4的中断，改成扫描按键，    记得昨晚后要开启中断
        PC_CR2 = 0;
        PB_CR2_C24 = 0;
        key_search();
        PC_CR2 |= 0x38;
        PB_CR2_C24 = 0;
        tmp=3;
      } break;   //定时开模式
    case 4 :  
      {
        flag_mode=4 ;TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;Hours=0;Minutes_5=0;Seconds_10=0;hours=0;minutes=0;seconds=0;msec=0;   mode3_flag=0;mode4_flag=0;
        PC_CR2 = 0;
        PB_CR2_C24 = 0;
        key_search();
        PC_CR2 |= 0x38;
        PB_CR2_C24 = 0;
        tmp = 4;
       }    break;   //定时关模式
         case 5 : 
        {
          flag_mode=5 ;TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;msec=0;somebody=0;
          work_anzhuang();msec=0;  
          tmp = 5;
        }break;   //安装模式
    case 0 :
      { 
                 TIM2_CR1 &= ~0x01;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;hours=0;minutes=0;seconds=0;msec=0;somebody=0;
          msec=0; tmp = 0; 
              } break;
              case 6 :
      { 
                 TIM2_CR1 &= ~0x01;TIM2_EGR &= 0xfe;TIM2_IER &= 0xfe;TIM2_CNTRH = 0X00;TIM2_CNTRL = 0X00;flag_speaker_on=0;flag_speaker_off=0;hours=0;minutes=0;seconds=0;msec=0;somebody=0;
          msec=0; tmp = 0; 
              } break;
      default:break;
     }
    
  }
    
}

