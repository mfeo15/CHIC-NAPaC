private void init() {
    // Bind the socket to the port
    socket = new Socket(ServerIP, serverPort);

    // Initialize the input and output streams
    this.in = new BufferedReader(
        new InputStreamReader( socket.getInputStream() )
        );
    this.out = new PrintStream( socket.getOutputStream() );
}
