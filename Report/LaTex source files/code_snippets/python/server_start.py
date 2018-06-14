def start(self):
    # Create a TCP/IP socket
    self._server_socket = 
        socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the port
    self._server_socket.bind((self._IP, self._PORT))

    # Start listening on the stream for incoming connections
    self.listen()