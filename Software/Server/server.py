import socket
import threading
import atexit
import sys, select

import ASCII
import database_manager as db
from message import Message

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
		#self._IP = "172.20.10.9"
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

				# Construct a new incoming message by reading a Byte-at-a-time until EOT
				input_stream = connection_socket.recv(1).decode("utf-8")
				while not input_stream.endswith(ASCII.EOT):
					input_stream += connection_socket.recv(1).decode("utf-8")
			
				message = Message.from_string(input_stream)

				if message:
					print()
					print("> Message received from {c}: \"{m}\" ".format(c=connection_socket.getpeername()[0], m=message.to_string(delimiter=" ") ))
					print("  DEST: {t}".format(t=message.destination))
					print("  SOURCE: {t}".format(t=message.source))
					print("  MSG_ID: {t}".format(t=message.msg_id))
					print("  PARAM: {t}".format(t=message.parameters))
					print()

					self.parse(connection_socket, message)

		except Exception as e:
			print()
			print("> A connection has crashed unexpectedly and the socket has been closed")
			print(e)
			connection_socket.close()


	def send(self, connection_socket, message):
		"""Method sending new message to a client. """
		threading.Thread( target=(lambda c, m : c.sendall(m.encode())), args=(connection_socket, message) ).start()


	def parse(self, connection_socket, message):

		if (message.destination[0] == 'S'):
			 # Message for the server, do something !

			 if (message.msg_id == "0001"):
			 	# Message for introduction, store the name of the connection
			 	self.register_connection(connection_socket, message.source)

			 	print("> Connection {c} has been renamed to {a}".format(c=self._connections[message.source].getpeername()[0], a=message.source))
			 	return

			 if (message.msg_id == "0002"):
			 	# Message for closing the connection
			 	self.unregister_connection(message.source)

			 	print("> Client {c}connection has been closed and un-registered from the server {a}".format(c=message.source))
			 	return

		if (message.destination[0] == 'U' or message.destination[0] == 'P'):

			if not db.ToyParentAssociationExist(message.destination, message.source):
				# The two clients are not associated together and the forward is not authorized
				# Prepare a new message of error
				self.send(self._connections[message.source], Message(message.source, "S001", "0004", ["0001"]).to_string())

				print("> Permissione denied: message could not be forwarded because {d} and {s} are not associated".format(s=message.source, d=message.destination))
				return

			# Message for a client (User or Plush Toy), forward it to the right destination
			self.send(self._connections[message.destination], message.to_string())

			print("> Message has been forwarded to {}".format(self._connections[message.destination].getpeername()[0]))
			return


	def register_connection(self, c, identifier):
		"""Method to add the new connection in the list with the other ones. """

		self._connections[identifier] = c

	def unregister_connection(self, identifier):
		c = self._connections[identifier]
		del self._connections[identifier]

		c.close()



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