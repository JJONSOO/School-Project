
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main() {
	string first;

	cin >> first;

	fstream origin;	

	fstream stego;	

	//인코딩
	if (first == "e") {

		char message[4096];	//메시지데이터

		getchar();	//버퍼 비워줌

		cin.getline(message, 4096);	// message 입력 받음

		int size=0; //입력받은 message 의 크기를 표현

		for (int i = 0; i < 4096; i++) {//입력받은 message 중 \0 이 나오기 전까지의 크기 구하기

			if (message[i] == '\0') break;

			else size++;
		}

		origin.open("origin.bmp", ios::in | ios::binary);

		stego.open("stego.bmp", ios::out | ios::binary | ios::trunc);//trunc 를 사용하여 stego.bmp 안에  있던 내용 삭제 

		char rw[4096];	//읽고 쓸것을 담는 버퍼

		while (1) {

			origin.read(rw, 1024);

			if (origin.eof()) {	//1024바이트를 읽는 도중 파일이 끝나게 되면

				origin.clear();	

				origin.seekg(0, ios::end);	//파일의 끝으로 이동

				stego.write(rw, origin.tellg() % 1024); // tellg로 파일크기 구한다음 1024으로 나눈 나머지 write

				break;	
			}

			stego.write(rw, 1024);	//1024바이트를 모두 읽은 경우 -> 그대로 stego.bmp에 write
		}

		stego.write(message, size);	//stego.bmp에 입력받은 message write


		// 파일 닫기
		origin.close();

		stego.close();
	}

	//디코딩
	else if (first == "d") {	

		stego.open("stego.bmp", ios::in | ios::binary);
		
		stego.seekg(2, ios::beg);	//파일의 시작위치에서 파일의 사이즈를 가리키는 오프셋(02)으로 이동
		
		int size;	
		
		stego.read((char*)&size, sizeof(int));	//bmp 사이즈 설정

		stego.seekg(size, ios::beg);	//file_size로 오프셋 이동 -> 이 이후 부터 인코딩 때 삽입한 메시지가 있음
		
		char buffer;
		
		while (!stego.eof()) {	

			stego.read(&buffer,1);//1byte씩 read

			if (!stego.eof()) cout << buffer; //message를 1byte씩 출력
		
		}
		
		stego.close();//파일 닫기
	}

	return 0;

}
