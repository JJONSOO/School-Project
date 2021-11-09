//#include <iostream>
//using namespace std;
//struct StudentInfo {
//	int id;
//	float grade;
//	char bloodType;
//}s3 = { 20201236, 4.4f, 'O' }, s4;
//
//int main()
//{
//	int a = 10;
//	int b = 0xA;
//	int c = 012;
//	int d = 0b1010; // c++ 14, binary literals
//
//	cout << a << endl;
//	cout << b << endl;
//	cout << c << endl;
//	cout << d << endl;
//
//	//StudentInfo s1 = { 20201234, 3.5f, 'O' };
//	//StudentInfo s2 = { 20201235, 3.7f, 'A' };
//
//	//cout << s2.grade << endl;
//	//cout << s1.id << endl;
//	//cout << s3.bloodType << endl;
//
//	//s4 = s2;
//	//cout << s4.bloodType << endl;
//
//	//s4.bloodType = 'B';
//	//cout << s4.bloodType << endl;
//	//cout << s2.bloodType << endl;
//	////s4.id = 20201237;
//	////s4.grade = 2.9f;
//
//
//	// Range based for loop
//	//for (int i : {1, 3, 5, 7, -9})
//	//	cout << i;
//
//	// Modern code
//	//char letters[] = "Hell";
//	//void* ps;
//	//ps = letters;
//
//	//for (auto letter : letters)
//	//	cout << letter;
//	
//	// Old school code
//	//char s[] = { 'H','e','l','l',0 };
//	//void* ps;
//	//ps = &s[0];
//
//	//for (int i = 0; i < sizeof(s); i++)
//	//	cout << *((char*)ps + i);
//
//	return 0;
//}
//
//// 002
////#include <iostream>
////using namespace std;
////int main()
////{
////	//char s[] = "Hell";
////	char s[] = {'H','e','l','l',0};
////	void* ps;
////	//ps = &s[0];
////	ps = s;
////
////	for(auto i=0; i<sizeof(s);i++)
////		cout << *((char*)ps+i);
////	//cout << (char*)ps << endl;
////	//cout << s << endl;
////
////	//short a = 2;
////	//double b = 3.14;
////	////int* ps;
////	//void* pv;
////	////ps = &a;
////	//pv = &a;
////	////cout << *ps << endl;
////	//cout << *(short*)pv << endl;
////	//pv = &b;
////	//cout << *(double*)pv << endl;
////
////
////	//const auto f = 3.1;
////	//auto s = "test12345";
////
////	////f = 3.14f;
////	//cout << sizeof(f) << "\t" << typeid(f).name() << endl;
////	//cout << sizeof(s) << "\t" << typeid(s).name() << endl;
////
////	//cout << f << endl;
////	//cout << s << endl;
////	return 0;
////}
//
//// 001
////#include <iostream>
////using namespace std;
////int main()
////{
////	// 자료형/음수표현방식(2의 보수법)/자료형SIZE
////	const int i = 5; // 32bit
////	// i = 7;
////	cout << i << endl;
////	unsigned short s = 65536; // 16bit 
////	// signed (-2의15승 ~ +2의15승-1)
////	// unsigned (0 ~ 2의16승-1)
////	//  1111 1111 1111 1111
////	// +                  1
////	// 10000 0000 0000 0000
////	cout << s << endl;
////
////	// 배열
////	//int arr[4];
////	//arr[0] = -9;
////	//arr[3] = 30000;
////
////	//int arr[4] = { 0 };
////	//arr[0] = -9;
////	//arr[3] = 30000;
////
////	//for (int i = 0; i < 4; i++)
////	//	cout << arr[i] << endl;
////	
////	// 배열명은 포인터 상수다
////	double arr[4] = { -9, 0, 0, 30000 }; 
////	auto* parr = &arr[0];
////
////	for(auto i=0; i<4; i++)
////		//cout << *(parr+i) << endl;
////		//cout << parr[i] << endl;
////		//cout << arr[i] << endl;
////		cout << *(arr+i) << endl;
////
////	return 0;
////}