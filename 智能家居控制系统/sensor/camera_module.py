import cv2
import base64
from PIL import Image
from time import sleep

cap = cv2.VideoCapture(0)


def __init__():
	if not cap.isOpened():
		print("err open camera")
		exit()


def GetImage():
	#while True:
	ret,frame = cap.read()
	print('show frame')
	if not ret:
		print("err catch image")
		return None
	#cv2.imshow('frame',frame)
	frame = cv2.resize(frame,(320,240),interpolation=cv2.INTER_AREA)
	cv2.imwrite('capture.jpg',frame)
	
	
	
	#sleep(10)
	if ret:
		#print('ret')
		#encodeFrame = cv2.imencode('.jpg',frame)[1].tobytes()
		#print('encode')
		#image = base64.b64encode(encodeFrame).decode('utf-8')
		
		image_data = Image.open('capture.jpg')
		image_data.save('after.jpg',quality=80)
		with open('after.jpg','rb') as f:
			image_data = f.read()
		return image_data
	return None
	#sleep(1)
	#if cv2.waitKey(1) & 0xFF == ord('q'):
		#break
	
	
#cap.release()
#cv2.destoryAllWindows()

