from cgi import print_environ_usage
import serial
import time

ser = serial.Serial('/dev/ttyS0', 9600)

while(True):
    line = ser.readline()
    print(f"{line}")
    