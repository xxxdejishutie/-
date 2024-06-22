from gpiozero import Servo
from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)

servo = Servo(12)


def OpenDoor():
	servo.value = -1
	sleep(2)
	
def CloseDoor():
	servo.value = 1
	sleep(2)



