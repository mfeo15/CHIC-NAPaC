package ch.epfl.chic.napac.toygether.toygether.connection;

/**
 * Created by mfeo15 on 25.04.18.
 */

public final class ASCII {

    public static final char STX    = (char) 2;
    public static final char EOT    = (char) 4;
    public static final char RS     = (char) 30;
    public static final char US     = (char) 31;

    public static String STX() {
        return String.valueOf(STX);
    }

    public static String EOT() {
        return String.valueOf(EOT);
    }

    public static String RS() {
        return String.valueOf(RS);
    }

    public static String US() {
        return String.valueOf(US);
    }
}