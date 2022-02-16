from cgi import print_environ_usage
import serial
import time

ser = serial.Serial('/dev/ttyS0', 115200)

while(True):
    line = ser.readline()
    print(f"{line}")
    