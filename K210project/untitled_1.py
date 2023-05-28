# Untitled - By: 13369 - 周一 2月 27 2023

import sensor, lcd, image# , time
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(40)

lcd.init() #LCD 初始化
lcd.rotation(2)

sensor.skip_frames(time = 1000) # 缓1秒
print("GOOD JOB")
# 拍摄并保存相关文件，也可以用".bmp"或其它文件方式。
x = 0
while True:
    x += 1
    sensor.snapshot().save("/sd/BanMaXian"+str(x)+".jpg")   #存储到SD卡中名称是xianyu.jpg
    print(x)

    lcd.display(image.Image("/sd/BanMaXian"+str(x)+".jpg")) #LCD 显示照片
    # time.delay(1000)
