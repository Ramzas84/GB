#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// 1.Создать шаблонную функцию, которая принимает итераторы на начало и конец
// последовательности слов, и выводящую в консоль список уникальных слов (если слово
// повторяется больше 1 раза, то вывести его надо один раз). Продемонстрировать работу
// функции, передав итераторы различных типов.

template <typename IT>
void uniqWords(IT begin, IT end){
    unordered_set<string> uniqWord;
    while(begin != end){
        uniqWord.insert(*begin);
        ++begin;
    }
    for_each(uniqWord.begin(), uniqWord.end(), [](const auto a){cout << a << ' ';});
    cout << endl;
}

// 2.Используя ассоциативный контейнер, напишите программу, которая будет считывать данные
// введенные пользователем из стандартного потока ввода и разбивать их на предложения.
// Далее программа должна вывести пользователю все предложения, а также количество слов в
// них, отсортировав предложения по количеству слов.
void task2 (){
    string EX = "!?.";
    cout << "Inter something centans:" << endl;
    string text;
    getline(cin, text);
    string temp;
    int count = 0;
    multimap <int, string> res;
    for (int i = 0; i < text.size(); ++i){
        temp += text[i];
        if (EX.find(text[i]) != string::npos){
            if (((i + 1) < text.size()) && !(EX.find(text[i + 1]) != string::npos)){
                res.insert({++count, temp});
                temp = "";
                count = -1;
            }
        }
        if ((text[i] == ' ') && ((i + 1) < text.size()) && (text[i + 1] != '-')) ++count;
    }
    for_each(res.begin(), res.end(), [](const auto a){cout << a.second << ' ' << a.first << "words." << endl;});
    cout << endl;
}

int main(){
    vector<string> s1 {"Cat", "Car", "Cat", "Moon"};
    deque<string> s2{"Cat", "Car", "Cat", "Moon"};
    uniqWords(s1.begin(), s1.end());
    uniqWords(s2.begin(), s2.end());
    
    task2();

    return 0;
}
