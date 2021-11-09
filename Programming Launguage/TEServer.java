package easy;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class TEServer implements Runnable{
	static int cnt=0;
	static int person;
	static int time;
	static int mafia=0;
	static int mafia2=0;

	static int citizenum=0;
	static int mafianum=0;
	static int votenum=0;//투표한 사람의 숫자
	static int votetr=0;
	public static LinkedHashMap<String,String>people;//들어있는 사람
	public static LinkedHashMap<String,String>votepaper;//투표용지
	public static LinkedHashMap<String, Integer> votebox;//투표함


	private static Socket clientSocket;
	public TEServer(Socket clientSocket) {
		this.clientSocket = clientSocket;
	}
	
	static class  CountDownLatchService implements Runnable{
		
		private CountDownLatch latch;
		public CountDownLatchService(CountDownLatch latch) {
			this.latch = latch;
		}	
		@Override
		public void run() {
			latch.countDown();		
		}
	}
	String set(String name) {
		if(cnt==mafia||cnt==mafia2) {
			people.put(name, "mafia");
			mafianum++;
			cnt++;
			return "mafia";
			}
			else {
			
			people.put(name,"cizizen");
			citizenum++;
			cnt++;
			return "citizen";
			}
	}
	
	public static void main(String[] args) throws InterruptedException {
		System.out.println("마피아 게임 시작~\n 게임 시작 인원을 설정하시오:(최소인원 5명)");
		Scanner sc = new Scanner(System.in);
		person=sc.nextInt();
		System.out.println("투표 시간을 설정하시오(초)\n");
		Scanner sv = new Scanner(System.in);
		time = sv.nextInt();
		people = new LinkedHashMap<String, String>();
		votepaper = new LinkedHashMap<String,String>();
		votebox = new LinkedHashMap<String,Integer>();
		
		Random randomnum = new Random();
		 mafia=randomnum.nextInt(person/2+1);
		 mafia2=randomnum.nextInt(person+1);
		while(mafia==mafia2) {
			System.out.println("중복값 나옴");
			mafia2=randomnum.nextInt(person+1);

		}
		
		if(person<5) {
			System.out.println("참가하는 사람은 최소 5명 넘어야 합니다.");
			main(args);
				
		}
		else {
		ExecutorService eService = Executors.newFixedThreadPool(person);
		CountDownLatch latch = new CountDownLatch(person);				
		try(ServerSocket sSocket = new ServerSocket(10000)){
			
			while(true) {
				System.out.println("사람이 들어왔다 !");
				new Thread(new CountDownLatchService(latch)).start();
				clientSocket = sSocket.accept();
				TEServer tes = new TEServer(clientSocket);
				eService.submit(tes);
				}
		} catch (IOException e) {
			e.printStackTrace();		
		}
		latch.await();
		System.out.println("latch끝났다");
		eService.shutdown();//쓰레드 풀 shutdown
	}
	}

	@Override
	public void run() {		

		try(
				BufferedReader br = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
				PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
		){		
			
			String name;
			String inputLine;
			name=br.readLine();
			System.out.println(name+"님이 들어오셨습니다");
			out.println(set(name));
			out.println("메세지 입력");

			while((inputLine = br.readLine()) != null) {
				if(inputLine.equals("투표하세요")) {
					out.println("죽일사람 투표하세요");
					if(vote(name,br.readLine()).equals(name)) {
						votenum++;

						
						System.out.println(name+"님이 투표로 죽었습니다");
						if(people.get(name).toString().equalsIgnoreCase("mafia")) {
							mafianum--;
							System.out.println("투표종료!");
							System.out.println(name+"님은  마피아였습니다. 남은 시민은 의 수는"+citizenum+" 남은 마피아의 남은수는"+mafianum);
							if(mafianum==citizenum) {
								System.out.println("마피아 승리 !");
								System.exit(0);
							}
							if(mafianum==0) {
								System.out.println("시민 승리 !");
								System.exit(0);
							}
							if(votenum==person) {
							votebox.clear();
							people.remove(name);
							votenum=0;
							person--;
							}
						}
						else {
							citizenum--;
							System.out.println("투표종료!");
							System.out.println(name+"님은 투표로 죽었습니다.");
							System.out.println(name+"님은  시민이였습니다. 남은 시민은 의 수는"+citizenum+" 남은 마피아의 남은수는"+mafianum);
							if(mafianum==citizenum) {
								System.out.println("마피아 승리 !");
								System.exit(0);
							}
							if(mafianum==0) {
								System.out.println("시민 승리 !");
								System.exit(0);
							}
							if(votenum==person) {
							votebox.clear();
							people.remove(name);
							votenum=0;
							person--;

							}
						}
						out.println("quit");
					}
					
				
					else{
						
						
						votenum++;

						System.out.println(name+"는 살았습니다");
						if(votenum==person) {
						votebox.clear();
						people.remove(name);
						votenum=0;
						person--;

						}
						out.println("메세지 입력");
						
						continue;
					}
				
				}
				
				else if(inputLine.equalsIgnoreCase("quit")) {
					break;
				}
				else{
					
					System.out.println("[" +name+"] : " + inputLine);
					out.println("메세지 입력");

				
				}
			}
		}catch(IOException ex) {
			ex.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		
	}


	String vote(String name, String voted) throws InterruptedException {
		System.out.println(name+"님이"+voted+ "를 투표하셨습니다.");
		if(votebox.containsKey(voted)) {
			int i=votebox.get(voted).intValue();
			votebox.put(voted,i+1);
		}
		else {
		votebox.put(voted,1);
		}
		Thread.sleep(time*1000);
		return Collections.max(votebox.entrySet(), (entry1, entry2) -> entry1.getValue() - entry2.getValue()).getKey();
		
		
	}
}