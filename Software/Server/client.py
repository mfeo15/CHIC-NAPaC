import socket

class Client(object):

	__client_socket = None

	__instance = None

	def __init__(self):
		# Create a TCP/IP socket
		self.__client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		# Connect the socket to the port where the server is listening
		server_address = ('localhost', 6789)
		self.__client_socket.connect(server_address)

	@classmethod
	def get_instance(cls):
 		if not cls.__instance:
 			cls.__instance = Client()

 		return cls.__instance

	def send(self, message):
 		self.__client_socket.sendall(message.encode())
 		print("[ CLIENT ] Message sent : {}".format(message))

if __name__ == "__main__":
	print("Standalone execution")
	Client.get_instance()

	Client.get_instance().send('ABCD:123456789:XYZ:$')
	Client.get_instance().send('EFGH:987654321:ZYX:$')
	Client.get_instance().send('DEFG:987123465:JKW:$')