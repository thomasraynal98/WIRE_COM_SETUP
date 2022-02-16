import serial
import time

ser = serial.Serial('/dev/ttyS0', 115200)
i = 0
msg = 'FROM RP4'

while(True):
    mode = msg + " [" + str(i) + "]\n"
    ser.write(mode.encode('utf-8'))
    time.sleep(0.02)
    i += 1