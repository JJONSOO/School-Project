#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;



// �߿��� Parameter ��
fstream bfile;

int entry_num = 0;  //block �ϳ��� entry ��

int depth = 0;

int rootBID = 0;

int block_num = 0;   //block ���� -> BID 

int block_Size = -1;   //ó�� �Է°��� ���� �޶����� block�� ������

//Entry ����  leaf node, non-leaf node �� ���� ���� �޶�����.

class Entry {

public:
    int key;

    int value;

    Entry(int _key, int _value) { key = _key; value = _value; }

};

//Node ����  leaf node, non-leaf node �� ���� ���� �޶�����.
class Node {

public:

    bool LeafCheck;

    int BID;

    int NextBid;

    vector<Entry> linked_list;

    Node(int _BID) { BID = _BID; }

};


//�� ��ɾ �����ϱ����� �߿��� parameter �� ����
void ready(char* filename) {

    bfile.open(filename, ios::binary | ios::out | ios::in);

    bfile.read(reinterpret_cast<char*>(&block_Size), 4);

    bfile.read(reinterpret_cast<char*>(&rootBID), sizeof(rootBID));

    bfile.read(reinterpret_cast<char*>(&depth), sizeof(depth));

    bfile.seekg(0, ios::beg); bfile.seekp(0, ios::beg);

    entry_num = (block_Size - 4) / 8;   //entry ���� �°� ����

    bfile.seekg(0, ios::end);

    block_num = ((int)(bfile.tellg()) - 12) / block_Size;   //����� �� ���� = (����ũ��-12) / block_Size;
}
// file modify
void FileFixed(Node* modified) {

    // physical offset �̵�

    bfile.seekp(12 + ((modified->BID - 1) * block_Size), ios::beg);

    // non leaf node , ó���� nextBID

    if (!modified->LeafCheck) {

        bfile.write((char*)&(modified->NextBid), sizeof(int));

    }

    // �߰��� entry �Է�

    for (int i = 0; i < modified->linked_list.size(); i++) {

        bfile.write((char*)&(modified->linked_list[i].key), sizeof(int));

        bfile.write((char*)&(modified->linked_list[i].value), sizeof(int));

    }
    // ������ 0���� ä���.

    for (int i = 0; i < entry_num - (modified->linked_list.size()); i++) {

        int zero = 0;

        bfile.write((char*)&zero, sizeof(int));

        bfile.write((char*)&zero, sizeof(int));

    }
    // leaf node , �������� nextBID

    if (modified->LeafCheck) {

        bfile.write((char*)&(modified->NextBid), sizeof(int));

    }

}

//BID block file ���� �����´�.

