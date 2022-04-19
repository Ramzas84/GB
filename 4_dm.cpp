#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
#include <fstream>
#include "time.h"

using namespace std;

// 1. Имеется отсортированный массив целых чисел. Необходимо разработать функцию
// insert_sorted, которая принимает вектор и новое число и вставляет новое число в
// определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
// Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым
// контейнером, содержащим любой тип значения.

template <typename T>
void insert_sorted (vector<T>& a, T insert){
    a.push_back(a[a.size() - 1]);
    auto it = upper_bound(a.begin(), a.end(), insert);
    if (it == a.end()){
        a[a.size() - 1] = insert;
        return;
    }
    copy(it, a.end(), it + 1);
    *it = insert;
}

// 3. Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:
// ○ count_if и find
// ○ count_if и цикл for
// ○ цикл for и find
// ○ 2 цикла for

string vowels = "aeiouyAEIOUY";

int count_ifAndFinde(fstream& fs){
    Timer T1("Count_if And Finde");
    int count = 0;
    string word;
    while(fs >> word){
        count += count_if(word.begin(), word.end(), [](char ch){if (vowels.find(ch) != std::string::npos) 
                                                    return true;});
    }
    cout << count << " vowels!\n";
    T1.print();
    return count;
}

int count_ifAndFor(fstream& fs){
    Timer T2("Count_if And For");
    int count = 0;
    string word;
    while(fs >> word){
        count += count_if(word.begin(), word.end(), [](char ch){for (char i : vowels){
                                                    if (ch == i)return true;}});
    }
    cout << count << " vowels!\n";
    T2.print();
    return count;
}

int forAndFind(fstream& fs){
    Timer T3("For And Find");
    int count = 0;
    string word;
    while(fs >> word){
        for (char ch : word){
            if (vowels.find(ch) != std::string::npos) ++count;
        }
    }
    cout << count << " vowels!\n";
    T3.print();
    return count;
}

int forAndFor(fstream& fs){
    Timer T4("For And For");
    int count = 0;
    string word;
    while(fs >> word){
        for (char ch : word){
            for (char i : vowels){
                if (i == ch) ++count;
            }
        }
    }
    cout << count << " vowels!\n";
    T4.print();
    return count;
}
int main(){
    int size = 40;
    vector<int> vec(size);
    generate(vec.begin(), vec.end(), [](){return rand() % 100;});
    for_each(vec.begin(), vec.end(), [](const int& a){cout << a << ' ';});
    printf("\n");
    sort(vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), [](const int& a){cout << a << ' ';});
    printf("\n");
    insert_sorted (vec, 86);
    for_each(vec.begin(), vec.end(), [](const int& a){cout << a << ' ';});
    printf("\n");
    
// 2. Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой
// значения аналогового сигнала. На основе этого массива чисел создайте другой вектор целых
// чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
// Выведите получившиеся массивы чисел. Посчитайте ошибку, которой обладает цифровой
// сигнал по сравнению с аналоговым по формуле:
    printf("---------Tusk 2---------\n");
    printf("---------Vector A---------\n");

    int sz = 100;
    vector<float> a (sz);
    generate(a.begin(), a.end(), [](){return rand() % 10000/100.00;});
    for_each(a.begin(), a.end(), [](const float& i){cout << i << ' ';});
    printf("\n---------Vector B---------\n");

    vector<int> b (sz);
    copy(a.begin(), a.end(), b.begin());
    for_each(b.begin(), b.end(), [](const float& i){cout << i << ' ';});
    std::vector<float>c;
    transform(a.begin(), a.end(), b.begin(), back_inserter(c), [](float a1, int b1){
        return pow(a1 - b1, 2);
    });
    printf("\n---------Vector C---------\n");
    for_each(c.begin(), c.end(), [](const float& i){cout << i << ' ';});
    float sum = accumulate(c.begin(), c.end(), 0.0);
    cout << endl << "mistake = " << sum;
    
    printf("\n---------Tusk 3 (Old homework)---------\n");
    fstream f("text.txt");
    count_ifAndFinde(f);
    
    fstream f2("text.txt");
    count_ifAndFor(f2);
    
    fstream f3("text.txt");
    forAndFind(f3);
    
    fstream f4("text.txt");
    forAndFor(f4);
    
    return 0;
}
