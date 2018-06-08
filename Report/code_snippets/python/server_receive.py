def receive(self, connection_socket):
    while flag_keep_receiving:
        # Construct a new incoming stream 
        stream = connection_socket.recv(1).decode("utf-8")
        while not input_stream.endswith(ASCII.EOT):
            stream += connection_socket.recv(1)..decode("utf-8")
            
        # Retrieve a Message object from the stream
        message = Message.from_string(input_stream)
        
        if message:
            self.parse(connection_socket, message)