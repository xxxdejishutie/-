import RPi.GPIO as GPIO
from . import motor_module
import time

speed = 0


	
def FanUp():
	global speed
	if speed < 100:
		speed += 10
	print("fan up , speed is ",speed)
	
def FanDown():
	global speed
	if speed <= 0:
		return
	speed -= 10
	if speed <= 0:
		FanStop()
	print("fan down , speed is ",speed)
	
def FanStop():
	global speed
	speed = 0
	print("fan stop")
	
