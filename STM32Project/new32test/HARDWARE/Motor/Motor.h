#ifndef __MOTOR_H
#define __MOTOR_H

void ServoControl(float duty_cycle);
void MotorControl(int left_or_right, int direction, float duty_cycle);

#endif