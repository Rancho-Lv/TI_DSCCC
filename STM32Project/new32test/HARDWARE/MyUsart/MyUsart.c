#include "MyUsart.h"	
#include "usart.h"
#include "main.h"
#include "stdlib.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma (__use_no_semihosting)             
//标准库需要的支持函数                 
struct FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
uint8_t data;

/*
串口回调函数
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 com_data; 
	u8 i;
	static u8 RxCounter1=0;
	static u16 RxBuffer1[6]={0};
	static u8 RxState = 0;

	u16 Rx_Data;
	
	if(huart->Instance==USART1)//如果是串口1
	{
				com_data = data;
				if(RxState==0&&com_data==0x2C)  //0x2c帧头
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
					HAL_GPIO_TogglePin(led_GPIO_Port,led_Pin);
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
					HAL_GPIO_TogglePin(led_GPIO_Port,led_Pin);
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1==6 && com_data == 0x5B)       //RxBuffer1接受满了,接收数据结束
					{
						
						Rx_Data=((RxBuffer1[RxCounter1-4]-48)*100)+((RxBuffer1[RxCounter1-3]-48)*10)+(RxBuffer1[RxCounter1-2]-48);
						PWM = Rx_Data;
						printf("%d\r\n",PWM);
						RxState = 0;
						
					}
					else if(RxCounter1 > 6)            //接收异常
					{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
					
					}
				}
				else   //接收异常
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
				}
 
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&data, 1); 
}

/*下面代码我们直接把中断控制逻辑写在中断服务函数内部。*/

//串口1中断服务程序
//void USART1_IRQHandler(void)                	
//{ 
//	u8 Res;
//	HAL_StatusTypeDef err;
//#if SYSTEM_SUPPORT_OS	 	//使用OS
//	OSIntEnter();    
//#endif
//	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		Res=USART1->DR; 
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//		{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//			}
//			else //还没收到0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//				}		 
//			}
//		}   		 
//	}
//	HAL_UART_IRQHandler(&UART1_Handler);	
//#if SYSTEM_SUPPORT_OS	 	//使用OS
//	OSIntExit();  											 
//#endif
//} 
//#endif	


