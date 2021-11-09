// inline variable keyword (C++17)
#include <iostream>
#include "test.h"
using namespace std;
int main() {
	Test aa;
	cout << aa.a++ << endl;
	return 0;
}

//#include <iostream>
//using namespace std;
////int main() {
////	cout << "1" << endl;
////	cout << "2" << endl;
////	cout << "3" << endl;
////	return 0;
////}
//inline void Test(){
//	cout << "1" << endl;
//	cout << "2" << endl;
//	cout << "3" << endl;
//}
//int main() {
//	Test();
//	return 0;
//}



// 정적(static)멤버 : 모든 객체가 공유하는 멤버.
//#include <iostream>
//#include <string>
//using namespace std;
//class Student {
//public:
//	string name;
//	int sNo;
//
//	Student(const string& name_arg, int stdNumber);
//	~Student();
//public:
//	static int student_count;
//	static void PrintStdCount();
//};
//int Student::student_count = 0;
//void Student::PrintStdCount() {
//	cout << "Student 객체 수 = " << student_count << "\n";
//}
//Student::Student(const string& name_arg, int stdNumber) {
//	student_count++;
//
//	name = name_arg;
//	sNo = stdNumber;
//}
//Student::~Student() {
//	student_count--;
//}
//void Func() {
//	Student std1("김인하", 20191234);//객체 생성 +1
//	Student std2("박인하", 20171111);//객체 생성 +1
//
//	Student::PrintStdCount(); //3명출력
//	// Func함수 끝날 때 std1, std2 객체가 소멸
//}
//int main() {
//	Student::PrintStdCount();
//	Student std("최인하", 20202323);//객체 생성 +1
//	Student::PrintStdCount();
//	Func();
//	Student::PrintStdCount();
//	return 0;
//}


// 접근제어
//#include <iostream>
//using namespace std;
//class AccessControl{
//public:
//	char publicData;
//	void publicFunc() {};
//protected:
//	int protectedData;
//	void protectedFunc() {};
//private:
//	float privateData;
//	void privateFunc() {};
//public:
//	void AccessAllMembers();
//};
//void AccessControl::AccessAllMembers() {
//	publicData = 'A';	// 성공
//	publicFunc();		// 성공
//	protectedData = 100;	// 실패
//	protectedFunc();  	// 실패
//	privateData = 4.5f;	// 실패
//	privateFunc();		// 실패
//}
//int main(){
//	AccessControl ac;
//	ac.AccessAllMembers();
//	//ac.publicData = 'A';	// 성공
//	//ac.publicFunc();		// 성공
//	//ac.protectedData = 100;	// 실패
//	//ac.protectedFunc();  	// 실패
//	//ac.privateData = 4.5f;	// 실패
//	//ac.privateFunc();		// 실패
//
//	return 0;
//}