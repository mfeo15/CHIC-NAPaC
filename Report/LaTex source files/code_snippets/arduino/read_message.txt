String read_message() 
{
    c = client.read();
    if (c == char(2)){          //STX[0] = char(2);
        do{
            stringa += c;
            c = client.read();  // reads on byte 
        }while(c != char(4));   //EOT[0] = char(4);
    }
    return stringa;
}