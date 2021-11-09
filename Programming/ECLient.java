package easy;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class EClient {
	public static void main(String[] args) {
		try {
			InetAddress localAddress = InetAddress.getLocalHost();

			try (Socket cSocket = new Socket(localAddress, 10000);
					BufferedReader br = new BufferedReader(new InputStreamReader(cSocket.getInputStream()));
					PrintWriter out = new PrintWriter(cSocket.getOutputStream(), true);
							) {
				System.out.println("이름을 입력하세요:");
				Scanner scv = new Scanner(System.in);
				String name = scv.nextLine();
				out.println(name);
				System.out.println("당신의 직업은 "+br.readLine());
				while (true) {
					String get = br.readLine();
					if("quit".equalsIgnoreCase(get)) {
						out.println("quit");
						
					
						
						break;
					}
					else {
						System.out.println(get);
					}
					String elem =  scv.nextLine();
				if ("투표".equalsIgnoreCase(elem)) {
					out.println("투표하세요");
					System.out.println(br.readLine());
					out.println(scv.nextLine());
				}

				else {
					
					out.println(elem); 
				}
				}
			}
		} catch (IOException ex) {

		}
	}
}