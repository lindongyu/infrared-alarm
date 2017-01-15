#include "iostm8s003f3.h"
#include "time.h"
#include "speaker.h"
#include "search.h"

unsigned int hours,minutes, seconds, msec,Hours,Minutes_5,Seconds_10;
char flag_time=0,HOUERS = 0;
long int test = 0,test2=0;
char flag_mode = 0;

void  GPIO_PWM_INIT(void)   // PCC  TIM1 CH3    
{   
    PC_DDR |= 0x40;
    PC_CR1 |= 0x40;
    PC_CR2 |= 0x40;
    
    PC_ODR &= 0xBF;

}

void TIM1_Config(void)   // 5k  hz
{                     
			
  TIM1_PSCRH = 0;  //置预分频系数32，即频率为2M/32=62500  注意不同定时器的分频计算公式
  TIM1_PSCRL = 3;   //0.5m
  TIM1_ARRH=0x00;  //设置自动装载寄存器的值为 62500，那么定时中断周期刚好为1s
  TIM1_ARRL=0X64;  //64

  TIM1_CCR1H=0/256;
  TIM1_CCR1L=0%256;
  TIM1_CCMR1 |=0X60;//为PWM1模式
   
  	TIM1_CR1 |= 0x04;		//URS设置为更新s时计数器不停止，且仅计数器溢出时中断有效
	TIM1_EGR |= 0x01;		//UG 产生一个更新事件，触发重装并初始化计数器
	TIM1_IER |= 0x01;		//_UIE允_UIE许更新中断
  
  TIM1_CCER1 |=0X01;//开启输出，高电平有效
  TIM1_OISR |=0X01;//空闲状态为高
  TIM1_BKR |=0X80;
}

void TIM2_Config(void)
{
	TIM2_PSCR = 3;			//1M
	TIM2_ARRH = 0x61;		//设置自动装载寄存器的值为 1000，那么定时中断周期刚好为1Ms
	TIM2_ARRL = 0xA8;		
	TIM2_CR1 |= 0x04;		//urs设置为更新s时计数器不停止，且仅计数器溢出时中断有效
	TIM2_EGR |= 0x01;		//UG产生一个更新事件，触发重装并初始化计数器
	TIM2_IER |= 0x01;		//UIE允UIE许更新中断
	
}


#pragma vector = 13
__interrupt void TIM1_Overflow_IRQHandler(void)
{
  TIM1_SR1 = 0x00;		//清除中断标志
  test++;
  if((mode3_flag==1)||(mode4_flag==1))
  {
      if(test >= 5000)
      {
            seconds ++;
           test = 0;
                              if((hours==Hours)&&((Minutes_5*5)==minutes)&&((Seconds_10*10)==seconds)) 
                       {
                         hours=0;
                         minutes=0;
                         seconds=0;
                         Hours=0;
                         Minutes_5=0;
                         Seconds_10=0;
                           if(mode4_flag==1)
                           {
                            //speaker = 0;    //待机
                             speaker = 6; 
                             mode4_flag=0;

                           }
                           else if(mode3_flag==1)
                           {
                            speaker = 2;
                            mode3_flag=0;
                           }
                       }
           
           if(seconds>59)			//seconds超出59后清零，minutes加1
          {
             seconds = 0;
             minutes ++;

             if(minutes>59)		//minutes超出59后清零
             {
               hours++;
               minutes=0;
             }  
          }
      }
  }
}



#pragma vector = 15
__interrupt void TIM2_Overflow_IRQHandler(void)

{
  
	TIM2_SR1 = 0x00;		//清除中断标志
	//msec ++;				//每 1ms中断一次，
	//if(msec>=100)			//
	//{
         test2++;
         
		msec = 0;
              if(flag_mode==2)
                {
		speaker_on();
                }
                if( (flag_mode==1) || (flag_mode==5) )
                {
                speaker_off();  //此时TIM2 还在继续跑
                }
     //  }

 
    
 }




