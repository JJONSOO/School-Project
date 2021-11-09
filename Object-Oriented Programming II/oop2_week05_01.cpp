//#include <iostream>
//using namespace std;
//int main() {
//	short* p = new short[100]; // 200byte 동적 할당	
//	cout << p << endl;
//	delete[] p; // 해제
//	p = NULL;
//
//	cout << p << endl;
//	delete[] p; // 해제
//	p = NULL;
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//int main() {
//	int* p = new int; // 할당
//	*p = 486;
//	cout << *p << endl;
//	delete p; // 해제
//	return 0;
//}



//#include <iostream>
//using namespace std;
//int main() {
//	int* p;
//	int length, total = 0;
//	double average;
//	cin >> length;
//	p = new int[length]; // 동적 메모리 할당
//
//	for (auto i = 0; i < length; ++i)
//		cin >> *(p + i);
//
//	for (auto i = 0; i < length; ++i)
//		total = total + p[i];
//
//	average = total / (double)length;
//	cout << total << endl;
//	cout << average << endl;
//
//	delete[] p;// 사용한 메모리 해제
//	return 0;
//}











//#include <iostream>
//#include <functional>
//using namespace std;
//// 익명함수, 함수객체를 생성
//// 함수 포인터와 함수객체의 장점을 지닌다.
//// 캡쳐 기능을 통해 함수 밖의 변수에 접근할 수 있고
//// & 기호를 통해 람다함수 안에서도 외부 변수의 값을 변경할 수 있다.
//// 재귀 호출도 가능하다.
//
//int main() {
//	// 람다에서 재귀를 구현 할 때 auto 타입으로는 추론 불가
//	// 반드시 대입하려고 하는 함수의 타입이 명시되어야 함.
//	function<int(int)> fact = [&fact](int n)-> int {		
//		return n <= 1 ? 1 : n * fact(n - 1);
//		//if (n <= 1)
//		//	return 1;
//		//else
//		//	return n * fact(n - 1);
//	};
//	cout << fact(6) << endl;
//
//
//	//auto power = [](int b, int e) {
//	//	int r = 1;
//	//	for (auto i = 1; i <= e; i++)
//	//		r = r * b;
//	//	return r;
//	//};
//	//cout << power(2, 8) << endl;
//	//cout << power(4, 2) << endl;
//	return 0;
//}




//#include <iostream>
//using namespace std;
//int main() {
//	//short c = 5, d = 7;
//	//auto inha = [&c, d](float a, int b) -> int {
//	//	c = -5;
//	//	return a + b + c + d;
//	//};
//	//cout << inha(1.9f, 2) << endl;
//	//cout << c << endl;
//
//	//short c = 5, d = 7;
//	//auto inha = [&](float a, int b) -> int {
//	//	c = -5;
//	//	d = 8;
//	//	return a + b + c + d;
//	//};
//	//cout << inha(1.9f, 2) << endl;
//
//	//short c = 5, d = 7;
//	//auto inha = [=](float a, int b) -> int {
//	//	return a + b + c + d;
//	//};
//	//cout << typeid(inha).name() << endl;
//	//cout << inha(1.9f, 2) << endl;
//	
//	//short c = 5, d = 7;
//	//auto inha = [=](float a, int b) -> int {
//	//	return a + b + c + d;
//	//}(1.9f, 2);
//	//cout << typeid(inha).name() << endl;
//	//cout << inha << endl;
//	return 0;
//}




//#include <iostream>
//using namespace std;
//int main() {
//	// Lambda Expression (C++11, 14)
//	// [캡쳐블럭](매개변수리스트)->리턴타입{함수바디};
//	[]()->void {};
//	[]() {};
//	[] {};
//
//	// 맨끝의 소괄호 쌍은 람다표현식을 즉시 실행시키는 역할
//	//[] {cout << "Hi Lambda!" << endl; }();
//
//	//auto inha = [] {cout << "Hi Lambda!" << endl; };
//	//inha();
//
//	//auto inha = []() { return 5 + 10; };
//	//cout << inha() << endl;
//	
//	//auto inha = [](int a, int b) { return a + b; };
//	//cout << inha(5, 10) << endl;
//
//	//auto inha = [](int a, int b) -> int { return a + b; };
//	//cout << inha(5, 10) << endl;
//	
//	//auto inha = [](int a, int b) -> int { return a + b; }(5, 10);
//	//cout << inha << endl;
//
//	//auto inha = [](float a, int b) -> int { return a + b; };
//	//cout << inha(7.7f, 2) << endl;
//
//	//auto inha = [](float a, int b) -> float { return a + b; };
//	//cout << inha(7.7f, 2) << endl;
//
//	//auto inha = [](float a, int b) { return a + b; };
//	//cout << inha(7.7f, 2) << endl;
//
//	short c = 5, d = 7;
//	auto inha = [c, d](float a, int b) -> int {
//		return a + b + c + d;
//	};
//	cout << inha(1.9f, 2) << endl;
//
//	return 0;
//}













