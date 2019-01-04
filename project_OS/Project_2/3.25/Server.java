import java.net.*;
import java.io.*;

public class Server{
	public static void main(String [] args){
		try{
			ServerSocket sock = new ServerSocket(6013);

			while(true){ /*listen for connection*/
				Socket client = sock.accept();

				InputStream in = client.getInputStream();
				BufferedReader bin = new BufferedReader(new InputStreamReader(in));
				/*create BufferReader to use i/o functions to read from client*/

				PrintWriter pout = new PrintWriter(client.getOutputStream(), true); 
				/*create PrintWriter to use i/o functions to write to client*/

					String input = bin.readLine();
					pout.println(input); /*send data back to client*/

				client.close(); /*close connection*/
			}
		}
		catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}