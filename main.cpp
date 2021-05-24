#include "myBinaryTree.h"
#include "mySet.h"

#include <iostream>
#include <ctime>

void func1(std::string str1) {
    char c;
    for (int i = 0; i < str1.length(); i++) {
        c = str1[i];
    }
}

void func2(const std::string& str1) {
    char c;
    for (int i = 0; i < str1.length(); i++) {
        c = str1[i];
    }
}

void func3(std::string* str1) {
    char c;
    for (int i = 0; i < str1->length(); i++) {
        c = str1->operator[](i);
    }
}

using namespace std;
int main() {
/*
    int count = 400000;

    string str;
    for (int i = 0; i < 10000; i++) {
        str += (char) (i % 256);
    }

    clock_t time1, time2;
    time1 = clock();
    for (int i = 0; i < count; i++) {
        func1(str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    time1 = clock();
    for (int i = 0; i < count; i++) {
        func2(str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    time1 = clock();
    for (int i = 0; i < count; i++) {
        func3(&str);
    }
    time2 = clock();
    cout << time2 - time1 << endl;

    return 0;
*/
    mySet<int> set1, set2;
    for (int i = 0; i < 20; i++) {
        set1.add(i);
        set2.add(i*2);
    }

    cout << set1 << endl << set2 << endl;
    cout << set1 + set2 << endl;
    cout << set1 * set2 << endl;
    cout << set1 - set2 << endl;
    cout << (set1 xor set2 ) << endl;

    myBinaryTree<int, int> tree;
    for (int i = 0; i < 20; i++)
        tree.insert(i, i);

    cout << tree.strLikeList() << endl;
    cout << tree << endl;

    return 0;
}