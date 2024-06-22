import RPi.GPIO as GPIO
from time import sleep
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

MotorPin = 22
MotorPin2 = 23


GPIO.setup(MotorPin,GPIO.OUT)
pwm = GPIO.PWM(MotorPin,100)

GPIO.setup(MotorPin2,GPIO.OUT)
pwm2 = GPIO.PWM(MotorPin2,100)

pwm.start(0)
pwm2.start(0)

def MotorFront():
	pwm.ChangeDutyCycle(0)
	sleep(2)
	pwm.ChangeDutyCycle(100)
	sleep(2)
	pwm.ChangeDutyCycle(0)
	#FanStop()


def MotorBack():
	pwm2.ChangeDutyCycle(0)
	sleep(2)
	pwm2.ChangeDutyCycle(100)
	sleep(2)
	pwm2.ChangeDutyCycle(0)
	#FanStop()

def FanSpeed(val):
	global pwm
	print('speed is ',int(val * 10))
	#pwm2.stop(0)
	#pwm2.ChangeDutyCycle(0)
	speed = int(val * 10)
	if speed > 100:
		speed = 100
	pwm.ChangeDutyCycle(100)
	sleep(1)
	#FanStop()


def FanStop():
	print('speed is 0')
	pwm.ChangeDutyCycle(0)



def MotorAddAndSub():
	try:
		while True:
			#pwm2.stop()
			#for dutyCycle in range(0,101,10):
			FanSpeed(2)
			#pwm.ChangeDutyCycle(60)
			sleep(0.5)
			#for dutyCycle in range(100,-1,-10):
				#pwm.ChangeDutyCycle(dutyCycle)
			#	sleep(0.5)
	except KeyboardInterrupt:
		pwm.stop()
		GPIO.cleanup()

#MotorAddAndSub()
