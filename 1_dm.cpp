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

// Создайте структуру PhoneNumber с 4 полями:
// · код страны (целое число)
// · код города (целое число)
// · номер (строка)
// · добавочный номер (целое число, опциональный тип)
// Для этой структуры перегрузите оператор вывода. Необходимо, чтобы номер телефона
// выводился в формате: +7(911)1234567 12, где 7 – это номер страны, 911 – номер города,
// 1234567 – номер, 12 – добавочный номер. Если добавочного номера нет, то его выводить не
// надо. Также перегрузите операторы < и == (используйте tie)

struct PhoneNumber{
    int countryCode, cityCode, number, additionalNumber;
    PhoneNumber (int cc, int city, int n, int an) :
        countryCode(cc), cityCode(city), number(n), additionalNumber(an) {}
    friend bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2);
    friend bool operator==(const PhoneNumber& pn1, const PhoneNumber& pn2);
    friend ostream& operator<<(ostream& out, const PhoneNumber& pn);
};

bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2){
    return tie(pn1.countryCode, pn1.cityCode, pn1.number, pn1.additionalNumber) <
            tie(pn2.countryCode, pn2.cityCode, pn2.number, pn2.additionalNumber);
}
bool operator==(const PhoneNumber& pn1, const PhoneNumber& pn2){
    return tie(pn1.countryCode, pn1.cityCode, pn1.number, pn1.additionalNumber) ==
            tie(pn2.countryCode, pn2.cityCode, pn2.number, pn2.additionalNumber);
}
ostream& operator<<(ostream& out, PhoneNumber& pn){
    out << '+' << pn.countryCode << '(' << pn.cityCode << ')' << pn.number;
    if (pn.additionalNumber != int('-')) out <<' ' << pn.additionalNumber;
    return out;
}

int main(){
    Person roman ("Yakunin", "Roman");
    Person vlad ("Yakunin", "Roman", "Vladimirovich");
    cout << roman << endl;
    cout << vlad << endl;
    
    PhoneNumber r (1, 650, 7504109, int('-'));
    PhoneNumber v (7, 908, 5555483, int('-'));
    cout << r << endl;
    cout << v << endl;

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
