import socket
import sys

import ASCII

serverIP = '127.0.0.1'
serverPORT = 6789

class Client(object):

	__client_socket = None

	__instance = None

	def __init__(self):
		# Create a TCP/IP socket
		self.__client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		# Connect the socket to the port where the server is listening
		server_address = (serverIP, serverPORT)
		self.__client_socket.connect(server_address)

	@classmethod
	def get_instance(cls):
 		if not cls.__instance:
 			cls.__instance = Client()

 		return cls.__instance

	def send(self, message):
 		self.__client_socket.sendall(message.encode())
 		print("[ CLIENT ] Message sent : {}".format(message))

	def receive(self):
 		while True:

 			message = self.__client_socket.recv(1).decode("utf-8")
 			while not message.endswith(ASCII.EOT):
					message += self.__client_socket.recv(1).decode("utf-8")

 			if message:
 				print()
 				print("> Message received: \"{m}\"".format(m=message))

 				Client.get_instance().send("{stx}0000{rs}U123{rs}P314{rs}2002{eot}".format(stx=ASCII.STX, rs=ASCII.RS, eot=ASCII.EOT))


if __name__ == "__main__":
	print("Standalone execution")
	
	if (len(sys.argv) > 1):
		serverIP = sys.argv[1]
		if (len(sys.argv) == 3):
			serverPORT = int(sys.argv[2])

	Client.get_instance()

	# Introduzione
	Client.get_instance().send("{stx}0000{rs}S001{rs}P314{rs}0001{eot}".format(stx=ASCII.STX, rs=ASCII.RS, eot=ASCII.EOT))

	# Message to forward and fail
	#Client.get_instance().send("{stx}0000{rs}U999{rs}P314{rs}9999{eot}".format(stx=ASCII.STX, rs=ASCII.RS, eot=ASCII.EOT))

	# Test message of color function
	Client.get_instance().receive()