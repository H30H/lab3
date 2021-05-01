//
// Created by Grisha on 23.04.2021.
//

#ifndef LAB3_MYBINARYTREE_H
#define LAB3_MYBINARYTREE_H

#include "myStack.h"

#include <iostream>

template <class Data, class Key>
class myBinaryTree {
public:
    using K = Key;
    using T = Data;
    using typeHeight = long int;

    template<class T, class K>
    class branch {
    public:
        K key;
        T data;
        typeHeight height = 1;

        branch *left = nullptr;
        branch *right = nullptr;

        branch& operator = (branch br) {
            key = br.key;
            data = br.key;
            height = br.height;

            left = br.left;
            right = br.right;

            return *this;
        }

        typeHeight getDelta() {
            auto h1 = left == nullptr ? 0 : left->height;
            auto h2 = right == nullptr ? 0 : right->height;
            return h2 - h1;
        }

        void updateHeight() {
            auto h1 = left == nullptr ? 0 : left->height;
            auto h2 = right == nullptr ? 0 : right->height;
            height = (h1 > h2 ? h1 : h2) + 1;
        }

        branch* rotateLeft() {
            branch *res = right;
            right = res->left;
            res->left = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        branch* rotateRight() {
            branch *res = left;
            left = res->right;
            res->right = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        branch* balance() {
            updateHeight();
            auto delta = getDelta();
            if (delta < -1) {
                if (left != nullptr && left->getDelta() > 0)
                    left = left->rotateLeft();
                return rotateRight();
            }
            if (delta > 1) {
                if (right != nullptr && right->getDelta() < 0)
                    right = right->rotateRight();
                return rotateLeft();
            }
            return this;
        }
    };

    class InvalidKeyword{
    public:
        K key;
        explicit InvalidKeyword(K key): key(key) {}
    };

private:

    branch<T, K> *head;

public:
    myBinaryTree(): head(nullptr) {}

    myBinaryTree(branch<T, K> *element): head(element) {}

    void Delete() {
        if (head->left != nullptr) {
            myBinaryTree<T, K>(head->left).Delete();
        }
        if (head->right != nullptr) {
            myBinaryTree<T, K>(head->right).Delete();
        }
        delete head;
        head = nullptr;
    }

    myBinaryTree(K key, T data) {
        auto res = new branch<T, K>;
        res->key = key;
        res->data = data;
    }

    T find(K key) {
        if (head == nullptr) throw InvalidKeyword(key);

        if (head->key == key) return head->data;

        if (key < head->key)
            return myBinaryTree<T, K>(head->left);

        return myBinaryTree<T, K>(head->right);
    }

    myBinaryTree<T, K>* insert(T data, K key) {
        if (head == nullptr) {
            head = new branch<T, K>;
            head->data = data;
            head->key = key;
            return this;
        }

        if (key == head->key) {
            head->data = data;
            return this;
        }

        if (key < head->key) {
            head->left = myBinaryTree<T, K>(head->left).insert(data, key)->head;
        }
        else {
            head->right = myBinaryTree<T, K>(head->right).insert(data, key)->head;
        }

        int leftVal = head->left == nullptr ? 0 : head->left->height;
        int rightVal = head->right == nullptr ? 0 : head->right->height;
        int maxVal = rightVal > leftVal ? rightVal : leftVal;
        int delta = head->getDelta();

        if (delta <= 1 && delta >= -1) {
            head->height = maxVal + 1;
            return this;
        }
        /*
        if (delta < -1) {

            branch *headNew = head->left;
            branch *swapped = headNew->right;
            headNew->right = head;
            head->left = swapped;
            leftVal = head->left == nullptr ? 0 : head->left->height;
            head->height =(rightVal > leftVal ? rightVal : leftVal) + 1;
            head = headNew;

        }
        else {
            branch *headNew = head->right;
            branch *swapped = headNew->left;
            headNew->left = head;
            head->right = swapped;
            rightVal = head->right == nullptr ? 0 : head->right->height;
            head->height = (rightVal > leftVal ? rightVal : leftVal) + 1;
            head = headNew;
        }*/
        head = head->balance();

        return this;
    }

    myBinaryTree<T, K>* remove(K key) {
        if (head == nullptr) throw InvalidKeyword(key);

        if (key != head->key) {
            if (key < head->key)
                head->left = myBinaryTree<T, K>(head->left).remove(key)->head;
            else
                head->right = myBinaryTree<T, K>(head->right).remove(key)->head;
            head = head->balance();
            return this;
        }

        if (head->left == nullptr && head->right == nullptr) {
            delete head;
            head = nullptr;
            return this;
        }

        if (head->left == nullptr && head->right != nullptr) {
            branch<T, K> *res = head->right;
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right == nullptr) {
            branch<T, K> *res = head->left;
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right != nullptr) {
            auto h1 = head->left->height;
            auto h2 = head->right->height;
            if (h1 > h2) {  ///реализовать стек и выполнить удаление через
                myStack<branch<T, K>*> stack;
                branch<T, K> *br, *last = nullptr;
                for (br = head->left; br->right != nullptr; br = br->right) {
                    if (last != nullptr)
                        stack.add(last);
                    last = br;
                }

                if (last == nullptr) {
                    br->right = head->right;
                    delete head;
                    head = br->balance();
                    return this;
                }

                last->right = br->left;
                br->left = head->left->balance();
                br->right = head->right;
                delete head;
                head = br;
                branch<T, K> *thing = last;

                while (stack.length() != 0) {
                    thing = stack.get();
                    thing->right = last->balance();
                    last = thing;
                }

                head->left = thing->balance();
                head = head->balance();
            }
            else {
                branch<T, K> *br, *last = nullptr;
                myStack<branch<T, K>*> stack;
                for (br = head->right; br->left != nullptr; br = br->left) {
                    if (last != nullptr)
                        stack.add(last);
                    last = br;
                }

                if (last == nullptr) {
                    br->left = head->left;
                    delete head;
                    head = br->balance();
                    return this;
                }

                last->left = br->right;
                br->right = head->right->balance();
                br->left = head->left;
                delete head;
                head = br;

                branch<T, K>* thing = last;
                while(stack.length() != 0) {
                    thing = stack.get();
                    thing->left = last->balance();//192 195
                    last = thing;
                }

                head->right = thing->balance();
                head = head->balance();
            }

            return this;
        }

        return this;
    }

    void print() {
        if (head == nullptr) return;
        std::cout << '{';
        myBinaryTree<T, K>(head->left).print();

        std::cout << "}(" << head->data << ")[";

        myBinaryTree<T, K>(head->right).print();
        std::cout << ']';
    }

    void print(const std::string& str) {
        std::string res;
    }

    void printAll() {
        if (head == nullptr) return;

        myBinaryTree<T, K>(head->left).printAll();

        std::cout << head->key << ": " << head->data << ", " << head->height << '\n';

        myBinaryTree<T, K>(head->right).printAll();
    }

    void printAll2() {
        printAll2(0, 0);
    }

    void printAll2(int count, int pol) {
        for (int i = 0; i < count - (pol != 0) + count - 1; i++)
            std::cout << ' ';

        if (pol == 1)
            std::cout << "├-";
        else if (pol == 2)
            std::cout << "└-";

        if (head == nullptr) {
            std::cout << "nullptr\n";
            return;
        }
        std::cout << head->key << '\n';

        myBinaryTree<T, K>(head->left).printAll2(count + 1, 1);
        myBinaryTree<T, K>(head->right).printAll2(count + 1, 2);
    }
};


#endif //LAB3_MYBINARYTREE_H
