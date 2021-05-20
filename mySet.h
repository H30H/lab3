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
    myBinaryTree<char, T> elements;
public:
    class IsEmpty {};

    mySet() {
        elements = myBinaryTree<char, T>();
    }

    explicit mySet(T item) {
        elements = myBinaryTree<char, T>();
        elements.insert(0, item);
    }

    mySet(T* items, int count) {
        elements = myBinaryTree<char, T>();
        for (int i = 0; i < count; i++) {
            elements.insert(0, items[i]);
        }
    }

    mySet(const mySet<T>& set) {
        elements = set.elements;
    }

    void add(T element) {
        elements.insert(0, element);
    }

    void remove(T element) {
        try {
            elements.remove(element);
        }
        catch (typename myBinaryTree<char, T>::InvalidKeyword error) {
            return;
        }
    }

    int length() {
        auto *keys = elements.getKeys();
        int res = keys->length();
        delete keys;
        return res;
    }

    int find(T element) {
        try {
            elements.find(element);
            return 1;
        }
        catch (typename myBinaryTree<char, T>::InvalidKeyword error) {
            return 0;
        }
    }

    void map(T (*f)()) {
        auto *keys = elements.getKeys();
        elements.Delete();
        for (auto &i : *keys) {
            add(f());
        }
        delete keys;
    }

    void map(T (*f)(T elements)) {
        auto *keys = elements.getKeys();
        elements.Delete();
        for (auto &i : *keys) {
            add(f(i));
        }
        delete keys;
    }

    T reduce(T (*f)(T res, T value), T start) {
        auto *keys = elements.getKeys();

        T res = start;

        for (int i = 0; i < keys->length(); i++) {
            res = f (res, keys->get(0));
        }

        return res;
    }

    void join(const mySet<T>& set) {
        auto *keys = set.elements.getKeys();
        for (int i = 0; i < keys->length(); i++) {
            add(keys->get(i));
        }
        delete keys;
    }

    void cross(const mySet<T>& set) {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();
        mySet<T> res;

        int i = 0, j = 0;

        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(j);
            if (val1 == val2) {
                res.add(val1);
                i++;
                j++;
            }
            else if (val1 < val2)
                i++;
            else
                j++;
        }

        elements = res;

        delete keys1;
        delete keys2;
    }

    void sub(const mySet<T>& set) {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();

        mySet<T> res;

        int i = 0, j = 0;
        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(j);
            if (val1 == val2) {
                i++;
                j++;
            }
            else if (val1 > val2) {
                j++;
            }
            else {
                res.add(val1);
            }
        }

        elements = res.elements;

        for (i; i < keys1->length(); i++) {
            add(keys1->get(i));
        }

        delete keys1;
        delete keys2;
    }
};


#endif //LAB3_MYSET_H
