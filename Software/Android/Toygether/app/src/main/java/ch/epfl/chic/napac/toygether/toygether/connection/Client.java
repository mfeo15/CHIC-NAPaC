package ch.epfl.chic.napac.toygether.toygether.connection;

import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Observable;
import java.util.Observer;

import ch.epfl.chic.napac.toygether.toygether.WaitingForToyActivity;

public class Client extends Observable implements Runnable {

    private static Client instance = null;

	private Socket socket;
	private int serverPort;
	private String ServerIP;

    private BufferedReader in;
    private PrintStream out;

    public static Client getInstance() {
        if (instance == null)
            instance = new Client();

        return instance;
    }

	public void setupParameters(String ServerIP, int serverPort) {
        this.ServerIP = ServerIP;
        this.serverPort = serverPort;
    }

    private void init() {
        try {
            socket = new Socket(ServerIP, serverPort);

            this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.out = new PrintStream(socket.getOutputStream());

            this.send( new Message("S001", "U123", "0001").toString() );

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {

        // Run the initial configuration with the previoslty provided parameters
        this.init();

        while (true)
            receive();
    }

    private void _send(String message) throws IOException {

        if (socket == null)
            return;

        out.print(message);
        out.flush();
    }

    public void send(final String message){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    _send(message);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private void receive() {

        try {
            // Read and build the incoming string stream until EOT is found
            String messageString = String.valueOf( (char) this.in.read() );
            while (! messageString.endsWith(ASCII.EOT())) {
                messageString += (char) this.in.read();
            }

            // Build a Message object from such stream
            Message m = new Message(  messageString );

            // If the Message obtained is legit (follow the protocol) then parse it
            if (m.isLegit()) {
                parse(m);
            }


        } catch (IOException e) {
            Log.d("Client", "ERROR !!!!");
            e.printStackTrace();
        }
    }

    private void parse(Message m) {
        //Log.d("Client", m.toString());

        notifyChangement(m);
    }





    public void notifyChangement(Object o) {

        setChanged();
        notifyObservers(o);
    }

    public void addNewObserver(Observer obs) {
        addObserver(obs);
    }

    public void deleteAnObserver(Observer obs) {
        deleteObserver(obs);
    }

    public void deleteAllObservers() {
        deleteObservers();
    }
}