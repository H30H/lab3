#include "Headers/myBinaryTree.h"
#include "Headers/mySet.h"
#include "tests/test.h"

#include <iostream>
#include <ctime>
#include "menuSet.h"

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

    myBinaryTree<int, int> binaryTree;
    for (int i = 0; i <= 200; i+=2) {
        binaryTree.insert(i, i);
    }

    int n = 0;
    for (auto &i : binaryTree) {
        cout << i << '\n';
        n++;
    }
    cout << endl;

    mainMenu();
    return 0;
}