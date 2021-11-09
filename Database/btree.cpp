#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;



// 중요한 Parameter 들
fstream bfile;

int entry_num = 0;  //block 하나당 entry 수

int depth = 0;

int rootBID = 0;

int block_num = 0;   //block 개수 -> BID 

int block_Size = -1;   //처음 입력값에 따라 달라지는 block의 사이즈

//Entry 구조  leaf node, non-leaf node 에 따라 값이 달라진다.

class Entry {

public:
    int key;

    int value;

    Entry(int _key, int _value) { key = _key; value = _value; }

};

//Node 구조  leaf node, non-leaf node 에 따라 값이 달라진다.
class Node {

public:

    bool LeafCheck;

    int BID;

    int NextBid;

    vector<Entry> linked_list;

    Node(int _BID) { BID = _BID; }

};


//각 명령어를 시작하기전에 중요한 parameter 들 설정
void ready(char* filename) {

    bfile.open(filename, ios::binary | ios::out | ios::in);

    bfile.read(reinterpret_cast<char*>(&block_Size), 4);

    bfile.read(reinterpret_cast<char*>(&rootBID), sizeof(rootBID));

    bfile.read(reinterpret_cast<char*>(&depth), sizeof(depth));

    bfile.seekg(0, ios::beg); bfile.seekp(0, ios::beg);

    entry_num = (block_Size - 4) / 8;   //entry 개수 맞게 수정

    bfile.seekg(0, ios::end);

    block_num = ((int)(bfile.tellg()) - 12) / block_Size;   //저장된 블럭 개수 = (파일크기-12) / block_Size;
}
// file modify
void FileFixed(Node* modified) {

    // physical offset 이동

    bfile.seekp(12 + ((modified->BID - 1) * block_Size), ios::beg);

    // non leaf node , 처음에 nextBID

    if (!modified->LeafCheck) {

        bfile.write((char*)&(modified->NextBid), sizeof(int));

    }

    // 중간에 entry 입력

    for (int i = 0; i < modified->linked_list.size(); i++) {

        bfile.write((char*)&(modified->linked_list[i].key), sizeof(int));

        bfile.write((char*)&(modified->linked_list[i].value), sizeof(int));

    }
    // 나머지 0으로 채운다.

    for (int i = 0; i < entry_num - (modified->linked_list.size()); i++) {

        int zero = 0;

        bfile.write((char*)&zero, sizeof(int));

        bfile.write((char*)&zero, sizeof(int));

    }
    // leaf node , 마지막에 nextBID

    if (modified->LeafCheck) {

        bfile.write((char*)&(modified->NextBid), sizeof(int));

    }

}

//BID block file 에서 가져온다.

Node findNode(int BID, int nowd) {

    Node* findNode_start = new Node(BID);

    //찾으려는 BID 의 block -> Leaf?

    findNode_start->LeafCheck = (depth == nowd);

    int key, value;

    bfile.seekg((((findNode_start->BID) - 1) * block_Size) + 12, ios::beg);   //Btree.bin

    //nonleaf

    if (!findNode_start->LeafCheck) {

        bfile.read(reinterpret_cast<char*>(&key), sizeof(int));

        findNode_start->NextBid = key;

    }

    for (int i = 0; i < entry_num; i++) {

        bfile.read(reinterpret_cast<char*>(&key), sizeof(int));

        bfile.read(reinterpret_cast<char*>(&value), sizeof(int));

        if (key == 0) continue;

        findNode_start->linked_list.push_back(*(new Entry(key, value)));

    }
    //leaf

    if (findNode_start->LeafCheck) {

        bfile.read(reinterpret_cast<char*>(&key), sizeof(int));

        findNode_start->NextBid = key;

    }

    return *findNode_start;
}

//search를 하면서 저장할 노드들 -> 탐색한 순서순으로  route에 저장 -> 위치 찾을 수 있다.

vector<Node> route;

int search(int key) {

    if (rootBID == 0) return 0;

    route.clear();

    int search_start = 0;

    Node root = findNode(rootBID, 0);

    Node* search_start_node = &root;

    //root 밖에 없을 경우

    if (depth == 0) {

        route.push_back(findNode(rootBID, 0));

        return rootBID;

    }

    route.push_back(*search_start_node);

    //Leaf node 가 될때까지 밑으로 탐색

    while (search_start != depth) {

        //노드 왼쪽

        if (key < search_start_node->linked_list[0].key) {

            route.push_back(findNode(search_start_node->NextBid, ++search_start));

        }

        //노드 오른쪽

        else if (key >= search_start_node->linked_list.back().key)

            route.push_back(findNode(search_start_node->linked_list.back().value, ++search_start));

        //노드 중간

        else {

            for (int i = 0; i < search_start_node->linked_list.size() - 1; i++) {

                if (search_start_node->linked_list[i].key <= key && key < search_start_node->linked_list[i + 1].key) {

                    route.push_back(findNode(search_start_node->linked_list[i].value, ++search_start));

                    break;

                }

            }
        }

        //최종 목표는 route 마지막에 push_back 되어있다.

        search_start_node = &route.back();

    }

    return search_start_node->BID;

}

