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

    explicit mySet(const mySet<T> *set) {
        elements = set->elements;
    }

    ~mySet() {
        elements.Delete();
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

    int length() const {
        auto *keys = elements.getKeys();
        int res = keys->length();
        delete keys;
        return res;
    }

    int find(T element) const {
        try {
            elements.find(element);
            return 1;
        }
        catch (typename myBinaryTree<char, T>::InvalidKeyword error) {
            return 0;
        }
    }

    int find(const mySet<T>& set) const {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();
        int count = 0;

        int i = 0, j = 0;
        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(i);
            if (val1 == val2) {
                i++;
                j++;
                count++;
            }
            else if (val1 < val2) {
                i++;
            }
            else {
                j++;
            }
        }

        count = count == keys2->length();

        delete keys1;
        delete keys2;

        return count;
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

    T reduce(T (*f)(T res, T value), T start) const {
        auto *keys = elements.getKeys();

        T res = start;

        for (int i = 0; i < keys->length(); i++) {
            res = f (res, keys->get(0));
        }

        delete keys;
        return res;
    }

    std::string getStr() const {
        return std::string("{") + elements.getStr("LK, R", "K") + std::string("\b\b}");
    }

    mySet<T> join(const mySet<T>& set) {
        auto *keys = set.elements.getKeys();
        for (int i = 0; i < keys->length(); i++) {
            add(keys->get(i));
        }
        delete keys;
        return *this;
    }

    mySet<T> cross(const mySet<T>& set) {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();
        mySet<T> res;

        int i = 0, j = 0;
        elements.Delete();

        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(j);
            if (val1 == val2) {
                add(val1);
                i++;
                j++;
            }
            else if (val1 < val2) {
                i++;
            }
            else {
                j++;
            }
        }

        delete keys1;
        delete keys2;

        return *this;
    }

    mySet<T> sub(const mySet<T>& set) {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();

        int i = 0, j = 0;
        elements.Delete();

        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(j);
            if (val1 == val2) {
                i++;
                j++;
            }
            else if (val1 < val2) {
                add(val1);
                i++;
            }
            else {
                j++;
            }
        }

        for (i; i < keys1->length(); i++) {
            add(keys1->get(i));
        }

        delete keys1;
        delete keys2;

        return *this;
    }

    mySet<T> Xor(const mySet<T> &set) {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();

        int i = 0, j = 0;
        elements.Delete();

        while (i < keys1->length() && j < keys2->length()) {
            T val1 = keys1->get(i);
            T val2 = keys2->get(j);

            if (val1 == val2) {
                i++;
                j++;
            }
            else if (val1 < val2) {
                add(val1);
                i++;
            }
            else {
                add(val2);
                j++;
            }
        }

        for (i; i < keys1->length(); i++)
            add(keys1->get(i));

        for (j; j < keys2->length(); j++)
            add(keys2->get(j));

        delete keys1;
        delete keys2;

        return *this;
    }

    mySet<T>& operator = (const mySet<T>& set) {
        elements = set.elements;
        return *this;
    }

    mySet<T> operator & (const mySet<T> &set) const {
        return mySet<T>(this).cross(set);
    }

    mySet<T> operator * (const mySet<T> &set) const {
        return mySet<T>(this).cross(set);
    }

    mySet<T> operator | (const mySet<T> &set) const {
        return mySet<T>(this).join(set);
    }

    mySet<T> operator + (const mySet<T> &set) const {
        return mySet<T>(this).join(set);
    }

    mySet<T> operator / (const mySet<T> &set) const {
        return mySet<T>(this).sub(set);
    }

    mySet<T> operator - (const mySet<T> &set) const {
        return mySet<T>(this).sub(set);
    }

    mySet<T> operator xor (const mySet<T> &set) const {
        return mySet<T>(this).Xor(set);
    }

    int operator == (const mySet<T> &set) const {
        auto *keys1 = elements.getKeys();
        auto *keys2 = set.elements.getKeys();

        int res = 1;

        if (keys1->length() != keys2->length()) {
            res = 0;
        }

        for (int i = 0; i < keys1->length() && res != 0; i++) {
            if (keys1->get(i) != keys2->get(i)) {
                res = 0;
            }
        }

        delete keys1;
        delete keys2;
        return res;
    }

    int operator != (const mySet<T> &set) const {
        return !(*this == set);
    }

    int operator <  (const mySet<T> &set) const {
        return *this != set && set.find(*this);
    }

    int operator <= (const mySet<T> &set) const {
        return set.find(*this);
    }

    int operator >  (const mySet<T> &set) const {
        return *this != set && find(set);
    }

    int operator >= (const mySet<T> &set) const {
        return find(set);
    }
};

template<class T>
std::ostream &operator << (std::ostream &cout, const mySet<T> &set) {
    return cout << set.getStr();
}

#endif //LAB3_MYSET_H
