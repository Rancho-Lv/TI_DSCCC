import sensor, image, time, lcd

# lcd初始化
lcd.init(freq=15000000)

#摄像头初始化
sensor.reset()  # 摄像头重启
sensor.set_pixformat(sensor.RGB565) # 设置摄像头颜色格式为RGB565或GRAYSCALE
sensor.set_framesize(sensor.QVGA)   # 设置分辨率格式为QVGA (320x240)
sensor.skip_frames(time = 2000)     # 设置跳过等待时间
clock = time.clock()                # 设置一个时钟对象用于FPS

while(True):
    clock.tick()                    # 更新FPS时钟
    img = sensor.snapshot()         # 拍摄一张图片存入变量img中
    lcd.display(img)                # 将图片img展示到lcd屏上
    print(clock.fps())              # 打印时钟FPS
