#将 LED(4)-"F10"配置成推挽输出模式
#pwm_a_a2=Pin('A2',Pin.OUT_PP)

#pwm_b_a3=Pin('A3',Pin.OUT_PP)

from pyb import Pin, Timer

p = Pin('X1') # X1 has TIM2, CH1
tim = Timer(2, freq=1000)
ch = tim.channel(1, Timer.PWM, pin=p)

ch.pulse_width_percent(50)
    
