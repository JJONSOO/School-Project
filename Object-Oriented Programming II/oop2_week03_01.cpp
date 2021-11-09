// 003
//#include <iostream>
//using namespace std;
//union JobUnion {
//	//char name[32]; // 공용체는 가장 큰 멤버 변수의 크기로 메모리 할당
//	long salary;
//	int workerId;
//}uJob;
//struct JobStruct {
//	//char name[32];
//	long salary;
//	int workerId;
//}sJob;
//int main() {
//	uJob.salary = 11;
//	uJob.workerId = 1234;
//
//	sJob.salary = 21;
//	sJob.workerId = 44434;
//
//	cout << uJob.salary << endl;
//	cout << uJob.workerId << endl;
//
//	cout << sJob.salary << endl;
//	cout << sJob.workerId << endl;
//	return 0;
//}

//#include <iostream>
//using namespace std;
//struct LinkedList {
//	int data;
//	LinkedList* p;
//};
//int main() {
//	LinkedList a, b, c;
//	a.data = 99;
//	a.p = &b;
//	b.data = 93;
//	b.p = &c;
//	c.data = 94;
//	c.p = &a;
//
//	cout << c.data << endl;
//	cout << b.p->data << endl;
//	cout << (*b.p).data << endl;
//	cout << a.p->p->data << endl;
//	cout << c.p->p->p->data << endl;
//
//	//cout << b.data << endl;
//	//cout << a.p->data << endl;
//	return 0;
//}

// 002
//#include <iostream>
//using namespace std;
//struct Rectangle {
//	int x, y;
//	int w, h;
//};
//int main() {
//	Rectangle r = { 15, 10, 50, 70 };
//	Rectangle* pr = &r;
//
//	cout << r.x << " " << (*pr).x << endl;
//	cout << (*pr).y << " " << pr->y << endl;
//	cout << (*pr).h << " " << pr->h << endl;
//	pr->h = 40;
//	(*pr).w = 100;
//	cout << (*pr).h << " " << pr->h << endl;
//	cout << r.w << " " << pr->w << endl;
//
//	return 0;
//}


//#include <iostream>
//using namespace std;
//struct Student {
//	int id; // 4
//	char name[20]; // 1
//	float grade[2]; // 8
//};
//int main() {
//	// 구조체 배열
//	Student sInfos[4] = {
//		{202001,"Lee", {4.3f, 4.1f}},
//		{202010,"Choi", {3.3f, 3.1f}},
//		{202107,"Park", {3.5f, 4.1f}},
//		{202101,"Kim", {4.2f, 3.7f}}
//	};
//
//	for (auto i = 0; i < 4; i++) {
//		cout << sInfos[i].id << endl;
//		cout << sInfos[i].name << endl;
//		cout << sInfos[i].grade[0] << endl;
//		cout << sInfos[i].grade[1] << endl;
//	}
//
//	return 0;
//}


// 001
//#include <iostream>
//int main() {
//	// 포인터 배열
//	short a, b, c=5, d=2;
//	short* arr[4];
//	arr[0] = &a;
//	arr[1] = &b;
//	arr[2] = &c;
//	arr[3] = &d;
//
//	std::cout << arr[1] << std::endl;
//	std::cout << arr[2] << std::endl;
//	std::cout << arr[3] << std::endl;
//	std::cout << &arr[1] << std::endl;
//	std::cout << &arr[2] << std::endl;
//	std::cout << &arr[3] << std::endl;
//	std::cout << *arr[1] << std::endl;
//	std::cout << *arr[2] << std::endl;
//	std::cout << *arr[3] << std::endl;
//
//
//	// 배열 포인터
//	//long arry[10];
//	//long(*p)[10] = &arry;
//
//	//(*p)[5] = 100;
//	//std::cout << arry[5] << std::endl;
//	//std::cout << (*p)[5] << std::endl;
//
//
//	//int arr[5];
//	//int* p1 = &arr[1];
//	//int* p2 = &arr[4];
//
//	//std::cout << p1 << std::endl;
//	//std::cout << p2 << std::endl;
//	//std::cout << p2 - p1 << std::endl;
//
//
//	//short arr[5];
//	//short* parr = &arr[2];
//
//	//std::cout << parr << std::endl;
//	//std::cout << parr + 1 << std::endl;
//	//std::cout << parr + 2 << std::endl;
//	//std::cout << parr - 2 << std::endl;
//	return 0;
//}