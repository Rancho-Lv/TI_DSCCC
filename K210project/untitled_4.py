# Untitled - By: 13369 - 周二 2月 28 2023

import sensor, image, lcd, time
import KPU as kpu
import gc, sys
from machine import Timer,PWM
from Maix import GPIO

ain_1=GPIO(GPIO.GPIO0,GPIO.OUT)
ain_2=GPIO(GPIO.GPIO1,GPIO.OUT)
bin_1=GPIO(GPIO.GPIO2,GPIO.OUT)
bin_2=GPIO(GPIO.GPIO3,GPIO.OUT)
stby = GPIO(GPIO.GPIO4,GPIO.OUT)
print("1")

tim = Timer(Timer.TIMER0, Timer.CHANNEL0, mode=Timer.MODE_PWM)
tim1 = Timer(Timer.TIMER0, Timer.CHANNEL1, mode=Timer.MODE_PWM)
tim2 = Timer(Timer.TIMER0, Timer.CHANNEL2, mode=Timer.MODE_PWM)

ch1 = PWM(tim, freq=50, duty=0, pin=33)
ch2 = PWM(tim1, freq=50, duty=0, pin=34)
ch3 = PWM(tim2, freq=50, duty=0, pin=35)
while True:
    print("2")
    stby.value(1)
    ain_1.value(1)
    ain_2.value(0)
    bin_1.value(0)
    bin_2.value(1)
    ch1.duty(duty)
    ch2.duty(duty)
    ch3.duty(duty2)

    time.sleep(5)

    ch1.duty(0)
    ch2.duty(0)
    ch3.duty(2.5)
    stby.value(0)
    ain_1.value(0)
    ain_2.value(0)
    bin_1.value(0)
    bin_2.value(0)

    time.sleep(5)
    print("3")

