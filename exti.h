#ifndef __EXTI_H_
#define __EXTI_H_

void GPIO_KEY_Init(void);
extern unsigned char temp;
#define key3 PC_IDR_IDR3	//将PA口的bit4定义为key0
#define key2  PC_IDR_IDR4
#define key1  PC_IDR_IDR5
#define key4  PB_IDR_IDR4
#define date  PD_IDR_IDR4

#endif