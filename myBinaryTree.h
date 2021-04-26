//
// Created by Grisha on 23.04.2021.
//

#ifndef LAB3_MYBINARYTREE_H
#define LAB3_MYBINARYTREE_H

#include <iostream>

template <class Data, class Key>
class myBinaryTree {
public:
    using K = Key;
    using T = Data;
    using typeHeight = unsigned long int;

    class branch {
    public:
        K key;
        T data;
        typeHeight height = 1;
        int delta = 0;

        branch *left = nullptr;
        branch *right = nullptr;
    };

    class InvalidKeyword{
        K key;
        explicit InvalidKeyword(K key): key(key) {}
    };

private:

    branch *head;

public:
    myBinaryTree(): head(nullptr) {}

    myBinaryTree(branch *element): head(element) {}

    ~myBinaryTree() {

    }

    void Delete() {
        if (head->left != nullptr) {
            myBinaryTree<T, K>(head->left).Delete();
        }
        if (head->right != nullptr) {
            myBinaryTree<T, K>(head->right).Delete();
        }
        free(head);
    }

    myBinaryTree(K key, T data) {
        auto res = new branch;
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

    branch *insert(T data, K key) {
        if (head == nullptr) {
            head = new branch;
            head->data = data;
            head->key = key;
            return head;
        }

        if (key == head->key) {
            head->data = data;
            return head;
        }

        if (key < head->key) {
            head->left = myBinaryTree<T, K>(head->left).insert(data, key);
        }
        else {
            head->right = myBinaryTree<T, K>(head->right).insert(data, key);
        }

        int leftVal = head->left == nullptr ? 0 : head->left->height;
        int rightVal = head->right == nullptr ? 0 : head->right->height;
        int maxVal = rightVal > leftVal ? rightVal : leftVal;
        int delta = rightVal - leftVal;

        if (delta <= 1 && delta >= -1) {
            head->height = maxVal + 1;
            return head;
        }

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
        }

        return head;
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
};


#endif //LAB3_MYBINARYTREE_H
