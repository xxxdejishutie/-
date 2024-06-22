import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)

FLAME_SENSOR_PIN = 18

GPIO.setup(FLAME_SENSOR_PIN,GPIO.IN)



def GetFlame():
	flame = GPIO.input(FLAME_SENSOR_PIN)
	
	if flame == GPIO.HIGH:
		print("检测到火焰")
		return True
	else:
		print('未检测到火焰')
		return False

#12
