import socket
import struct
import threading

ServerSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

Ip = '192.168.236.53'
#Ip = '127.0.0.1'
Port = 4322

address = None

lock = threading.RLock()

def ClientProgram():
	global ServerSocket
	#ServerSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
	
	ServerAddress = (Ip,Port)
	
	ServerSocket.bind(ServerAddress)
		
	print('[debug] server init success')
	
	
	

def NetSend(val):
	global ServerSocket
	if address == None:
		print('[sendto] not have address')
		return
	with lock:
		print('[sendto] val is' ,val)
		chunk = 1024;
		offset = 0;
		#while offset < len(val):
		#	ServerSocket.sendto(val[offset:offset + chunk],address)
			#offset += chunk
			
		ServerSocket.sendto(val,address)
	
def NetRecv():
	global ServerSocket
	global address
	response = None
	#with lock:
	response,address1 = ServerSocket.recvfrom(1024)
	address = address1
	print('response' ,response.decode())
	
	return response.decode()



def main(args):
	ClientProgram()
	while True:
		resp = NetRecv()
		res = "0007abcd"
		
		print('res' ,res)
		NetSend(res)

	return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
