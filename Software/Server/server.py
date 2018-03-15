import socket
from threading import Thread

from connection import Connection

class Server(object):
	"""Class to model a TCP Server with multiple client capabilities.

	The object follows the Singleton pattern in order to have it instanced once and 
	avoiding overlapping. 


	Matteo Yann Feo @ EPFL, NAPaC team of CHIC 2017/2018
	25/02/2018
	"""

	__instance = None


	def __init__(self):
		"""Constructor method of the class. 

		New instance of the server socket on the provided __PORT. If the process completes
		without troubles a log is printed on the console with easy access for the IP address.
		If the operation fails (busy port), the error is logged as well.
		"""

		self._server_socket = None
		self._IP = socket.gethostbyname(socket.gethostname())
		self._PORT = 6789
		self._connections = {}

	
	@classmethod
	def get_instance(cls):
		"""Implementation of the Singleton design patter for the Class object. 

		Returns:
			the existing instance of the object or a new one if it is invoked for
			the very first time in the execution.
		"""

		if not cls.__instance:
			cls.__instance = Server()

			return cls.__instance


	def _register_connection(self, c):
		"""Method to add the new connection in the list with the other ones. """

		self._connections.append(c)


	def start(self):
		try:
			# Create a TCP/IP socket
			self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

			# Bind the socket to the port
			self._server_socket.bind((self._IP, self._PORT))

			# Print out a log information
			print("")
			print("")
			print("NAPaC Server : ON")
			print("[ SERVER ] Server Socket inizialiazed : {}".format(self._IP))

			self.listen()

		except Exception as e:
			print("Error during init")
			print(e)


	def listen(self):
		"""Method to activate the instanced and setup Server in the constructor.

		A new connection is instanced for each new client reaching the server. Those are
		registered in a list for easy retrieval in the future.
		Whenever a connection fails, it is closed to prevent malffunctions.
		"""

		# Listen for incoming connections
		self._server_socket.listen(5)

		try:
			print("[ SERVER ] Now listening")

			while True:

				# Wait for a connection
				connection_socket, client_address = self._server_socket.accept()

				print()
				print("[ SERVER ] New Client IP Address : {}".format(client_address) )

				# Instance a new connection for the new client and save it
				connection = Connection(connection_socket)
				connection.start()

		except Exception as e: 
			print("Error during connection")
			print(e)

		finally:
			# Clean up the connection and close the Server
			self.close()
			connection_socket.close()


	def close(self):
		"""Method close and clean-up the Server object when not needed anymore """

		self._server_socket.close()


if __name__ == "__main__":
	print("Standalone execution")
	Server.get_instance().start()
