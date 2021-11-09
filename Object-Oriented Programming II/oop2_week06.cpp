//#include <iostream>
//#include "ex1.h"
//using namespace std;
//int main() {
//	int r;
//	r = Plus(3, 7);
//	return 0;
//}

//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//#include <string>
//using namespace std;
//int main() {
//	char cstyle[3];
//	string cppstyle;
//
//	//cin >> cstyle;
//	//cin >> cppstyle;
//	cin.getline(cstyle, 3);
//	cin.clear();
//	getline(cin, cppstyle);
//
//	cout << cstyle << endl;
//	cout << cppstyle << endl;
//	return 0;
//}


//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//using namespace std;
//int main() {
//	string cppstyle = "Hell!";
//	char* cstyle = new char[cppstyle.size() + 1];
//
//	strcpy(cstyle, cppstyle.c_str());
//
//	cstyle[0] = 'Y';
//
//	cout << cstyle << endl;
//	cout << cppstyle << endl;
//
//	delete[] cstyle;
//	cstyle = NULL;
//	return 0;
//}


//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//using namespace std;
//int main() {
//	string cppstyle = "Hell!";
//	const char* cstyle = NULL;
//
//	cstyle = cppstyle.c_str();
//
//	cout << cstyle << endl;
//	cout << cppstyle << endl;
//	return 0;
//}


//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//using namespace std;
//int main() {
//	char cstyle[] = "Hi~";
//	string cppstyle;
//
//	cppstyle = cstyle;
//	cppstyle[0] = 'A';
//	cout << cstyle << endl;
//	cout << cppstyle << endl;
//	return 0;
//}


// find, substr
//#include <iostream>
//using namespace std;
//int main() {
//	string str = "Hi, Inha Univ.";
//	cout << str.find("Univ.") << endl;
//	string capture = str.substr(4, 4);
//	cout << capture << endl;
//
//	return 0;
//}

// C++ Style
//#include <iostream>
//using namespace std;
//int main() {
//	string str1 = "Inha";
//	string str2 = "Inha";
//
//	if (str1 == str2) {
//		cout << "같다" << endl;
//		cout << typeid((str1 == str2)).name() << endl;
//	}
//	else {
//		cout << "다르다" << endl;
//		cout << (str1 == str2) << endl;
//	}
//
//	//str1 = str1 + str2;
//	//cout << str1 << endl;
//	//cout << str2 << endl;
//
//	return 0;
//}



// Old Style (C Style)
//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//using namespace std;
//int main() {
//	char str1[10] = "Inha";
//	char str2[] = "Inha";
//
//	if (strcmp(str1, str2) == 0)
//		cout << "같다" << endl;
//	else {
//		cout << "다르다" << endl;
//		cout << strcmp(str1, str2) << endl;
//	} // ascii  str1 < str2 -1 리턴, str1 > str2 1 리턴 
//		
//	//strcat(str1, str2);
//	//cout << str1 << endl;
//	//cout << str2 << endl;
//
//	return 0;
//}


// C++ Style
//#include <iostream>
//using namespace std;
//int main() {
//	string src = "Inha Univ";
//	string dest;
//
//	cout << src.size() << endl;
//
//	dest = src;
//
//	cout << src << endl;
//	cout << dest << endl;
//
//	return 0;
//}


// Old Style (C Style)
//#pragma warning(disable:4996)
//#include <iostream>
//#include <cstring>
//using namespace std;
//int main() {
//	char src[] = "Inha Univ";
//	int len = strlen(src);
//	cout << len << endl;
//
//	char* dest = new char[len + 1];
//	strcpy(dest, src);
//
//	cout << src << endl;
//	cout << dest << endl;
//
//	delete[] dest;
//	dest = NULL;
//
//	return 0;
//}



//#include <iostream>
//using namespace std;
//char* ReverseString(const char* src, int len){
//	char* rev = new char[len + 1];
//	for (auto i = 0; i < len; ++i)
//		rev[i] = src[len - i - 1];
//	rev[len] = NULL;
//	return rev;
//}
//int main(){
//	char orig[] = "Inha";
//	char* copy = ReverseString(orig, 4);
//	cout << orig << "\n";
//	cout << copy << "\n";
//	delete[] copy;
//	copy = NULL;
//	return 0;
//}