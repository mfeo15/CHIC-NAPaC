
from server import Server

def main():
	"""Main method that takes care of setting up and running the Server object. """
	print()
	print()
	print("  _   _    _    ____        ____   _____ ____ ____    ____                           ")
	print(" | \ | |  / \  |  _ \ __ _ / ___| |_   _/ ___|  _ \  / ___|  ___ _ ____   _____ _ __ ")
	print(" |  \| | / _ \ | |_) / _` | |       | || |   | |_) | \___ \ / _ \ '__\ \ / / _ \ '__|")
	print(" | |\  |/ ___ \|  __/ (_| | |___    | || |___|  __/   ___) |  __/ |   \ V /  __/ |   ")
	print(" |_| \_/_/   \_\_|   \__,_|\____|   |_| \____|_|     |____/ \___|_|    \_/ \___|_|   ")
	print("                                                                                     ")
	print()

	# Server starting
	#Server.get_instance()
	Server.get_instance().start()


if __name__ == "__main__":
	main()