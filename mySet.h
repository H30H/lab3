//
// Created by Grisha on 17.05.2021.
//

#ifndef LAB3_MYSET_H
#define LAB3_MYSET_H

#include "myBinaryTree.h"
#include "myArraySequence.h"

template <class T>
class mySet {
private:
    myBinaryTree<char, T> data;
public:
    mySet() {
        data = myBinaryTree<char, T>();
    }

    explicit mySet(T item) {
        data = myBinaryTree<char, T>();
        data.insert(0, item);
    }

    mySet(T* items, int count) {
        data = myBinaryTree<char, T>();
        for (int i = 0; i < count; i++) {
            data.insert(0, items[i]);
        }
    }

    mySet(const mySet<T>& set) {
        data.Delete();
        data = set.data;
    }

    void add(T element) {
        data.insert(0, element);
    }

    void remove(T element) {
        try {
            data.remove(element);
        }
        catch (typename myBinaryTree<char, T>::InvalidKeyword error) {
            return;
        }
    }

    int find(T element) {
        try {
            data.find(element);
            return 1;
        }
        catch (typename myBinaryTree<char, T>::InvalidKeyword error) {
            return 0;
        }
    }


};


#endif //LAB3_MYSET_H
