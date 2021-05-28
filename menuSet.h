//
// Created by Grisha on 12.04.2021.
//

#ifndef LAB2_MENU_H
#define LAB2_MENU_H

#include <complex>
#include <iostream>
#include "tests/test.h"
#include "Headers/mySet.h"

void mainMenu();
int getType();

//1
void readSet(myArraySequence<mySet<int>*> *intArr,
                    myArraySequence<mySet<float>*> *floatArr);

template<class T>
void readTypeSet(myArraySequence<mySet<T>*> *arr, int count);

template<class T>
void generateRandomSet(myArraySequence<mySet<T>*> *arr, int count, T (*func)());

//2
void operationWithSet(myArraySequence<mySet<int>*> *intArr,
                             myArraySequence<mySet<float>*> *floatArr);

template<class T>
void operationTypeWithSet(myArraySequence<mySet<T>*> *arr);

//3
void printSet(myArraySequence<mySet<int>*> *intArr,
                     myArraySequence<mySet<float>*> *floatArr);

template<class T>
void printTypeSet(myArraySequence<mySet<T>*> *arr);


//4
void deleteSet(myArraySequence<mySet<int>*> *intArr,
                      myArraySequence<mySet<float>*> *floatArr);

template<class T>
void deleteTypeSet(myArraySequence<mySet<T>*> *arr);

//5
void testFunc();

#endif //LAB2_MENU_H
