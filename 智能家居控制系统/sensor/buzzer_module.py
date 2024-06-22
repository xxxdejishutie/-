import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)

BuzzerPin = 27
GPIO.setup(BuzzerPin,GPIO.OUT)
GPIO.output(BuzzerPin,GPIO.LOW)


def BuzzerRun():
	GPIO.output(BuzzerPin,GPIO.HIGH)
	sleep(1)
	GPIO.output(BuzzerPin,GPIO.LOW)
	sleep(1)


def ClockOpen():
	GPIO.output(BuzzerPin,GPIO.HIGH)


def ClockClose():
	GPIO.output(BuzzerPin,GPIO.LOW)