// block 내 entry 들을 key 값으로 정렬 

bool sort_by_entry_key(Entry& x, Entry& y) {

    return x.key < y.key;

}

// block 내 entry 삽입

void insert(int key, int value, Node* final, int location) {

    // full이 아닌경우 -> 추가만하고 정렬후 파일 수정

    if (final->linked_list.size() < entry_num) {

        final->linked_list.push_back(*(new Entry(key, value)));

        sort(final->linked_list.begin(), final->linked_list.end(), sort_by_entry_key);

        FileFixed(final);

        return;

    }

    //full 이여서 split 을 해야 할 때

    //1. 일단 합친다. 이때 entry_num 보다 커져도 상관 없음 밑에서 나눈다.

    final->linked_list.push_back(*(new Entry(key, value)));

    sort(final->linked_list.begin(), final->linked_list.end(), sort_by_entry_key);

    //2. 왼쪽이 더 많게 나눔

    int num = entry_num / 2 + 1;

    //num : 새로운 노드의 시작엔트리 인덱스번호

    //3. 떨어져 나온 절반 노드

    Node* half = new Node(++block_num);

    half->LeafCheck = final->LeafCheck;

    //4. 엔트리 절반(오른쪽 노드)를 떨엉져 나온 절반 노드로 이동

    for (int i = 0; i < entry_num - num + 1; i++) {

        half->linked_list.push_back(*(new Entry(final->linked_list[num].key, final->linked_list[num].value)));

        final->linked_list.erase(final->linked_list.begin() + num);

    }

    //5. 따로 떨어진 entry

    Entry half2(half->linked_list[0].key, half->BID);

    //리프노드 아닐경우, 삭제될 엔트리의 value= half.NextBid

    if (final->LeafCheck == false) {

        half->NextBid = half->linked_list[0].value;

        half->linked_list.erase(half->linked_list.begin());

    }

    //리프노드일 경우, 나눠진 두개의 노드를 붙힌다.

    else {

        half->NextBid = final->NextBid;

        final->NextBid = half->BID;

    }

    //root가 split -> root 새로 생성 , 두개의 노드 연결

    if (final->BID == rootBID) {

        Node root2(++block_num);

        root2.LeafCheck = false;

        rootBID = root2.BID;

        root2.NextBid = final->BID;

        root2.linked_list.push_back(half2);

        depth++;

        //file 수정 -> rootBID, depth

        bfile.seekp(4, ios::beg);

        bfile.write((char*)&(root2.BID), sizeof(int));

        bfile.write((char*)&depth, sizeof(int));

        FileFixed(&root2);

        FileFixed(half);

        FileFixed(final);

        return;
    }
    //root를 split 하지 않을 경우 ->윗 노드로 올려보낸다

    FileFixed(half);

    FileFixed(final); //스플릿된 노드들 파일에서 수정

    //윗 노드 수정해야 한다면

    if (location > 0) {

        insert(half2.key, half2.value, &route[location - 1], location - 1);

        FileFixed(&route[location - 1]);

    }

}

//point search

void point(char* input, char* output) {

    ifstream i;

    ofstream o;

    i.open(input, ios::in);

    o.open(output, ios::out);

    char tmp[25]; int key, value;

    while (i.getline(tmp, sizeof(tmp))) {

        key = atoi(tmp);

        if (key != 0) {

            int i = 0, key = 0;

            for (i; tmp[i] != '\0'; i++) {

                key = key * 10 + (tmp[i] - '0');

            }

            //key 가 들어있는 Block 를 찾는다.

            Node location = findNode(search(key), depth);

            //Block 안에서 key 의 value 값을 찾는다

            for (int i = 0; i < location.linked_list.size(); i++) {

                if (location.linked_list[i].key == key) {

                    value = location.linked_list[i].value; break;

                }

            }

            //write

            o << key << "," << value << "\n";

        }
    }

    i.close();

    o.close();
}

//Range search

void range(char* input, char* output) {

    char tmp[20];//txt file 한줄씩 만들기

    int start, end;// range 의 시작 부분 , 끝 부분

    ifstream in;

    ofstream o;

    in.open(input, ios::in);

    o.open(output, ios::out);

    while (in.getline(tmp, sizeof(tmp))) {

        int i = 0, start = 0, end = 0;

        //start 구하기 ( 범위 시작점 )

        for (i; tmp[i] != ','; i++) {

            start = start * 10 + (tmp[i] - '0');

        }

        int s_BID = search(start);   //start BID 저장

        if (s_BID == 0) return;

        //end 구하기 ( 범위 마지막 점 )

        for (int j = i + 1; tmp[j] != '\0' && tmp[j] != '\t'; j++) {

            end = end * 10 + (tmp[j] - '0');

        }



        route.clear();

        route.push_back(findNode(s_BID, depth));

        Node* location = &route[0];

        while (1) {   //리프노드들 모두 순회

            bool overrange = false;   //end 범위 벗어날 경우 while 문 벗어난다.

            for (int i = 0; i < location->linked_list.size(); i++) {   //target노드들의 엔트리들을 보면서 

                //key가 end범위를 벗어나는 경우 -> 종료

                if (location->linked_list[i].key > end) {

                    overrange = true;

                    break;

                }

                else if (location->linked_list[i].key > start) {

                    o << (location->linked_list[i].key) << "," << (location->linked_list[i].value) << " \t ";

                }

            }

            if (overrange) break;

            if (location->NextBid == 0) break;

            route.push_back(findNode(location->NextBid, depth));

            location = &(route.back());

        }

        //한줄 완료시 \n

        o << "\n";

    }
    in.close();

    o.close();

    route.clear();
}

