def listen(self):
    # Listen for incoming connections
    self._server_socket.listen(5)
    
    while flag_keep_listening:
        # Wait for a connection
        client_socket = self._server_socket.accept()
        
        # Instance a thread for the new client and run it
        threading.Thread(target=self.receive, 
                         args=[client_socket]).start()