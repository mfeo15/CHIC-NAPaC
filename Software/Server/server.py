import socket
import threading
import atexit
import sys, select
#from threading import Thread

#import _thread

#from connection import Connection

class Server(object):
	"""Class to model a TCP Server with multiple client capabilities.

	The object follows the Singleton pattern in order to have it instanced once and 
	avoiding overlapping. 


	Matteo Yann Feo @ EPFL, NAPaC team of CHIC 2017/2018
	25/02/2018
	"""

	__instance = None

	__MESSAGE_LENGTH = 20
	__MESSAGE_DELIMITER = ':'


	def __init__(self):
		"""Constructor method of the class. 

		New instance of the server socket on the provided __PORT. If the process completes
		without troubles a log is printed on the console with easy access for the IP address.
		If the operation fails (busy port), the error is logged as well.
		"""

		self._server_socket = None
		#self._IP = socket.gethostbyname(socket.gethostname())
		self._IP = "172.20.10.9"
		self._PORT = 6789
		self._connections = {}

		atexit.register(self.close)


	
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


	def receive(self, connection_socket):
		"""Method handling new message received from the client. """

		try:

			while True:
				message  = connection_socket.recv(self.__MESSAGE_LENGTH).decode("utf-8")
		
				if message:
					print()
					print("> Message received from {c}: \"{m}\"".format(c=connection_socket.getpeername()[0], m=message))

					if (message[self.__MESSAGE_LENGTH-1] == '$'):
						#connection_socket.sendall(message.encode("utf-8"))
						self.parse(connection_socket, message[:-1])

		except Exception as e:
			print()
			print("> Connection {c} has crashed unexpectedly and the socket has been closed".format(c=connection_socket.getpeername()[0]))
			connection_socket.close()


	def send(self, connection_socket, message):
		"""Method sending new message to a client. """
		threading.Thread( target=(lambda c, m : c.sendall(m.encode())), args=(connection_socket, message) ).start()


	def parse(self, connection_socket, message):

		receiver, sender, identifier, param  = message.split(self.__MESSAGE_DELIMITER)

		print("  RECEIVER: {t}".format(t=receiver))
		print("  SENDER: {t}".format(t=sender))
		print("  MSG_ID: {t}".format(t=identifier))
		print("  PARAM: {t}".format(t=param))
		print()

		if (receiver[0] == 'S'):
			 # Message for the server, do something !

			 if (identifier == "0001"):
			 	# Message for introduction, store the name of the connection
			 	self.register_connection(connection_socket, sender)

			 	print("> Connection {c} has been renamed to {a}".format(c=self._connections[sender].getpeername()[0], a=sender))

			 return

		if (receiver[0] == 'U' or receiver[0] == 'P'):
			# Message for a client (User or Peluche), forward it to the right destination
			self.send(self._connections[receiver], message)

			print("> Message has been forwarded to {}".format(self._connections[receiver].getpeername()[0]))
			return


	def register_connection(self, c, identifier):
		"""Method to add the new connection in the list with the other ones. """

		self._connections[identifier] = c


	def start(self):
		try:
			# Create a TCP/IP socket
			self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

			# Reuse the address of socket after closing for debugging
			self._server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

			# Bind the socket to the port
			self._server_socket.bind((self._IP, self._PORT))

			# Print out a log information
			print()
			print()
			print("NAPaC Server : ON")
			print("> Server Socket inizialiazed : {}".format(self._IP))

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
			print("  Now listening...")

			while True:

				# Wait for a connection
				connection_socket, client_address = self._server_socket.accept()

				print()
				print("> New Client IP Address : {}".format(client_address) )

				# Instance a new connection for the new client and save it
				threading.Thread(target=self.receive, args=[connection_socket]).start()

		except Exception as e:
			print("Error during listening")
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
