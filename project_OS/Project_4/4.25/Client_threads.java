import java.net.*;
import java.io.*;

public class Client_threads{
	public static void main(String [] args){
		try{
			Socket sock = new Socket("127.0.0.1", 6013); 
			/*Connect to server socket, (Server is listening on port 6013)*/

			PrintWriter send = new PrintWriter(sock.getOutputStream(), true);
			for(int i = 0; i < args.length; i++){
				send.println(args[i]); /*Take in argument from command line*/
			}
			//send.println("hello there");

			InputStream in = sock.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(in));

			System.out.println("ECHO: ");

			String line; 
			while((line = bin.readLine()) != null){
				System.out.println(line);
		    }

			sock.close(); /*close connection*/
		}
		catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}