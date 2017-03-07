'''
	 POWERD BY ZHANGMING 
	 ALL RIGHTS RESERVERD
'''
#ALL THE IMPORT 
import socket
import sys

#ESTABLISH SOCKET OBJECT
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#ESTABLISH FINISHED
host = socket.gethostname()
port = 9999

#THE MOST LARGE NUMBER OF CLIENTS WHITCH COULD BE LISTENED
client.connect((host,port))

while True:
	#RECEIVE THE MESSAGE
	message = client.recv(1024)
	'''
	OUTPUT THE MESSAGE FROM SERVER TO SCREEN
	DECODE UTF-8 FROM THE SERVER TO UNICODE AS OUTPUT
	'''
	print(message.decode('utf-8'))
	if message == 'q':
		#CLOSE THE CLIENT
		client.close()
		break
