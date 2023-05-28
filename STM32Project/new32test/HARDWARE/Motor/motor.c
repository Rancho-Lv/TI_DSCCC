#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "MyUsart.h"
#include "Motor.h"

/*
舵机控制函数：
返回值：无		参数：float类型的占空比值x%
注：
	7占空比的时候大概在中间位置，舵机使用的是 TIM_1的Channel_1 -> PE9
*/
void ServoControl(float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 2.5)	//限制舵机PWM范围为20%-12.5%占空比，超出按照极限值算
	{
		duty_cycle = 2.5;
	}
	else if(duty_cycle > 12.5)
	{
		duty_cycle = 12.5;
	}

	pwm = (duty_cycle /100) * 20000.0;		//换算为pwm数值，计数值为20000

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
}

/*
电机控制函数：
返回值：无		参数：int类型的左右电机选择	0->左电机 1->右电机
									int类型的前进后退或停止选择	0->前进	1->后退 2->停止
									float类型的占空比值x%
注：
	左电机pwmA口 -> TIM_1的Channel_2 -> PE11
	右电机pwmB口 -> TIM_1的Channel_3 -> PE13
	AIN1 -> PF0		10
	AIN2 -> PF1
	BIN1 -> PF2		10
	BIN2 -> PF3
	STBY -> PF4
*/
void MotorControl(int left_or_right, int direction, float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 0)	//限制舵机PWM范围为0%-100%占空比，超出按照极限值算
	{
		duty_cycle = 0;
	}
	else if(duty_cycle > 100)
	{
		duty_cycle = 100;
	}
	pwm = (duty_cycle /100) * 20000.0;		//换算为pwm数值，计数值为20000
	
	
	if(left_or_right == 0)	//控制左 或者 右电机 0->左电机 1->右电机
	{
		if(direction == 0)//控制电机前进后退或停止	0->前进	1->后退 2->停止
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
		if(direction == 0)//控制电机前进后退或停止	0->前进	1->后退 2->停止
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
