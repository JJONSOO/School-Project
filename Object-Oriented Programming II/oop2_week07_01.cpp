//#include <iostream>
//using namespace std;
//class DynamicArray {
//public:
//	int* arr;
//
//	DynamicArray(int arraySize);
//	~DynamicArray();
//};
//DynamicArray::DynamicArray(int arraySize) {
//	arr = new int[arraySize];// 동적 메모리 할당
//}
//DynamicArray::~DynamicArray() {
//	cout << "소멸자 동작" << endl;
//	delete[] arr;
//	arr = NULL;
//}
//int main() {
//	int size;
//	cout << "몇 개의 정수를 입력하시겠소? ";
//	cin >> size;
//
//	DynamicArray da(size);
//
//	for (int i = 0; i < size; ++i)
//		cin >> da.arr[i];
//
//	for (int i = size - 1; i >= 0; --i)
//		cout << da.arr[i] << " ";
//	cout << "\n";
//
//	return 0;
//}


//#include <iostream>
//using namespace std;
//class NeedConstructor {
//public:
//	const int max;
//	int& ref;
//	int temp;
//
//	NeedConstructor();
//	NeedConstructor(int cnt, int& number);
//};
//NeedConstructor::NeedConstructor()
//	:max(100),ref(temp) {
//	temp = 10;
//}
//NeedConstructor::NeedConstructor(int cnt, int& number)
//	: max(cnt), ref(number) {
//	temp = 10;
//}
//int main(){
//	//NeedConstructor cr;
//	int num = 400;
//	NeedConstructor cr(500, num);
//
//	cout << cr.max << endl;
//	cout << cr.ref << endl;
//}


//#include <iostream>
//using namespace std;
//// 1. class 키워드를 사용
//// 2. public과 같은 접근제어와 관련된 키워드 사용
//// 3. 멤버 함수(메서드)를 정의할 수 있다
//
//// 생성자 : 객체를 생성할 때 자동적으로 호출되는 함수
//// 소멸자 : 객체가 소멸될 때 자동으로 호출되는 함수
//class Point {
//public:
//	int x, y;
//
//	// 생성자들
//	Point(); // 생성자는 리턴타입이 없다, 클래스의 이름과 같다
//	Point(int _x, int _y);
//	// 복사 생성자
//	// 자신과 동일한 타입의 객체에 대한 레퍼런스를 인자로 받는 생성자
//	//Point(Point& pt);
//	Point(const Point& pt);
//
//	// 메서드
//	void Print();
//};
//// 1. 클래스 정의 안에는 메서드의 프로토타입만 남겨둔다
//// 2. 클래스 정의 밖에서는 범위 지정 연산자를 사용해서 함수를 정의
//Point::Point() {
//	x = 0;
//	y = 0;
//}
//Point::Point(int _x, int _y) {
//	x = _x;
//	y = _y;
//}
//Point::Point(const Point& pt) {
//	cout << "Copy constructor!" << endl;
//	x = pt.x;
//	y = 0;
//}
//
//void Point::Print() {
//	cout << x << ", " << y << endl;
//};
//
//int main() {
//	Point p1, p2, p4, p5(200,150);
//	p1.x = 10;
//	p1.y = 10;
//	p2.x = 20;
//	p2.y = 20;
//
//	Point p6(p1);
//	p5.Print();
//	p4.Print();
//
//	Point p3 = p2; // 초기화
//	p3.Print();
//	p3 = p1; // 대입
//	p3.Print();
//
//	p1.Print();
//	p2.Print();
//	return 0;
//}