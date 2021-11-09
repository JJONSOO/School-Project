//#include <iostream>
//using namespace std;
//
//void Hello(int); // 인사
//int Factorial(int); // 팩토리얼 함수, 반복문 이용
//int FactorialRecursion(int); // 팩토리얼 함수, 재귀함수 이용
//int main() {
//	int(*pFact)(int); // 함수포인터
//	void(*pHi)(int);
//
//	pFact = &Factorial;
//	pHi = &Hello;
//
//	int in;
//	cin >> in;
//
//	cout << (*pFact)(in) << endl;
//	(*pHi)(in);
//
//
//	//cout << FactorialRecursion(in) << endl;
//	//cout << Factorial(in) << endl; 
//	//Hello(in); // 함수 호출
//	return 0;
//}
//int FactorialRecursion(int f) {
//	// f = 4
//	// f = 3
//	// f = 2
//	if (f <= 1)
//		return 1;
//	else
//		return f * FactorialRecursion(f - 1);
//		// 4 * FactorialRecursion(3)
//		// 3 * FactorialRecursion(2)
//		// 2 * FactorialRecursion(1)
//}
//int Factorial(int f) {
//	int result = 1;
//
//	for (int i = 1; i <= f; i++)
//		result = result * i;
//	return result;
//}
//void Hello(int n) {
//	cout << "Hi~ " << n << endl;
//}



//#include <iostream>
//using namespace std;
//
//int main() {
//	int a = 5;
//	const int& ra = 9;
//	cout << ra << endl;
//
//	//int a = 1;
//	//int b = 2;
//	//const int& c = a; // 초기화
//
//	////c = 3;
//	////c = b; // b의 값을 대입 (참조하는게 아님)
//	////c = 4;
//
//	////cout << a << endl;
//	//cout << c << endl;
//	//a = 5;
//	//cout << c << endl;
//
//
//	// 자료타입 &변수이름 = 대상변수;
//	//short s = 5;
//	//short& rs = s; // 레퍼런스
//	//short* ps = &s; // 포인터
//
//	//cout << s << " " << &s <<  endl;
//	//cout << rs << " " << &rs << endl;
//	//cout << *ps << " " << &ps << endl;
//
//	return 0;
//}


// Modern Style (enum class c++11)
//#include <iostream>
//using namespace std;
//
//enum class Java { PASS, FAIL };
//enum class Python { PASS, FAIL };
//enum class Cplusplus { PASS, FAIL };
//
//int main() {
//	Cplusplus c = Cplusplus::FAIL;
//
//	switch (c) {
//		case Cplusplus::PASS:
//			cout << "합격!";
//			break;
//		case Cplusplus::FAIL:
//			cout << "재수강!";
//			break;
//	}
//	return 0;
//}

// Old Style
//#include <iostream>
//using namespace std;
//
//namespace sophomore {
//	enum Java { PASS, FAIL };
//}
//
//namespace freshman {
//	enum Python { PASS, FAIL };
//}
//
//int main(){
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//enum Color { RED, GREEN, BLUE, YELLOW };
//enum Java { PASS, FAIL };
//enum Python { PASS, FAIL };
//
//int main() {
//	Color c1 = RED;
//	Color c2;
//	
//	// 명시적 Casting 후 대입 가능
//	//Color c3 = (Color)2;
//	Color c3 = (Color)1000;
//	cout << (Color)c3 << endl;
//
//	// 산술연산 불가
//	//c1 = GREEN + BLUE;
//	//c1 = c1 + 2;
//
//	// 정수대입 불가
//	//c2 = 3;
//
//	// 반대의 경우 대입과 산술연산이 가능
//	// 묵시적 Casting
//	//int n = BLUE;
//	//int o = GREEN + BLUE;
//
//	//cout << n << endl;
//	//cout << o << endl;
//
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//enum JOB_KINDS { JOB_NECROMANCER=10, JOB_BARBARIAN, JOB_WIZARD };
//struct Character {
//	JOB_KINDS jobType; // 0: 강령술사, 1: 야만용사, 2:마법사
//};
//int main(){
//	Character c;
//	c.jobType = JOB_WIZARD;
//	if (c.jobType == JOB_WIZARD) {
//		cout << "비전격류!" << endl;
//	}
//
//	return 0;
//}