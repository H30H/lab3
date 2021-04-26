#include "myBinaryTree.h"

#include <iostream>

using namespace std;
int main() {
    int key, data;
    myBinaryTree<int, int> tree;
    while(true) {
        cin >> key >> data;
        if (key == -1 && data == -1)
            break;

        tree.insert(data, key);
        tree.print();
        cout << endl;
    }

    return 0;
}
