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
        c = (*str1)[i];
    }
}

using namespace std;
int main() {
    int key, data;
    myBinaryTree<int, int> tree;
    while(true) {
        int n;
        cin >> n;
        cin >> key >> data;
        if (key == -1 && data == -1)
            break;
        if (n == 1)
            tree.insert(data, key);
        else
            tree.remove(key);
        //tree.printAll2();
        cout << tree.getStr(string("LK, R"), string("K")) << endl;
        cout << tree.getKeys() << endl;
    }


    return 0;
}
