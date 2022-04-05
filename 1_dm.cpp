#include <iostream>
#include <fstream>
#include <string>
#include <tuple>


using namespace std;

// Создайте структуру Person с 3 полями: фамилия, имя, отчество. Поле отчество должно быть
// опционального типа, т.к. не у всех людей есть отчество. Перегрузите оператор вывода данных
// для этой структуры. Также перегрузите операторы < и == (используйте tie).

struct Person{
    string name, lastname, fathername;
    Person(string ln, string n) : name(n), lastname(ln), fathername("-") {}
    Person(string ln, string n, string fn) : 
        name(n), lastname(ln), fathername(fn) {}
    friend bool operator<(const Person& p1, const Person& p2);
    friend bool operator==(const Person& p1, const Person& p2);
    friend ostream& operator<<(ostream& out, const Person& p1);
};

bool operator<(const Person& p1, const Person& p2){
        return tie(p1.name, p1.lastname, p1.fathername) < tie(p2.name, p2.lastname, p2.fathername);
    }
bool operator==(const Person& p1, const Person& p2){
    return tie(p1.name, p1.lastname, p1.fathername) == tie(p2.name, p2.lastname, p2.fathername);
}
ostream& operator<<(ostream& out, const Person& p1){
    out << p1.lastname <<' ' << p1.name;
    if (p1.fathername != "-") out << ' ' << p1.fathername;
    return out;
}

int main(){
    Person roman ("Yakunin", "Roman");
    Person vlad ("Yakunin", "Roman", "Vladimirovich");
    cout << roman << endl;
    cout << vlad << endl;

    //bool r = roman < vlad;
    
    cout << (roman == vlad);
    string str;
    fstream file;
    file.open("book.txt");
    if (file){
        while(!file.eof()){
            string tmp;
            file >> tmp;
            str += tmp;
        }
    }
    //cout << str;
    return 0;
}
