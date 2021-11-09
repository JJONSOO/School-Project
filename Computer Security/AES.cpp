#include<stdio.h>
//in : key 를 입력받아 저장 , out 최종 암호화 또는 복호화된 것 
unsigned char in[16], out[16], state[4][4];
// Round key
unsigned char RoundKey[240];
// Key
unsigned char Key[32];
#include <bitset>
#include<algorithm>
#include <iostream>
#include<string>
#include<fstream>
int total = 0;
using namespace std;
// Shift and XOR -> Computational Considerations Multiplication 구현 
int check(int a, int cnt) {
	for (int i = 0; i < cnt - 1; i++) {
		a = a << 1;
		if (a >= 256) {
			a = (a ^ 0x01E7)%256;

		}
	}
	return a;
}
int deg(int  bp) {
	for (int i = 31; i >= 0; i--) {
		if ((bp & (1 << i)) != 0) {
			return i;
		}
	}
	return 0;
}
// 곱셈에 대한 역원 구하기 
int findinv(int a, int b) {
	int u = a;
	int v = b;
	int g_1 = 1;
	int g_2 = 0;
	int h_1 = 0;
	int h_2 = 1;
	while (u != 0) {
		int j = deg(u) - deg(v);
		if (j < 0) {
			int temp = 0;
			temp = u;
			u = v;
			v = temp;
			temp = g_1;
			g_1 = g_2;
			g_2 = temp;
			temp = h_1;
			h_1 = h_2;
			h_2 = temp;
			j = -j;
		}
		u = u ^ (v << j);
		g_1 = g_1 ^ (g_2 << j);
		h_1 = h_1 ^ (h_2 << j);
	}
	return g_2;
}
//bitset 으로 1의 개수 0의 개수 정하여서 1 or 0 을 정한다. 그 후 cnt 를 통해 2의 배수 표현 -> 2진수 자릿수의 수 표현 
void boxmade(int ch, int start, int one, int zero, int cnt) {
	bitset<8>(mid) = bitset<8>(ch) & bitset<8>(start);
	for (int i = 0; i < 8; i++) {
		if (mid[i] == 1)one++;
		else zero++;
	}
	int x = (one % 2 ? 1 : 0);//one 이 홀수개라면 1 , 짝수개라면 0 
	if (zero)//zero 가 하나라도 있다면 
		x = x ^ 0;;//0 과 XOR
	total += x * pow(2, cnt);

}
unsigned int SubByte(int x) {
	//GF(2^8)에서 곱셈에 대한 역원 구하기
	int start = findinv(x, 0x01E7);//x^8+𝑥^7+𝑥^6+𝑥^5+𝑥^2+𝑥+1
	total = 0;
	boxmade(241, start, 1, 0, 0);//10001111
	boxmade(227, start, 1, 0, 1);//11000111
	boxmade(199, start, 0, 1, 2);//11100011
	boxmade(143, start, 0, 1, 3);//11110001
	boxmade(31, start, 0, 1, 4); //11111000
	boxmade(62, start, 1, 0, 5); //01111100
	boxmade(124, start, 1, 0, 6);//00111110
	boxmade(248, start, 0, 1, 7);//00011111


	return total;
}
unsigned int invSubByte(int x) {
	int start = x;
	total = 0;
	boxmade(164, start, 1, 0, 0);
	boxmade(73, start, 0, 1, 1);
	boxmade(146, start, 1, 0, 2);
	boxmade(37, start, 0, 1, 3);
	boxmade(74, start, 0, 1, 4);
	boxmade(148, start, 0, 1, 5);
	boxmade(41, start, 0, 1, 6);
	boxmade(82, start, 0, 1, 7);

	total = findinv(total, 0x01E7);
	return total;
}
unsigned char calc(unsigned char a, unsigned char b) {
	unsigned char p = 0, i = 0, x = 0;
	for (i = 0; i < 8; i++) {
		if (b & 1) {
			p ^= a;
		}
		x = a & 0x80;
		a <<= 1;
		if (x) a ^= 0x01E7; // 1 1110 0111	
		b >>= 1;
	}
	return (unsigned char)p;
}
unsigned char R[] = { 0x02, 0x00, 0x00, 0x00 };
//Round 별 상수 정하기
unsigned char *Rcon(unsigned char i) {

	if (i == 1) {
		R[0] = 0x01; // x^(1-1) = x^0 = 1
	}
	else if (i > 1) {
		R[0] = 0x02;
		i--;
		while (i > 1) {
			R[0] = calc(R[0], 0x02);
			i--;
		}
	}

	return R;
}
//S-box 연산 후 Round 상수와 XOR
void XOR(unsigned char a[], unsigned char b[], unsigned char d[]) {

	d[0] = a[0] ^ b[0];
	d[1] = a[1] ^ b[1];
	d[2] = a[2] ^ b[2];
	d[3] = a[3] ^ b[3];
}
void KeyExpansion()
{
	int i, j;
	unsigned char RoundkeyMade[4], k;
	//First Round key = Key
	for (i = 0; i<4; i++){
		RoundKey[i * 4] = Key[i * 4];
		RoundKey[i * 4 + 1] = Key[i * 4 + 1];
		RoundKey[i * 4 + 2] = Key[i * 4 + 2];
		RoundKey[i * 4 + 3] = Key[i * 4 + 3];
	}

	// word 단위로 Round Key 만든다.
	while (i < 92)
	{
		for (j = 0; j<4; j++)
		{
			RoundkeyMade[j] = RoundKey[(i - 1) * 4 + j];
		}
		if (i % 4 == 0){
			// 바이트마다 연산
			// 자리이동 후 , S-box연산을 한 후 마지막으로 Round 상수와 XOR연산한다.	
		
				k = RoundkeyMade[0];
				RoundkeyMade[0] = RoundkeyMade[1];
				RoundkeyMade[1] = RoundkeyMade[2];
				RoundkeyMade[2] = RoundkeyMade[3];
				RoundkeyMade[3] = k;
		//S-box연산을 한 후 마지막으로 Round 상수와 XOR연산한다.	 
				RoundkeyMade[0] = SubByte(RoundkeyMade[0]);
				RoundkeyMade[1] = SubByte(RoundkeyMade[1]);
				RoundkeyMade[2] = SubByte(RoundkeyMade[2]);
				RoundkeyMade[3] = SubByte(RoundkeyMade[3]);
			XOR(RoundkeyMade, Rcon(i / 4), RoundkeyMade);


		}
		 
		RoundKey[i * 4 + 0] = RoundKey[(i - 4) * 4 + 0] ^ RoundkeyMade[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - 4) * 4 + 1] ^ RoundkeyMade[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - 4) * 4 + 2] ^ RoundkeyMade[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - 4) * 4 + 3] ^ RoundkeyMade[3];
		i++;
	}
}
// State XOR RoundKey
void AddRoundKey(int round)
{
	printf("AR: ");
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{	
			state[j][i] ^= RoundKey[round * 16 + i * 4 + j];

		/*	printf("%2x ", state[j][i]);*/
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			printf(" %2x ", state[i][j]);
		}
	}
	printf("\n");
}
//BS
void SubBytes()
{
	int i, j;
	printf("BS: ");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			state[i][j] = SubByte(state[i][j]);
			
		}	
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			printf(" %2x ", state[i][j]);
		}
	}
	printf("\n");

}


