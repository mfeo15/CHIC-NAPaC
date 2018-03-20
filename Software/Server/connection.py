from threading import Thread

import server

class Connection(Thread):
	"""Class implemented to handle and manage a single connection to the Server.

	This class is instanced whenever a new Client connect to the server, enabling 
	it to schedule a threading for each new client. This allow multi-client support
	in the system.

	Attributes:
		socket (Socket) : connection socket between this client and the server


	Matteo Yann Feo @ EPFL, NAPaC team of CHIC 2017/2018
	10/03/2018
	"""

	__MESSAGE_LENGTH = 20
	__MESSAGE_DELIMITER = ':'

	def __init__(self, socket):
		"""Constructor method of the class.

		Args:
			socket (Socket): connection socket between this client and the server.
		"""

		Thread.__init__(self)

		self._socket = socket
		self._active = True 


	def _receive(self):
		"""Method handling new message received from the client. """

		message  = self._socket.recv(self.__MESSAGE_LENGTH).decode("utf-8")
		
		if message:
			print()
			print("> Message received from {c}: \"{m}\"".format(c=self._get_address(), m=message))

			self.parse(message)


	def _get_address(self):
		"""Method extracting the connected client IP address.

		Returns:
			the connected client IP address.

		"""

		return self._socket.getsockname()[0]

	def _is_active(self):
		"""TODO. """

		return self._active


	def run(self):
		"""TODO. """

		while (self._is_active()):
			self._receive()


	def parse(self, message):

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
			 	server.Server.get_instance().register_connection(self, sender)

			 	print("> Connection name has been set to {}".format(Server.get_instance()._connections[sender]))

			 return

		if (receiver[0] == 'U' or receiver[0] == 'P'):
			# Message for a client (User or Peluche), forward it to the right destination

			print("> Message has been forwarded to {}".format(receiver))
			return

		if (identifier == "0001"):
			server.Server.get_instance().register_connection(self, sender)
			return

		if (identifier == "0002"):

			return


