# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time, lcd, math, time#, pyb
from fpioa_manager import fm
from machine import UART

# IO9 -> TX  IO10 -> RX
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)

# 创建一个串口对象 波特率115200
uart_A = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096)

# 设置黑线阈值
Black_Line_THRESHOLD = (5, 40, -9, 4, -3, 11)
# QVGA:
#roi_area_1 = (0,50,320,50)
#roi_area_2 = (50,50,50,240)
#roi_area_3 = (320-50,50,320-50,240)

# QQVGA2:
# 划分三个区域，分别用来检测他们区域内的黑块
roi_area_1 = (0,50,320,50)
roi_area_2 = (50,50,50,240)
roi_area_3 = (320-50,50,320-50,240)

# 创建三个区域识别到的色块坐标变量
色块对象1的x坐标 = 0
色块对象1的y坐标 = 0
色块对象2的x坐标 = 0
色块对象2的y坐标 = 0
色块对象3的x坐标 = 0
色块对象3的y坐标 = 0

# 创建斜率计算变量
y坐标变化量 = 0
x坐标变化量 = 0
斜率k = 0
y中心坐标 = 0
距离 = 0
交点 = 0
i = 0
交点出现次数 = 0

sensor.reset(dual_buff=True) # 初始化重置摄像头，默认频率24MHZ，双缓冲dual_buff默认为false
                             # 提高频率可以增加帧率，但画质可能降低。开启双缓冲可以提高帧率，
                             # 但是会增加内存的占用
sensor.set_vflip(1) # 垂直翻转 1 -> 开 0 -> 关
sensor.set_hmirror(0)   #水平翻转 1 -> 开 0 -> 关
sensor.set_pixformat(sensor.RGB565)  # 设置摄像头颜色格式为RGB565或GRAYSCALE
sensor.set_framesize(sensor.QVGA)   # 设置分辨率格式为QVGA (320x240)
sensor.run(1)   # 开启摄像头
sensor.skip_frames(time = 2000)     # 设置跳过等待时间
clock = time.clock()                # 设置一个时钟对象用于FPS
lcd.init() # 初始化LCD屏幕

#def find_max(blobs):
    #max_size=0
    #for blob in blobs:
        #if blob[2]*blob[3] > max_size:
            #max_blob=blob
            #max_size = blob[2]*blob[3]
    #return max_blob


while(True):
    try:
        clock.tick()                    # Update the FPS clock.
        img = sensor.snapshot()         # 拍一张照片，返回一个对象保存到img变量中
        fps = int(clock.fps())
        img.draw_string(0,20,"{}".format(fps))
        img.draw_line(roi_area_1, color = (255,0,0))    # 划分区域1，用来识别节点
        img.draw_string(0,0,"1")
        img.draw_line(roi_area_2, color = (255,0,0))    # 划分区域2，跟踪黑线负（x0，y0）
        img.draw_string(0,50,"2")
        img.draw_line(roi_area_3, color = (255,0,0))    # 划分区域，跟踪黑线负（x0，y0）
        img.draw_string(320-50,50,"3")

        色块类1 = img.find_blobs([Black_Line_THRESHOLD], roi = (0, 0, 320, 50), area_threshold = 450)
        色块类2 = img.find_blobs([Black_Line_THRESHOLD], roi = (0, 50, 50, 240-50), area_threshold = 500)
        色块类3 = img.find_blobs([Black_Line_THRESHOLD], roi = (320-50, 50, 50, 240-50), area_threshold = 500)

        if 色块类1:
            if(len(色块类1) == 1):
                交点 = True
                for 色块对象1 in 色块类1:
                    色块对象1的x坐标 = 色块对象1.cx()
                    色块对象1的y坐标 = 色块对象1.cy()
                    色块对象1的中心坐标 = (色块对象1.cx(), 色块对象1.cy())
                    img.draw_rectangle(色块对象1.rect())
                    img.draw_cross(色块对象1的x坐标, 色块对象1的y坐标, size=5)
        else:
            交点 = False

        if 交点 == True:
            i += 1
            if i == 3:   #i == 3
                交点出现次数 += 1
        else:
            i = 0

        距离显示字符串 = str(交点出现次数)
        img.draw_string(64, 30, 距离显示字符串)
        #print("i：{}".format(i))
        if 色块类2:
            if(len(色块类2) == 1):
                for 色块对象2 in 色块类2:
                    色块对象2的密度 = 色块对象2.density()
                    print("色块对象2的密度:{}".format(色块对象2的密度))
                    if (色块对象2的密度 > 0.7):
                        色块对象2的x坐标 = 色块对象2.cx()
                        色块对象2的y坐标 = 色块对象2.cy()
                        area_2_blob_pixels = 色块对象2.pixels()
                        img.draw_rectangle(色块对象2.rect())
                        img.draw_cross(色块对象2的x坐标, 色块对象2的y坐标, size=5)
                    else:
                        #print("区域2色块的密度小于75%")
                        pass
            else:
                #print("区域2出现多个色块")
                pass
        if 色块类3:
            if (len(色块类3) == 1):
                for 色块对象3 in 色块类3:
                    色块对象3的密度 = 色块对象3.density()
                    print("色块对象3的密度:{}".format(色块对象2的密度))
                    if (色块对象3的密度 > 0.7):
                        色块对象3的x坐标 = 色块对象3.cx()
                        色块对象3的y坐标 = 色块对象3.cy()
                        area_3_blob_pixels = 色块对象3.pixels()
                        img.draw_rectangle(色块对象3.rect())
                        img.draw_cross(色块对象3的x坐标, 色块对象3的y坐标, size=5)
                    else:
                        #print("区域3色块的密度小于60%")
                        pass
            else:
                #print("区域3出现多个色块")
                pass

        y坐标变化量 = (色块对象2的y坐标 - 色块对象3的y坐标)
        x坐标变化量 = (色块对象2的x坐标 - 色块对象3的x坐标)
        斜率k = y坐标变化量 / x坐标变化量
        y中心坐标 = (abs(色块对象3的y坐标 - 色块对象2的y坐标) / 2)

        if (y坐标变化量 > 0):
            距离 = 145 - (y中心坐标 + 色块对象3的y坐标)
        elif (y坐标变化量 < 0):
            距离 = 145 - (y中心坐标 + 色块对象2的y坐标)

        img.draw_line((色块对象2的x坐标, 色块对象2的y坐标, 色块对象3的x坐标, 色块对象3的y坐标), color = (0,255,0))
        img.draw_line((int((色块对象2的x坐标 + 色块对象3的x坐标) / 2), int((色块对象2的y坐标 + 色块对象3的y坐标) / 2), 160, 240), color = (0,255,0))
        #斜率显示字符串 = str(斜率k * 1000)
        #距离显示字符串 = str(距离 * 10)
        #uart_A.write("{}".format(距离 * 10)+"\r\n")
        #uart_A.write("{}".format(斜率k * 1000)+"\r\n")

        uart_A.write(0XBF);
        uart_A.write(0XFB);
        img.draw_string(int((色块对象2的x坐标 + 色块对象3的x坐标) / 2), int((色块对象2的y坐标 + 色块对象3的y坐标) / 2), "{}".format(斜率k * 1000))
        img.draw_string(160, 230, "{}".format(距离 * 10))
        #print("倾斜：{}".format(斜率k * 1000), "距离：{}".format(距离 * 10))
        lcd.display(img)
        #print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                        # to the IDE. The FPS should increase once disconnected.

    except Exception as e:
        print("Exception is ", e)
