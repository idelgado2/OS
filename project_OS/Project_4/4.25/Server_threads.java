import java.net.*;
import java.io.*;

class message implements Runnable{
	private ServerSocket sock;

	public message(ServerSocket sock){
		this.sock = sock;
	}

	public void run(){
		try{
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
				catch(IOException ioe){
					System.err.println(ioe);
				}
	}
}

public class Server_threads{
	public static void main(String [] args){
		try{
			ServerSocket sock = new ServerSocket(6013);

			while(true){ /*listen for connection*/
				Thread thrd = new Thread(new message(sock));
				thrd.start();
				try{
					thrd.join();
				} catch (InterruptedException ie){}
			}
		}
		catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}