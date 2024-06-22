from sensor import temp_module
from sensor import fan_module
from sensor import led_module
from sensor import flame_module
from sensor import camera_module
from sensor import buzzer_module
from sensor import motor_module
from sensor import servo_moudle
import json
from net import net
from time import sleep
import threading

#WaringLock = threading.RLock()


CloseFlag = False
TargetTemp = 28.0
WaringFlag = False

class Kernel:
	writeTemp = None
	def __init__(self):
		writeTemp = threading.Thread(target = temp_module.WriteTemp)
		writeTemp.start()
		net.ClientProgram()
		controltemp = threading.Thread(target = self.controltemp)
		controltemp.start()
		
		controlflame = threading.Thread(target = self.controlFlame)
		controlflame.start()
		
		pass
		
		
	def Run(self):
		global WaringFlag
		global TargetTemp 
		while True:
			response = net.NetRecv() 
			cmd = response[0]
			#cmd = '5'
			match cmd:
				case '0':
					if response[1] == '0':
						continue
					a = 0.0
					a += int(response[1])
					a *= 10
					a += int(response[2])
					TargetTemp = a
				case '1':
					print('will open led')
					led_module.led.on()
					print('have opened led')
					#open led
				case '2':
					print('will close led')
					led_module.led.off()
					print('have closed led')
					#close ledd
				case '3':
					print('will open chuan')
					motor_module.MotorFront()
					print('have opened chuan')
					#open 
				case '4':
					print('will close chuan')
					motor_module.MotorBack()
					print('have closed chuan')
					#close
				case '5':
					print('have input password')
					servo_moudle.OpenDoor()
					servo_moudle.CloseDoor()
					print('have opened door')
				case '7':
					WaringFlag = False
					print('have closed baojing')
					
				case '8':
					print('morning')
					if WaringFlag:
						continue
					buzzer_module.ClockOpen()
					print('have opened clock')
				case '9':
					print('clock close')
					if WaringFlag:
						continue
					buzzer_module.ClockClose()
					print('have closed clock')
				
			sleep(1)
			
	def controltemp(self):
		kp = 1.0
		ki = 0.05
		kd = 0.01
		
		lastError = 0
		integral = 0
		
		global TargetTemp
		
		currentTemp = 30.0
		
		while True:
			if CloseFlag == True:
				sleep(10)
				return
			sleep(2)
			currentTemp = temp_module.ReadTemp()
			
			
			errorTemp =  currentTemp - TargetTemp
			print('目标温度为 ： ',TargetTemp,'当前温度为 ： ',currentTemp,' 误差为 ： ',errorTemp)
			if errorTemp < 0:
				lastError = 0
				integral = 0
				motor_module.FanStop()
				continue
			
			
			integral += errorTemp
			derivate = errorTemp - lastError
			
			output = kp * errorTemp + ki * integral + kd * derivate
			
			lastError = errorTemp
			
			motor_module.FanSpeed(output)
			#if temp > 28:
			#	fan_module.FanUp()
			#else:
			#	fan_module.FanDown()
	
	def controlFlame(self):
		while True:
			global WaringFlag
			if CloseFlag == True:
				print('[CloseFlag] flame close')
				sleep(10)
				return
			sleep(1)
			flame = flame_module.GetFlame()
			if flame == True:
				WaringFlag = True
				#抓拍，发送报警包
				image = camera_module.GetImage()
				net.NetSend(image)
				#data = {
				#	"num" : "6",
				#	"image" : image
				#}
				#net.NetSend(json.dumps(data))
				print('buzzer')
				while WaringFlag:
					buzzer_module.BuzzerRun()
				
			#else
				#continue
	
	


def main(args):
	ker = Kernel()
	ker.Run()
	return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))




	
