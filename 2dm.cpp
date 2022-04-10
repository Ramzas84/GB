#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "time.h"

using namespace std;

// 1. Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, 
// на которые указывают эти указатели (нужно обменивать именно сами указатели, переменные должны 
// оставаться в тех же адресах памяти).

template<typename T>
void Swap(T*& a, T*& b){
    T* c = a;
    a = b;
    b = c;
}

// 2. Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует 
// указатели по значениям, на которые они указывают.
template<typename T>
void SortPointers (vector<T*>& a){
    sort (a.begin(), a.end(),
            [](T* b, T* c) {return *b < *c;});
}

template<typename T>
void printVec(vector<T>& a){
    for (T& rec : a){
        cout << rec << ' ';
    }
    cout << endl;
}

// 3. Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:
// ○ count_if и find
// ○ count_if и цикл for
// ○ цикл for и find
// ○ 2 цикла for
// Замерьте время каждого способа подсчета и сделайте выводы.
// Справка:
// count_if - это алгоритмическая функция из STL, которая принимает 3 параметра: итератор на начало, 
// итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
// find - это метод класса string, который возвращает позицию символа (строки), переданного в качестве 
// параметра, в исходной строке. Если символ не найден, то метод возвращает string::npos.

//примерно понимаю как должна выглядеть программа, но вообще ничего не знаю про count_if и find и пока не 
//получается в них разобраться. Если на ближайших пару лекциях этому не научат, постараюсь еще разобраться сам 
//и тогда сдам задачу, если еще будут принимать.

int main(){
    Timer t1 ("tmr1");
    int size = 40;
    vector<int> a(size);
    vector<int*> aLn(size);
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        aLn[i] = &a[i];
    }
    printVec(a);
    //printVec(aLn);
    for (auto rec : aLn){
        cout << *rec <<' ';
    }
    cout << endl;
    
    SortPointers(aLn);
    
    for (auto rec : aLn){
        cout << *rec <<' ';
    }
    cout << endl;
    //sort(a.begin(), a.end());
    //printVec(a);
    //SortPointers(vec);
    t1.print();
    
    return 0;
}
