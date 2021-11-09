
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main() {
	string first;

	cin >> first;

	fstream origin;	

	fstream stego;	

	//���ڵ�
	if (first == "e") {

		char message[4096];	//�޽���������

		getchar();	//���� �����

		cin.getline(message, 4096);	// message �Է� ����

		int size=0; //�Է¹��� message �� ũ�⸦ ǥ��

		for (int i = 0; i < 4096; i++) {//�Է¹��� message �� \0 �� ������ �������� ũ�� ���ϱ�

			if (message[i] == '\0') break;

			else size++;
		}

		origin.open("origin.bmp", ios::in | ios::binary);

		stego.open("stego.bmp", ios::out | ios::binary | ios::trunc);//trunc �� ����Ͽ� stego.bmp �ȿ�  �ִ� ���� ���� 

		char rw[4096];	//�а� ������ ��� ����

		while (1) {

			origin.read(rw, 1024);

			if (origin.eof()) {	//1024����Ʈ�� �д� ���� ������ ������ �Ǹ�

				origin.clear();	

				origin.seekg(0, ios::end);	//������ ������ �̵�

				stego.write(rw, origin.tellg() % 1024); // tellg�� ����ũ�� ���Ѵ��� 1024���� ���� ������ write

				break;	
			}

			stego.write(rw, 1024);	//1024����Ʈ�� ��� ���� ��� -> �״�� stego.bmp�� write
		}

		stego.write(message, size);	//stego.bmp�� �Է¹��� message write


		// ���� �ݱ�
		origin.close();

		stego.close();
	}

	//���ڵ�
	else if (first == "d") {	

		stego.open("stego.bmp", ios::in | ios::binary);
		
		stego.seekg(2, ios::beg);	//������ ������ġ���� ������ ����� ����Ű�� ������(02)���� �̵�
		
		int size;	
		
		stego.read((char*)&size, sizeof(int));	//bmp ������ ����

		stego.seekg(size, ios::beg);	//file_size�� ������ �̵� -> �� ���� ���� ���ڵ� �� ������ �޽����� ����
		
		char buffer;
		
		while (!stego.eof()) {	

			stego.read(&buffer,1);//1byte�� read

			if (!stego.eof()) cout << buffer; //message�� 1byte�� ���
		
		}
		
		stego.close();//���� �ݱ�
	}

	return 0;

}
