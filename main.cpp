#include "myBinaryTree.h"

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
    myBinaryTree<int, int> binaryTree1;
    myBinaryTree<int, int> binaryTree2;

    for (int i = 0, j = 1; i < 20; i++, j *= 2) {
        binaryTree1.insert(j, i);
    }

    cout << binaryTree1 << endl;
    binaryTree2 = binaryTree1;
    cout << binaryTree1 << endl;
    cout << binaryTree2 << endl;

    cout << binaryTree1.strLikeList();

    return 0;
}