void ShiftRows()
{
	unsigned char stateshift;
	//첫 번째 행 1 열을 왼쪽으로 회전
	stateshift = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = stateshift;
	//두 번째 행 2 열을 왼쪽으로 회전
	stateshift = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = stateshift;
	stateshift = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = stateshift;
	//세 번째 행 3 열을 왼쪽으로 회전
	stateshift = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = stateshift;
	printf("SR: ");

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			printf(" %2x ", state[i][j]);
		}
	}
	printf("\n");
}
//열 내에서 이동 

void MixColumns()	
{
	//Computational Considerations 에서 Addition 은 XOR , Multiplication 은 Shift and XOR 로 표현  
	for (int i = 0; i < 4; i++) {
		int first =  check(state[0][i], 2)							^(check(state[1][i], 2) ^ check(state[1][i], 1))  ^ check(state[2][i], 1)							^ check(state[3][i], 1);
		int second = check(state[0][i], 1)							^ check(state[1][i], 2)							  ^(check(state[2][i], 2) ^ check(state[2][i], 1))  ^ check(state[3][i], 1);
		int third =  check(state[0][i], 1)							^ check(state[1][i], 1)							  ^ check(state[2][i], 2)							^(check(state[3][i], 2) ^ check(state[3][i], 1));
		int fourth = (check(state[0][i], 2) ^ check(state[0][i], 1))^ check(state[1][i], 1)							  ^ check(state[2][i], 1)							^ check(state[3][i], 2);
		state[0][i] = first;
		state[1][i] = second;
		state[2][i] = third;
		state[3][i] = fourth;
	}

	printf("MC: ");
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			printf(" %2x ", state[i][j]);
		}
	}
	printf("\n");
}
void Cipher()
{
	int i, j, round = 0;
	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			state[j][i] = in[i * 4 + j];
	printf("Starting state: \n");
	AddRoundKey(0);

	for (round = 1; round<10; round++)
	{
		printf("%d - round: \n", round);
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}
	printf("10 - round: \n");

	//마지막 Round에선 MixColumns 하지 않는다.
	SubBytes();
	ShiftRows();
	AddRoundKey(10);
	// 암호화된 State -> out
	for (i = 0; i<4; i++)
		for (j = 0; j<4; j++)
			out[i * 4 + j] = state[j][i];
	printf("Encryption finish !! \n\n\n");
}
void InvShiftRows()
{
	unsigned char InvShiftmade;

	//첫 번째 행을 오른쪽으로 1 열 회전
	InvShiftmade = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = InvShiftmade;

	//두 번째 행을 오른쪽으로 2열 회전
	InvShiftmade = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = InvShiftmade;

	InvShiftmade = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = InvShiftmade;

	//세 번째 행을 오른쪽으로 3 열 회전
	InvShiftmade = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = InvShiftmade;
}
void InvMixColumns()
{
	
	for (int i = 0; i < 4; i++) {
		int first =	 (check(state[0][i], 2) ^ check(state[0][i], 3)  ^ check(state[0][i], 4)) ^ (check(state[1][i], 1) ^ check(state[1][i], 2)  ^ check(state[1][i], 4)) ^ (check(state[2][i], 1) ^ check(state[2][i], 3) ^ check(state[2][i], 4))	 ^ (check(state[3][i], 1) ^ check(state[3][i], 4));
		int second = (check(state[0][i], 1) ^ check(state[0][i], 4))						  ^ (check(state[1][i], 2) ^ check(state[1][i], 3)  ^ check(state[1][i], 4)) ^ (check(state[2][i], 1) ^ check(state[2][i], 2) ^ check(state[2][i], 4))   ^ (check(state[3][i], 1) ^ check(state[3][i], 3) ^ check(state[3][i], 4));
		int third =  (check(state[0][i], 1) ^ check(state[0][i], 3)  ^ check(state[0][i], 4)) ^ (check(state[1][i], 1) ^ check(state[1][i], 4)) 					     ^ (check(state[2][i], 2) ^ check(state[2][i], 3) ^ check(state[2][i], 4))   ^ (check(state[3][i], 1) ^ check(state[3][i], 2) ^ check(state[3][i], 4));
		int fourth = (check(state[0][i], 1) ^ check(state[0][i], 2)  ^ check(state[0][i], 4)) ^ (check(state[1][i], 1) ^ check(state[1][i], 3)  ^ check(state[1][i], 4)) ^ (check(state[2][i], 1) ^ check(state[2][i], 4))                           ^ (check(state[3][i], 2) ^ check(state[3][i], 3) ^ check(state[3][i], 4));
		state[0][i] = first;
		state[1][i] = second;
		state[2][i] = third;
		state[3][i] = fourth;

	}
	printf("MC: ");
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			printf(" %2x ", state[i][j]);
		}
	}
	printf("\n");
}

