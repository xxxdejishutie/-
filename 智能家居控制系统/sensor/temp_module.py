from w1thermsensor import W1ThermSensor
import threading
from time import sleep


tempSensor = W1ThermSensor()
temp = None
lock = threading.RLock()

def WriteTemp():
    global temp
    while True:
        with lock:
            try:
                temp = tempSensor.get_temperature()
                #print("write temp is ",temp)
            except Exception as ex:
                print("temp error")
        sleep(1)

def ReadTemp():
    global temp
    with lock:
        return temp




#7 3.3 gnd 