//print B+ Tree

void print(char* filename) {

    ofstream oo;

    oo.open(filename, ios::out);

    route.clear();

    oo << "<0>\n\n";

    route.push_back(findNode(rootBID, 0)); //<0> 단계


    Node* location = &route[0];

    int sizee = location->linked_list.size();

    for (int i = 0; i < sizee; i++) {		//root 부터 시작하여 계속 이어나감

        route.push_back(findNode(route[0].linked_list[i].value, 1));

    }

    location = &route[0];

    oo << (route[0].linked_list[0].key);

    for (int i = 1; i < location->linked_list.size(); i++) {

        oo << ", " << (location->linked_list[i].key);

    }

    //<0>단계 종료

    route.push_back(findNode(route[0].NextBid, 1));	// <1> 단계

    oo << "\n<1>\n\n";

    if (route.size() == 1) return;

    location = &route[1];

    oo << (location->linked_list[0].key);				//1단계 첫 부분

    for (int i = 1; i < location->linked_list.size(); i++) {

        oo << ", " << (location->linked_list[i].key);

    }


    for (int i = 2; i < route.size(); i++) {	//1단계 두번째 부분부터 끝까지 output.txt file 

        location = &route[i];

        for (int j = 0; j < location->linked_list.size(); j++) {

            oo << ", " << (location->linked_list[j].key);

        }

    }

    oo << "\n";

    oo.close();

}

int main(int argc, char* argv[]) {

    //create index 할 때 쓰인다. 

    ofstream outF;

    //insert 할 때 쓰인다.

    ifstream insertion;

    char command = argv[1][0];

    int zero = 0; //switch 에서 zero 선언을 하지 못하므로 여기서 선언


    switch (command)

    {

    case 'c':

        block_Size = atoi(argv[3]);

        //입력받은 file 생성

        outF.open(argv[2], ios::binary);

        //첫번째로 block size 두번째론 RootBID 세번째론 Depth 가 입력된다.

        outF.write(reinterpret_cast<char*>(&block_Size), sizeof(int));

        outF.write(reinterpret_cast<char*>(&zero), sizeof(int));

        outF.write(reinterpret_cast<char*>(&zero), sizeof(int));

        entry_num = (block_Size - 4) / 8;

        outF.close();

        break;

    case 'i':

        ready(argv[2]);

        insertion.open(argv[3]);

        insertion.seekg(0, ios::beg);

        char tmp[25];

        int key, val;

        while (insertion.getline(tmp, sizeof(tmp))) {   //insert 진행

            int i = 0, key = 0, val = 0;

            for (i; tmp[i] != ','; i++) {

                //자릿수 정하기 (*10) 및 마지막 자리 숫자 더하기 

                key = key * 10 + (tmp[i] - '0');

            }

            for (int j = i + 1; tmp[j] != '\0'; j++) {

                //자릿수 정하기 (*10) 및 마지막 자리 숫자 더하기 

                val = val * 10 + (tmp[j] - '0');

            }

            int tmp = search(key);   //route.back()에 삽입위치 저장

            if (tmp != 0) insert(key, val, &(route.back()), depth); //(key, rid) 엔트리를 route.back() 블럭에 삽입 -> depth로 루트판단

            else {

                // root Node 가 없을 경우 

                Node* target = new Node(++block_num);

                target->LeafCheck = true;

                target->linked_list.push_back(*(new Entry(key, val)));

                rootBID = target->BID;            //rootBID 설정

                bfile.seekp(4, ios::beg);         //file에도 수정하기위해 이동

                bfile.write(reinterpret_cast<char*>(&target->BID), sizeof(int));      //이동 후 rootBID 수정

                FileFixed(target);

            }

        }

        //첫번째  block size 두번째 RootBID 세번째 Depth 설정 

        bfile.seekp(4, ios::beg);

        bfile.write(reinterpret_cast<char*> (&rootBID), sizeof(int));

        bfile.write(reinterpret_cast<char*> (&depth), sizeof(int));

        insertion.close();

        break;

    case 's':

        ready(argv[2]);

        point(argv[3], argv[4]);

        break;

    case 'r':

        ready(argv[2]);

        range(argv[3], argv[4]);

        break;

    case 'p':

        ready(argv[2]);

        print(argv[3]);

        break;
    }

    bfile.close();

    return 0;

}