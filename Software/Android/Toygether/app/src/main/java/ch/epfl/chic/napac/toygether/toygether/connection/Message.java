package ch.epfl.chic.napac.toygether.toygether.connection;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by mfeo15 on 25.04.18.
 */

public class Message {

    private Boolean legit = false;
    private String destination;
    private String source;
    private String messageID;
    private String[] parameters = new String[0];

    public Message(String destination, String source, String messageID) {

        this.destination = destination;
        this.source = source;
        this.messageID = messageID;
        this.legit = true;
    }

    public Message(String destination, String source, String messageID, String[] parameters ) {

        this(destination, source, messageID);

        this.parameters = parameters;
    }

    public Message(String m) {

        if (m == null)
            return;

        if (!(m.startsWith(ASCII.STX()) && m.endsWith(ASCII.EOT())))
            return;

        String[] records = m.substring(1, m.length() - 1).split(ASCII.RS());

        if (records.length == 4) {
            this.destination = records[1];
            this.source = records[2];
            this.messageID = records[3];
            this.legit = true;
            return;
        }

        if (records.length == 5) {
            this.destination = records[1];
            this.source = records[2];
            this.messageID = records[3];
            this.legit = true;

            String[] parameters = records[4].split(ASCII.US());
            this.parameters = Arrays.copyOfRange(parameters, 1, parameters.length);
            return;
        }
    }

    public Boolean isLegit() {
        return this.legit;
    }

    public String toString() {

        String main = ASCII.RS() + this.destination + ASCII.RS() + this.source + ASCII.RS() + this.messageID;

        if (this.parameters.length > 0) {
            main += ASCII.RS() + String.valueOf(this.parameters.length);

            for (String p : this.parameters)
                main += ASCII.US() + p;

        }

        return ( ASCII.STX() + String.format("%04d", 2+4+main.length()) + main + ASCII.EOT() );
    }

    public String toBytes() {

        String messageString = this.toString();

        String output = "";
        for (int i = 0; i < messageString.length(); i++){
            char c = messageString.charAt(i);
            output += String.format("%02d", (int) c) + " ";
        }

        return output;
    }
}