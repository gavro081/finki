package tcp;

import java.io.*;
import java.net.Socket;


public class Worker extends Thread {
    private Socket socket;
    public Worker(Socket socket) {
        this.socket = socket; //go prezema socketot
    }

    @Override
    public void run() {
        BufferedReader reader = null;
        BufferedWriter writer = null;

        try {
            //otvora input i output stream kon tcp konekcijata
            reader = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
            writer = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));


            while(true) {

                //cita poraka od socketot
                String message=reader.readLine();

                //zatvara konekcija ako klientot go inicira toa
                if(message.equals("Closing connection")){
                    System.out.println("Client asked to close connection");
                    System.out.println("Worker deactivated");
                    break;
                }

                System.out.println(message+ socket.getInetAddress().getHostAddress()+ " "+socket.getPort());


                // praka povratna poraka kon klientot
                writer.write("Hello back from server");
                writer.newLine();
                writer.flush();

            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}