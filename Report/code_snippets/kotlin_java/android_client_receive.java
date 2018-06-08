private void receive() {
    // Build the incoming string-stream until EOT is found
    String input = String.valueOf( (char) this.in.read() );
    while (! input.endsWith(ASCII.EOT()))
        input += (char) this.in.read();
    
    // Build a Message object from such stream
    Message m = new Message( input );
    
    // Notify observers if the Message obtained is legit
    if (m.isLegit())
        notifyObservers(m);
}