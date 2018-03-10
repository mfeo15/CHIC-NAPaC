
from server import Server

def main():
	"""Main method that takes care of setting up and running the Server object. """

	print("Running server environment...")

	# Server starting
	Server.get_instance()
	Server.get_instance().start()


if __name__ == "__main__":
	main()