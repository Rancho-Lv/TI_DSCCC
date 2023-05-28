from pyb import Pin, Timer, delay
#将 LED(4)-"F10"配置成推挽输出模式
ain1_pa0=Pin('A0',Pin.OUT_PP)
ain2_pa1=Pin('A1',Pin.OUT_PP)
bin1_pa2=Pin('A2',Pin.OUT_PP)
bin2_pa3=Pin('A3',Pin.OUT_PP)
stby_pa4=Pin('A4',Pin.OUT_PP)

pwma_a6 = Pin('A6') # X1 has TIM2, CH1
pwmb_a7 = Pin('A7') # X1 has TIM2, CH1
pwm_b0 = Pin('B0')
tim = Timer(3, freq=50)
pwma = tim.channel(1, Timer.PWM, pin=pwma_a6)
pwmb = tim.channel(2, Timer.PWM, pin=pwmb_a7)
pwm = tim.channel(3, Timer.PWM, pin=pwm_b0)



while True:
    ain1_pa0.low() #点亮 LED（4）蓝灯
    ain2_pa1.high() #关闭 LED（4）蓝灯
    bin2_pa3.high() #点亮 LED（4）蓝灯
    bin1_pa2.low() #关闭 LED（4）蓝灯
    stby_pa4.high() #点亮 LED（4）蓝灯
    pwma.pulse_width_percent(50)
    pwmb.pulse_width_percent(50)
#     for i in range(100):
#         print(i)
#         pyb.delay(500)
    pwm.pulse_width_percent(8.5)
    
    pyb.delay(5000)
    
    ain1_pa0.low() #点亮 LED（4）蓝灯
    ain2_pa1.low() #关闭 LED（4）蓝灯
    bin2_pa3.low() #点亮 LED（4）蓝灯
    bin1_pa2.low() #关闭 LED（4）蓝灯
    stby_pa4.low() #点亮 LED（4）蓝灯
    pwma.pulse_width_percent(0)
    pwmb.pulse_width_percent(0)
    pwm.pulse_width_percent(3)
    
    pyb.delay(2000)
    
 
 