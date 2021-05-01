#include "myBinaryTree.h"

#include <iostream>

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
        tree.printAll2();
        cout << endl;
    }

    return 0;
}
