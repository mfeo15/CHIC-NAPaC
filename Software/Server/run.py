
from server import Server

def main():
	print("Running server environment...")

	Server.get_instance()

	Server.get_instance().start()


if __name__ == "__main__":
	main()