import socket

class Server(object):

 	__instance = None

 	__server_socket = None

 	__PORT = 6789

 	def __init__(self):

 		try:
 			# Create a TCP/IP socket
 			self.__server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

 			# Bind the socket to the port
 			server_address = ('localhost', self.__PORT)
 			self.__server_socket.bind(server_address)

 			# Print out a log information
 			print("")
 			print("")
 			print("NAPaC Server : ON")
 			print("[ SERVER ] Server Socket inizialiazed : {}".format(socket.gethostbyname(socket.gethostname()) ))

 		except:
 			print("Error during init")

 	@classmethod
 	def get_instance(cls):
 		if not cls.__instance:
 			cls.__instance = Server()

 		return cls.__instance

 	def start(self):

 		# Listen for incoming connections
 		self.__server_socket.listen(1)

 		while True:
 			try:
 				# Wait for a connection
 				connection, client_address = self.__server_socket.accept()

 				print()
 				print("[ SERVER ] New Client IP Address : {}".format(client_address) )

 			except:
 				print("Error during connection")

 			finally:
 				# Clean up the connection
 				connection.close()

 	def close(self):
 		pass


if __name__ == "__main__":
	print("Standalone execution")
	Server.get_instance().start()