Node findNode(int BID, int nowd) {

    Node* findNode_start = new Node(BID);

    //ã������ BID �� block -> Leaf?

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

//search�� �ϸ鼭 ������ ���� -> Ž���� ����������  route�� ���� -> ��ġ ã�� �� �ִ�.

vector<Node> route;

int search(int key) {

    if (rootBID == 0) return 0;

    route.clear();

    int search_start = 0;

    Node root = findNode(rootBID, 0);

    Node* search_start_node = &root;

    //root �ۿ� ���� ���

    if (depth == 0) {

        route.push_back(findNode(rootBID, 0));

        return rootBID;

    }

    route.push_back(*search_start_node);

    //Leaf node �� �ɶ����� ������ Ž��

    while (search_start != depth) {

        //��� ����

        if (key < search_start_node->linked_list[0].key) {

            route.push_back(findNode(search_start_node->NextBid, ++search_start));

        }

        //��� ������

        else if (key >= search_start_node->linked_list.back().key)

            route.push_back(findNode(search_start_node->linked_list.back().value, ++search_start));

        //��� �߰�

        else {

            for (int i = 0; i < search_start_node->linked_list.size() - 1; i++) {

                if (search_start_node->linked_list[i].key <= key && key < search_start_node->linked_list[i + 1].key) {

                    route.push_back(findNode(search_start_node->linked_list[i].value, ++search_start));

                    break;

                }

            }
        }

        //���� ��ǥ�� route �������� push_back �Ǿ��ִ�.

        search_start_node = &route.back();

    }

    return search_start_node->BID;

}

// block �� entry ���� key ������ ���� 

bool sort_by_entry_key(Entry& x, Entry& y) {

    return x.key < y.key;

}

// block �� entry ����

void insert(int key, int value, Node* final, int location) {

    // full�� �ƴѰ�� -> �߰����ϰ� ������ ���� ����

    if (final->linked_list.size() < entry_num) {

        final->linked_list.push_back(*(new Entry(key, value)));

        sort(final->linked_list.begin(), final->linked_list.end(), sort_by_entry_key);

        FileFixed(final);

        return;

    }

    //full �̿��� split �� �ؾ� �� ��

    //1. �ϴ� ��ģ��. �̶� entry_num ���� Ŀ���� ��� ���� �ؿ��� ������.

    final->linked_list.push_back(*(new Entry(key, value)));

    sort(final->linked_list.begin(), final->linked_list.end(), sort_by_entry_key);

    //2. ������ �� ���� ����

    int num = entry_num / 2 + 1;

    //num : ���ο� ����� ���ۿ�Ʈ�� �ε�����ȣ

    //3. ������ ���� ���� ���

    Node* half = new Node(++block_num);

    half->LeafCheck = final->LeafCheck;

    //4. ��Ʈ�� ����(������ ���)�� ������ ���� ���� ���� �̵�

    for (int i = 0; i < entry_num - num + 1; i++) {

        half->linked_list.push_back(*(new Entry(final->linked_list[num].key, final->linked_list[num].value)));

        final->linked_list.erase(final->linked_list.begin() + num);

    }

    //5. ���� ������ entry

    Entry half2(half->linked_list[0].key, half->BID);

    //������� �ƴҰ��, ������ ��Ʈ���� value= half.NextBid

    if (final->LeafCheck == false) {

        half->NextBid = half->linked_list[0].value;

        half->linked_list.erase(half->linked_list.begin());

    }

    //��������� ���, ������ �ΰ��� ��带 ������.

    else {

        half->NextBid = final->NextBid;

        final->NextBid = half->BID;

    }

    //root�� split -> root ���� ���� , �ΰ��� ��� ����

    if (final->BID == rootBID) {

        Node root2(++block_num);

        root2.LeafCheck = false;

        rootBID = root2.BID;

        root2.NextBid = final->BID;

        root2.linked_list.push_back(half2);

        depth++;

        //file ���� -> rootBID, depth

        bfile.seekp(4, ios::beg);

        bfile.write((char*)&(root2.BID), sizeof(int));

        bfile.write((char*)&depth, sizeof(int));

        FileFixed(&root2);

        FileFixed(half);

        FileFixed(final);

        return;
    }
    //root�� split ���� ���� ��� ->�� ���� �÷�������

    FileFixed(half);

    FileFixed(final); //���ø��� ���� ���Ͽ��� ����

    //�� ��� �����ؾ� �Ѵٸ�

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

            //key �� ����ִ� Block �� ã�´�.

            Node location = findNode(search(key), depth);

            //Block �ȿ��� key �� value ���� ã�´�

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

    char tmp[20];//txt file ���پ� �����

    int start, end;// range �� ���� �κ� , �� �κ�

    ifstream in;

    ofstream o;

    in.open(input, ios::in);

    o.open(output, ios::out);

    while (in.getline(tmp, sizeof(tmp))) {

        int i = 0, start = 0, end = 0;

        //start ���ϱ� ( ���� ������ )

        for (i; tmp[i] != ','; i++) {

            start = start * 10 + (tmp[i] - '0');

        }

        int s_BID = search(start);   //start BID ����

        if (s_BID == 0) return;

        //end ���ϱ� ( ���� ������ �� )

        for (int j = i + 1; tmp[j] != '\0' && tmp[j] != '\t'; j++) {

            end = end * 10 + (tmp[j] - '0');

        }



        route.clear();

        route.push_back(findNode(s_BID, depth));

        Node* location = &route[0];

        while (1) {   //�������� ��� ��ȸ

            bool overrange = false;   //end ���� ��� ��� while �� �����.

            for (int i = 0; i < location->linked_list.size(); i++) {   //target������ ��Ʈ������ ���鼭 

                //key�� end������ ����� ��� -> ����

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

        //���� �Ϸ�� \n

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

    route.push_back(findNode(rootBID, 0)); //<0> �ܰ�


    Node* location = &route[0];

    int sizee = location->linked_list.size();

    for (int i = 0; i < sizee; i++) {		//root ���� �����Ͽ� ��� �̾��

        route.push_back(findNode(route[0].linked_list[i].value, 1));

    }

    location = &route[0];

    oo << (route[0].linked_list[0].key);

    for (int i = 1; i < location->linked_list.size(); i++) {

        oo << ", " << (location->linked_list[i].key);

    }

    //<0>�ܰ� ����

    route.push_back(findNode(route[0].NextBid, 1));	// <1> �ܰ�

    oo << "\n<1>\n\n";

    if (route.size() == 1) return;

    location = &route[1];

    oo << (location->linked_list[0].key);				//1�ܰ� ù �κ�

    for (int i = 1; i < location->linked_list.size(); i++) {

        oo << ", " << (location->linked_list[i].key);

    }


    for (int i = 2; i < route.size(); i++) {	//1�ܰ� �ι�° �κк��� ������ output.txt file 

        location = &route[i];

        for (int j = 0; j < location->linked_list.size(); j++) {

            oo << ", " << (location->linked_list[j].key);

        }

    }

    oo << "\n";

    oo.close();

}

int main(int argc, char* argv[]) {

    //create index �� �� ���δ�. 

    ofstream outF;

    //insert �� �� ���δ�.

    ifstream insertion;

    char command = argv[1][0];

    int zero = 0; //switch ���� zero ������ ���� ���ϹǷ� ���⼭ ����


    switch (command)

    {

    case 'c':

        block_Size = atoi(argv[3]);

        //�Է¹��� file ����

        outF.open(argv[2], ios::binary);

        //ù��°�� block size �ι�°�� RootBID ����°�� Depth �� �Էµȴ�.

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

        while (insertion.getline(tmp, sizeof(tmp))) {   //insert ����

            int i = 0, key = 0, val = 0;

            for (i; tmp[i] != ','; i++) {

                //�ڸ��� ���ϱ� (*10) �� ������ �ڸ� ���� ���ϱ� 

                key = key * 10 + (tmp[i] - '0');

            }

            for (int j = i + 1; tmp[j] != '\0'; j++) {

                //�ڸ��� ���ϱ� (*10) �� ������ �ڸ� ���� ���ϱ� 

                val = val * 10 + (tmp[j] - '0');

            }

            int tmp = search(key);   //route.back()�� ������ġ ����

            if (tmp != 0) insert(key, val, &(route.back()), depth); //(key, rid) ��Ʈ���� route.back() ���� ���� -> depth�� ��Ʈ�Ǵ�

            else {

                // root Node �� ���� ��� 

                Node* target = new Node(++block_num);

                target->LeafCheck = true;

                target->linked_list.push_back(*(new Entry(key, val)));

                rootBID = target->BID;            //rootBID ����

                bfile.seekp(4, ios::beg);         //file���� �����ϱ����� �̵�

                bfile.write(reinterpret_cast<char*>(&target->BID), sizeof(int));      //�̵� �� rootBID ����

                FileFixed(target);

            }

        }

        //ù��°  block size �ι�° RootBID ����° Depth ���� 

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