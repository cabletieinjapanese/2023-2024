# This work is licensed under the MIT license.
# Copyright (c) 2013-2023 OpenMV LLC. All rights reserved.
# https://github.com/openmv/openmv/blob/master/LICENSE
#
# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor
import time
import math
import random
import pyb

sensor.reset()  # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565)  # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)  # Set frame size to QVGA (320x240)
sensor.skip_frames(time=2000)  # Wait for settings take effect.
clock = time.clock()  # Create a clock object to track the FPS.
uart = pyb.UART(3,100000,bits=8)

SCREEN_X = 320
SCREEN_Y = 240

ball = (63, 100, 9, 127, 20, 127)

while True:
    img = sensor.snapshot()
    img.scale(1,1)
    data = 0

    blobs = img.find_blobs([ball],x_stride=10,y_stride=1,pixels_threshold=10,merge=True)
    record_size = 0
    record_blob = False
    for blob in blobs:
        if blob.area() > 10000:
            pass
        elif blob.area() > record_size:
            record_blob = blob
            record_size = blob.area()

    if record_blob:
        img.draw_rectangle(record_blob[0:4]) # rect
        img.draw_cross(record_blob[5], record_blob[6])
        data = math.floor(record_blob.cxf() * 1000 + record_blob.cyf())

    clock.tick()  # Update the FPS clock.
    for byte in range(uart.any()):
        print(uart.readchar())

    bit_length = len(bin(data)[2:])
    offset = 0
    while offset < bit_length:
        packet = 0
        if offset+5 >= bit_length:
            complete_marker = 1
        else:
            complete_marker = 0

        identifier = 0
        payload = math.floor((data % math.pow(2,offset+5) / math.pow(2,offset)))
        packet = complete_marker * 128 + identifier * 32 + payload
        print(packet)
        uart.writechar(packet)
        offset += 5


    completeness = 0 #is the packet a complete signal? (0/1)
    identifier = 2 #what type of signal is this packet? (0 ~ 3)
     #data (0 ~ 31)

