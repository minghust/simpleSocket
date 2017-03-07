'''
	 POWERD BY ZHANGMING 
	 ALL RIGHTS RESERVERD
'''
#ALL THE IMPORT
import socket
import sys


#ESTABLISH SOCKET OBJECT
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
#ESTABLISH FINISHED
host = socket.gethostname()
port = 9999

#BIND THE HOSTNAME AND PORT WITH A TURPLE
server.bind((host,port))

#THE LARGEEST NUMBER OF CLIENTS WHITCH COULD BE LISTENED
server.listen(5)

while True:
	#GET THE CLIENT'S ADDRESS
	client,adderss = server.accept()

	print('The adderss of client: %s' % str(adderss))

	while True:
		message = input('INPUT (q to quit) : ')
		if message == 'q':
			break
		'''
		IF NOT QUIT, SEND THE MESSAGE INPUTED TO CLIENT
		USE ENCODE TO CONVERT UNICODE(CHINESE CHARACTER)
		TO UTF-8
		'''
		client.send(message.encode('utf-8'))

	#CLOSE SERVER
	server.close()
	
	break



