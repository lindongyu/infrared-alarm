#include "iostm8s003f3.h"
#include "delay.h"

unsigned long int count = 0;

void delay_init(void)
{
    TIM4_PSCR = 0X03;
    TIM4_IER = 0X01;
    TIM4_ARR = 250;
    TIM4_CNTR = 250;
    
}
 
void delay_ms(unsigned int num)
{
  unsigned long int tmp;
  tmp = count; 
  while( (count-tmp  <= num) );
}

#pragma vector = 25
__interrupt void TIME4_Interrupt(void)  //1ms
{
    TIM4_SR = 0X00;
    count ++;
}

void Delay_ms(unsigned int num)
{
  unsigned char i;
  while(num--){
    for(i=0;i<100;i++);}
}