//
// Created by Grisha on 23.04.2021.
//

#ifndef LAB3_MYBINARYTREE_H
#define LAB3_MYBINARYTREE_H

#include "myStack.h"
#include "myQueue.h"
#include "myArraySequence.h"

#include <iostream>

template <class Key, class Data>
class myBinaryTree {
public:
    using K = Key;
    using T = Data;
    using typeHeight = long int;

    template<class K, class T>
    class Node {
    public:
        K key;
        T data;
        typeHeight height = 1;

        Node *left = nullptr;
        Node *right = nullptr;

        Node(K key1, T data1): key(key1), data(data1) {}

        Node& operator = (const Node& br) {
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

        Node* rotateLeft() {
            Node *res = right;
            right = res->left;
            res->left = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        Node* rotateRight() {
            Node *res = left;
            left = res->right;
            res->right = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        Node* balance() {
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

    class IsEmpty{

    };

    template<class K, class T>
    class myIterator {
    private:
        myBinaryTree<K, T> *binaryTree = nullptr;
        myStack<Node<K, T>*> *stack = nullptr;
        Node<K, T> *now = nullptr;
    public:
        myIterator(): stack(new myStack<Node<K, T>*>) {}

        myIterator(myBinaryTree<K, T> *tree) {
            binaryTree = tree;
            stack = new myStack<Node<K, T>*>;
        }

        myIterator(myBinaryTree<K, T> *tree, myStack<Node<K, T>*>* Stack, Node<K, T> *elem) {
            binaryTree = tree;
            stack = new myStack<Node<K, T>*>(Stack);
            now = elem;
        }

        myIterator(const myIterator<K, T>& iter) {
            binaryTree = iter.binaryTree;
            stack = new myStack<Node<K, T>*>(iter.stack);
            now = iter.now;
        }

        ~myIterator() {
            if (stack)
                delete stack;
        }


        myIterator<K, T>& begin() {
            now = binaryTree->head;
            if (now == nullptr)
                return *this;

            stack->add(nullptr);

            while(now->left != nullptr) {
                stack->add(now);
                now = now->left;
            }
            return *this;
        }

        myIterator<K, T> end() {
            return myIterator<K, T>(binaryTree, new myStack<Node<K, T>*>, nullptr);
        }

        myIterator<K, T>& operator++() {
            if (now == nullptr)
                return *this;

            if (now->right != nullptr) {
                now = now->right;
                while (now->left != nullptr) {
                    stack->add(now);
                    now = now->left;
                }
            }
            else {
                now = stack->get();
            }

            return *this;
        }

        int operator == (myIterator<K, T>& iter) {
            return binaryTree->operator==(*iter.binaryTree) &&
                   now == iter.now &&
                   stack->length() == iter.stack->length();
        }

        int operator != (myIterator<K, T>& iter) {
            return !(operator==(iter));
        }

        T& operator *() {
            return now->data;
        }
    };
    /**/
private:
    Node<K, T> *head;
    short int _isCopy_ = 0;

    ///Функции для работы преобразования в строку

    std::string strFromQueue(int* queue, int num, const std::string &Start, const std::string &First,
                             const std::string &Second, const std::string &End, const std::string &typePrint) const {
        int ind1 = 0, ind2 = 0;
        switch (queue[num]) {
            default: return std::string();
            case 0:
                return myBinaryTree<K, T>(head->left).strSplited(queue, Start, First, Second, End, typePrint);

            case 1:
                ind1 = (int) typePrint.find('K');
                ind2 = (int) typePrint.find('D');

                if (ind1 > typePrint.length() && ind2 > typePrint.length())
                    return std::string();

                if (ind1 > typePrint.length())
                    return std::to_string(head->data);

                if (ind2 > typePrint.length())
                    return std::to_string(head->key);

                if (ind1 <= typePrint.length() && ind2 <= typePrint.length())
                    return std::string("\"") + std::to_string(head->key) + ", " + std::to_string(head->data) + "\"";

            case 2:
                return myBinaryTree<K, T>(head->right).strSplited(queue, Start, First, Second, End, typePrint);
        }
        return std::string();
    }

    std::string strSplited(int* queue, const std::string &Start, const std::string &First,
                           const std::string &Second, const std::string &End, const std::string &typePrint) const {
        if (head == nullptr) {
            return std::string();
        }

        std::string res = Start;
        res += strFromQueue(queue, 0, Start, First, Second, End, typePrint);
        res += First;
        res += strFromQueue(queue, 1, Start, First, Second, End, typePrint);
        res += Second;
        res += strFromQueue(queue, 2, Start, First, Second, End, typePrint);
        res += End;

        return res;
    }

    void strGetKeys(const std::string &str, int* queue, int* key, std::string* keys,
                    std::string &Start, std::string &First, std::string &Second, std::string &End) const {
        key[0] = (int) str.find(keys[0]);
        key[1] = (int) str.find(keys[1]);
        key[2] = (int) str.find(keys[2]);

        if (key[0] > str.length() || key[1] > str.length() || key[2] > str.length())
            return;

        if (key[0] < key[1] && key[1] < key[2]) {
            queue[0] = 0; queue[1] = 1; queue[2] = 2;
        }
        else if (key[0] < key[2] && key[2] < key[1]) {
            queue[0] = 0; queue[1] = 2; queue[2] = 1;
            int swap = key[1]; key[1] = key[2]; key[2] = swap;
        }
        else if (key[1] < key[0] && key[0] < key[2]) {
            queue[0] = 1; queue[1] = 0; queue[2] = 2;
            int swap = key[0]; key[0] = key[1]; key[1] = swap;
        }
        else if (key[1] < key[2] && key[2] < key[0]) {
            queue[0] = 1; queue[1] = 2; queue[2] = 0;
            int swap = key[0]; key[0] = key[1]; key[1] = key[2]; key[2] = swap;
        }
        else if (key[2] < key[0] && key[0] < key[1]) {
            queue[0] = 2; queue[1] = 0; queue[2] = 1;
            int swap = key[0]; key[0] = key[2]; key[2] = key[1]; key[1] = swap;
        }
        else if (key[2] < key[1] && key[1] < key[0]){
            queue[0] = 2; queue[1] = 1; queue[2] = 0;
            int swap = key[0]; key[0] = key[2]; key[2] = swap;
        }

        Start  = str.substr(0, key[0]);
        First  = str.substr(key[0] + keys[queue[0]].length(), key[1] - key[0] - keys[queue[0]].length());
        Second = str.substr(key[1] + keys[queue[1]].length(), key[2] - key[1] - keys[queue[1]].length());
        End    = str.substr(key[2] + keys[queue[2]].length(), str.length() - key[2] - keys[queue[2]].length());
    }

    ///Функции для работы получение ключей и значений в дереве

    myArraySequence<T>* getValues(Node<K, T>* node) const {
        if (!node) {
            return new myArraySequence<T>;
        }

        myArraySequence<T>* res1 = getValues(node->left);
        myArraySequence<T>* res2 = getValues(node->right);

        res1->append(node->data);
        res1->concat(res2);

        delete res2;
        return res1;
    }

    myArraySequence<K>* getKeys(Node<K, T>* node) const {
        if (!node) {
            return new myArraySequence<K>;
        }

        myArraySequence<K>* res1 = getKeys(node->left);
        myArraySequence<K>* res2 = getKeys(node->right);

        res1->append(node->key);
        res1->concat(res2);

        delete res2;
        return res1;
    }

    ///Функция для поиска поддерева

    int isSubTree(Node<K, T> *tree, Node<K, T> *subTree) {
        if (tree == subTree)
            return 1;

        if (subTree == nullptr)
            return 1;

        if (tree == nullptr)
            return 0;

        if (tree->key != subTree->key || tree->data != subTree->data)
            return 0;

        if (!isSubTree(tree->left, subTree->left))
            return 0;

        if (!isSubTree(tree->right, subTree->right))
            return 0;

        return 1;
    }

public:
    myBinaryTree(): head(nullptr) {}

    explicit myBinaryTree(Node<K, T> *element): head(element), _isCopy_(1) {}

    void Delete() {
        if (head == nullptr)
            return;

        if (head->left != nullptr) {
            myBinaryTree<K, T>(head->left).Delete();
        }
        if (head->right != nullptr) {
            myBinaryTree<K, T>(head->right).Delete();
        }
        delete head;
        head = nullptr;
    }

    myBinaryTree(const K& key, const T& data) {
        auto *res = new Node<K, T>;
        res->key = key;
        res->data = data;
        head = res;
    }

    myBinaryTree(const myArraySequence<K>& keys, const myArraySequence<T>& elements) {
        auto len1 = keys.length(), len2 = elements.length();
        head = nullptr;
        auto min = len1 > len2 ? len2 : len1;

        for (int i = 0; i < min; i++) {
            K key = keys.get(i);
            T element = elements.get(i);
            insert(key, element);
        }
    }
    

    ~myBinaryTree() {
        if (!_isCopy_)
            Delete();
    }


    T find(K key) const {
        if (head == nullptr) throw InvalidKeyword(key);

        if (head->key == key) return head->data;

        if (key < head->key)
            return myBinaryTree<K, T>(head->left).find(key);

        return myBinaryTree<K, T>(head->right).find(key);
    }

    myBinaryTree<K, T>* insert(K key, T data) {
        if (head == nullptr) {
            head = new Node<K, T>(key, data);
            return this;
        }

        if (key == head->key) {
            head->data = data;
            return this;
        }

        if (key < head->key) {
            head->left = myBinaryTree<K, T>(head->left).insert(key, data)->head;
        }
        else {
            head->right = myBinaryTree<K, T>(head->right).insert(key, data)->head;
        }

//        int leftVal = head->left == nullptr ? 0 : head->left->height;
//        int rightVal = head->right == nullptr ? 0 : head->right->height;
//        int maxVal = rightVal > leftVal ? rightVal : leftVal;
        head->updateHeight();
        int delta = head->getDelta();

        if (delta <= 1 && delta >= -1) {
//            head->height = maxVal + 1;
            return this;
        }
        head = head->balance();

        return this;
    }

    myBinaryTree<K, T>* remove(K key) {
        if (head == nullptr) throw InvalidKeyword(key);

        if (key != head->key) {
            if (key < head->key)
                head->left = myBinaryTree<K, T>(head->left).remove(key)->head;
            else
                head->right = myBinaryTree<K, T>(head->right).remove(key)->head;
            head = head->balance();
            return this;
        }

        if (head->left == nullptr && head->right == nullptr) {
            delete head;
            head = nullptr;
            return this;
        }

        if (head->left == nullptr && head->right != nullptr) {
            Node<K, T> *res = head->right;
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right == nullptr) {
            Node<K, T> *res = head->left;
            delete head;
            head = res;
            return this;
        }

        if (head->left != nullptr && head->right != nullptr) {
            auto h1 = head->left->height;
            auto h2 = head->right->height;
            if (h1 > h2) {
                myStack<Node<K, T>*> stack;
                Node<K, T> *br, *last = nullptr;
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
                Node<K, T> *thing = last;

                while (stack.length() != 0) {
                    thing = stack.get();
                    thing->right = last->balance();
                    last = thing;
                }

                head->left = thing->balance();
                head = head->balance();
            }
            else {
                Node<K, T> *br, *last = nullptr;
                myStack<Node<K, T>*> stack;
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

                Node<K, T>* thing = last;
                while(stack.length() != 0) {
                    thing = stack.get();
                    thing->left = last->balance();
                    last = thing;
                }

                head->right = thing->balance();
                head = head->balance();
            }

            return this;
        }

        return this;
    }

    std::string getStr(const std::string& str) const {
        std::string typePrint("KD");
        return getStr(str, typePrint);
    }

    std::string getStr(const std::string& str, const std::string& typePrint) const {
        int queue[] = {-1, -1, -1};
        int key[3];
        int val = str.length() + 1;
        for (auto &i : key) {
            i = val;
        }
        std::string Start, First, Second, End;

        std::string keys[] = {std::string("L"), std::string("K"), std::string("R")};

        strGetKeys(str, queue, key, keys, Start, First, Second, End);

        return strSplited(queue, Start, First, Second, End, typePrint);
    }

    std::string strLikeList() {
        return strLikeList(0, 0);
    }

    std::string strLikeList(int count, int pol) {
        std::string res;
        for (int i = 0; i < count - (pol != 0) + count - 1; i++)
            res += ' ';

        if (pol == 1)
            res += "├-";
        else if (pol == 2)
            res += "└-";

        if (head == nullptr) {
            res += "nullptr\n";
            return res;
        }
        res += std::to_string(head->key) + '\n';

        res += myBinaryTree<K, T>(head->left).strLikeList(count + 1, 1);
        res += myBinaryTree<K, T>(head->right).strLikeList(count + 1, 2);
        return res;
    }

    myBinaryTree<K, T>& operator = (const myBinaryTree<K, T>& binaryTree) {
        Delete();
        //toOperatorEqual(binaryTree.head);
        if (binaryTree.head == nullptr)
            return *this;

        myQueue<Node<K, T>*> queue(binaryTree.head);

        while(queue.length() != 0) {
            auto *nodeRes = queue.get();
            insert(nodeRes->key, nodeRes->data);
            if (nodeRes->left != nullptr)
                queue.add(nodeRes->left);

            if (nodeRes->right != nullptr)
                queue.add(nodeRes->right);
        }

        return *this;
    }

    int equal(const myBinaryTree<K, T>& binaryTree) {
        if (head == binaryTree.head)
            return 1;

        if (head == nullptr || binaryTree.head == nullptr)
            return 0;

        if (head->key != binaryTree.head->key || head->data != binaryTree.head->data)
            return 0;

        if (!(myBinaryTree<K, T>(head->left).equal(myBinaryTree<K, T>(binaryTree.head->left))))
            return 0;

        if (!(myBinaryTree<K, T>(head->right).equal(myBinaryTree<K, T>(binaryTree.head->right))))
            return 0;

        return 1;
    }

    int operator == (const myBinaryTree<K, T>& binaryTree) {
        return equal(binaryTree);
    }

    int operator != (const myBinaryTree<K, T>& binaryTree) {
        return !equal(binaryTree);
    }

    T& operator [] (K key) {
        if (head == nullptr) throw InvalidKeyword(key);

        if (head->key == key) return head->data;

        if (key < head->key)
            return myBinaryTree<K, T>(head->left)[key];

        return myBinaryTree<K, T>(head->right)[key];
    }

    myArraySequence<T>* getValues() const {
        return getValues(head);
    }

    myArraySequence<K>* getKeys() const {
        return getKeys(head);
    }

    void map(T (*f)()) {
        if (!head)
            return;

        head->data = f();
        myBinaryTree<K, T>(head->left).map(f);
        myBinaryTree<K, T>(head->right).map(f);
    }

    void map(T (*f)(T value)) {
        if (!head)
            return;

        head->data = f(head->data);
        myBinaryTree<K, T>(head->left).map(f);
        myBinaryTree<K, T>(head->right).map(f);
    }

    T reduce(T (*f)(T res, T value), T start) {
        if (!head)
            return start;

        T res = start;

        auto *data = getValues();

        for (int i = 0; i < data->length(); i++) {
            res = f(res, data->get(i));
        }

        return res;
    }

    myBinaryTree<K, T>* getSubTree(K key) {
        if (head == nullptr)
            return new myBinaryTree<K, T>;

        if (head->key == key) {
            auto *res = new myBinaryTree<K, T>;
            *res = myBinaryTree<K, T>(head);
            return res;
        }

        if (head->key < key)
            return myBinaryTree<K, T>(head->right).getSubTree(key);
        else
            return myBinaryTree<K, T>(head->left).getSubTree(key);
    }

    int inTree(K key) {
        auto* arr = getKeys();
        int k = arr->find(key);
        delete arr;
        return k != -1;
    }

    int inTree(const myBinaryTree<K, T>& binaryTree) {
        if (binaryTree.head == nullptr)
            return 1;

        if (head == binaryTree.head)
            return 1;

        if (head == nullptr)
            return 0;

        if (head->key == binaryTree.head->key) {
            return isSubTree(head, binaryTree.head);
        }

        if (binaryTree.head->key < head->key) {
            return myBinaryTree<K, T>(head->left).inTree(binaryTree);
        }
        else {
            return myBinaryTree<K, T>(head->right).inTree(binaryTree);
        }
    }

    myBinaryTree<K, T>& getLink() {
        return *this;
    }
};

template <class K, class T>
std::ostream& operator << (std::ostream& cout, const myBinaryTree<K, T> &binaryTree) {
    std::string format("{L}[K](R)");
    return std::cout << binaryTree.getStr(format, std::string("K"));
}

#endif //LAB3_MYBINARYTREE_H
