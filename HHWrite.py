# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

"""
from serial.tools.list_ports import comports

for port in comports():
    print(port)
"""

import serial
import time

arduino = serial.Serial('COM6', 9600, timeout=0.1)
time.sleep(3)

def HHWrite(axis, current):
    arduino.write('H'.encode('ascii'))
    arduino.write(axis.encode('ascii'))
    arduino.write(str(current).encode('ascii'))
    time.sleep(0.1)
    while (arduino.in_waiting == 0):
        pass
    arduino.read()
    return arduino.read_until()

userInput = input("> ")
while userInput != "STOP":
    """
    arduino.write(userInput.encode('ascii'))
    time.sleep(0.1)
    if arduino.in_waiting > 0:
        print(arduino.read_until())
    """
    print(HHWrite(userInput[0], userInput[1:]))
    userInput = input("> ")
    


arduino.close()