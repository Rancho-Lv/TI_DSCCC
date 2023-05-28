THRESHOLD = (0,26,-6,5,-4,5) # Grayscale threshold for dark things...
import sensor, image, time
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.001, i=0)

sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    line = img.get_regression([(100,100)], roi = (0,0,50,120), robust = True)
    if (line):
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color = (255,0,0))
        print(rho_err,line.magnitude(),rho_err)
        if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            rho_output = rho_pid.get_pid(rho_err,1)
            theta_output = theta_pid.get_pid(theta_err,1)
            output = rho_output+theta_output
            print("output = ",output)
            #car.run(50+output, 50-output)
        else:
            pass
            #car.run(0,0)
    else:
        #car.run(50,-50)
        pass
    #print(clock.fps())
