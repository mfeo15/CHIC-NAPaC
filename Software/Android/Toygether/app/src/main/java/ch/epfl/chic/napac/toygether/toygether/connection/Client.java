package ch.epfl.chic.napac.toygether.toygether.connection;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.TimeUnit;

public class Client implements Runnable {

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

	public void setupParamters(String ServerIP, int serverPort) {
        this.ServerIP = ServerIP;
        this.serverPort = serverPort;
    }

    @Override
    public void run() {

        try {
            TimeUnit.SECONDS.sleep(5);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        try {
            socket = new Socket(ServerIP, serverPort);

            this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            this.out = new PrintStream(socket.getOutputStream());

            //Send introduction of the new client to the server
            //this.asyncSend("S001:U123:0001:0000$");

        } catch (UnknownHostException e1) {
            e1.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void send(String message) throws IOException {

        if (socket == null)
            return;

        out.print(message);
        out.flush();
    }

    public void asyncSend(final String message){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    send(message);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}