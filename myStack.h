//
// Created by Grisha on 30.04.2021.
//

#ifndef LAB3_MYSTACK_H
#define LAB3_MYSTACK_H

#include "myLinkedList.cpp"

template<class T>
class myStack {
private:
    myLinkedList<T> elements;
public:
    class IndexOutOfRange: public myLinkedList<T>::IndexOutOfRange {

    };

    myStack() = default;

    explicit myStack(T element): elements(myLinkedList<T>(element)) {}

    explicit myStack(myLinkedList<T> *list): elements(*list) {}

    void add(T element) {
        elements.prepend(element);
    }

    T get() {
        if (elements.length() == 0)
            throw IndexOutOfRange();

        return elements.pop(0);
    }

    int length() {
        return elements.length();
    }
};


#endif //LAB3_MYSTACK_H
