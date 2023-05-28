#include "MyUsart.h"	
#include "usart.h"
#include "main.h"
#include "stdlib.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma (__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
uint8_t data;

/*
���ڻص�����
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 com_data; 
	u8 i;
	static u8 RxCounter1=0;
	static u16 RxBuffer1[6]={0};
	static u8 RxState = 0;

	u16 Rx_Data;
	
	if(huart->Instance==USART1)//����Ǵ���1
	{
				com_data = data;
				if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
					HAL_GPIO_TogglePin(led_GPIO_Port,led_Pin);
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
					HAL_GPIO_TogglePin(led_GPIO_Port,led_Pin);
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1==6 && com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						
						Rx_Data=((RxBuffer1[RxCounter1-4]-48)*100)+((RxBuffer1[RxCounter1-3]-48)*10)+(RxBuffer1[RxCounter1-2]-48);
						PWM = Rx_Data;
						printf("%d\r\n",PWM);
						RxState = 0;
						
					}
					else if(RxCounter1 > 6)            //�����쳣
					{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
					
					}
				}
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}
 
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&data, 1); 
}

/*�����������ֱ�Ӱ��жϿ����߼�д���жϷ������ڲ���*/

//����1�жϷ������
//void USART1_IRQHandler(void)                	
//{ 
//	u8 Res;
//	HAL_StatusTypeDef err;
//#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
//	OSIntEnter();    
//#endif
//	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res=USART1->DR; 
//		if((USART_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//			}
//			else //��û�յ�0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//	}
//	HAL_UART_IRQHandler(&UART1_Handler);	
//#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
//	OSIntExit();  											 
//#endif
//} 
//#endif	