void InvSubBytes()
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			state[i][j] = invSubByte(state[i][j]);
		}
	}
}

void decryption() {
	int i, j, round = 0;

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			state[j][i] = in[i * 4 + j];
		}
	}
	printf("Starting state: \n");
	AddRoundKey(10);

	
	for (round = 9; round>0; round--)
	{
		printf("%d - round: \n", round);
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}

	
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			out[i * 4 + j] = state[j][i];
		}
	}
	printf("Decryption finish !! \n\n\n");


}
int main()
{	

	string first;

	cin >> first;
	//Encryption
	if (first == "e") {
		//Read key.bin
		ifstream keyFile("key.bin", ios::binary);
		if (!keyFile.is_open()) {
			cout << "key.bin is not open" << endl;
			return -1;
		}
		//Read plainFile
		ifstream plainFile("plain.bin", ios::binary);		

		while (plainFile.read((char*)in, 16)) {
			//Input Key
			keyFile.read((char*)Key, 16);
			KeyExpansion();
			Cipher();
			ofstream cipherFile("cipher.bin", ios::binary | ios::app);
			cipherFile << state[0][0] << state[1][0] << state[2][0] << state[3][0]
				<< state[0][1] << state[1][1] << state[2][1] << state[3][1]
				<< state[0][2] << state[1][2] << state[2][2] << state[3][2]
				<< state[0][3] << state[1][3] << state[2][3] << state[3][3];
		}
	}
	//Decryption
	else if (first == "d") {
		ifstream keyFile("key.bin", ios::binary);
		keyFile.read((char*)Key, 16);

		ifstream cipherFile("cipher.bin", ios::binary);
		if (!cipherFile.is_open()) {
			cout << "cipher.bin is not open" << endl;
			return -1;
		}

		while (cipherFile.read((char*)in, 16)) {
			keyFile.read((char*)Key, 16);
			KeyExpansion();
			decryption();

			ofstream plainFile2("plain2.bin", ios::binary | ios::app);
			plainFile2 << state[0][0] << state[1][0] << state[2][0] << state[3][0]
				<< state[0][1] << state[1][1] << state[2][1] << state[3][1]
				<< state[0][2] << state[1][2] << state[2][2] << state[3][2]
				<< state[0][3] << state[1][3] << state[2][3] << state[3][3];

		}
	}
}
