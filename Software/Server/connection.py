from threading import Thread

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
			print("[ SERVER ] Message received from {c}: {m}".format(c=self._get_address(), m=message))


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



