#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "MyUsart.h"
#include "Motor.h"

/*
������ƺ�����
����ֵ����		������float���͵�ռ�ձ�ֵx%
ע��
	7ռ�ձȵ�ʱ�������м�λ�ã����ʹ�õ��� TIM_1��Channel_1 -> PE9
*/
void ServoControl(float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 2.5)	//���ƶ��PWM��ΧΪ20%-12.5%ռ�ձȣ��������ռ���ֵ��
	{
		duty_cycle = 2.5;
	}
	else if(duty_cycle > 12.5)
	{
		duty_cycle = 12.5;
	}

	pwm = (duty_cycle /100) * 20000.0;		//����Ϊpwm��ֵ������ֵΪ20000

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
}

/*
������ƺ�����
����ֵ����		������int���͵����ҵ��ѡ��	0->���� 1->�ҵ��
									int���͵�ǰ�����˻�ֹͣѡ��	0->ǰ��	1->���� 2->ֹͣ
									float���͵�ռ�ձ�ֵx%
ע��
	����pwmA�� -> TIM_1��Channel_2 -> PE11
	�ҵ��pwmB�� -> TIM_1��Channel_3 -> PE13
	AIN1 -> PF0		10
	AIN2 -> PF1
	BIN1 -> PF2		10
	BIN2 -> PF3
	STBY -> PF4
*/
void MotorControl(int left_or_right, int direction, float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 0)	//���ƶ��PWM��ΧΪ0%-100%ռ�ձȣ��������ռ���ֵ��
	{
		duty_cycle = 0;
	}
	else if(duty_cycle > 100)
	{
		duty_cycle = 100;
	}
	pwm = (duty_cycle /100) * 20000.0;		//����Ϊpwm��ֵ������ֵΪ20000
	
	
	if(left_or_right == 0)	//������ ���� �ҵ�� 0->���� 1->�ҵ��
	{
		if(direction == 0)//���Ƶ��ǰ�����˻�ֹͣ	0->ǰ��	1->���� 2->ֹͣ
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
		}
		else if(direction == 1)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		}
		else if(direction == 2)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
		}
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
		
		}
	else
	{
		if(direction == 0)//���Ƶ��ǰ�����˻�ֹͣ	0->ǰ��	1->���� 2->ֹͣ
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
		}
		else if(direction == 1)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
		}
		else if(direction == 2)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
		}

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
	}
	
}
