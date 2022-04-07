#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
#include <algorithm>

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
        return tie(p1.lastname, p1.name, p1.fathername) < tie(p2.lastname, p2.name, p2.fathername);
    }
bool operator==(const Person& p1, const Person& p2){
    return tie(p1.lastname, p1.name, p1.fathername) == tie(p2.lastname, p2.name, p2.fathername);
}
ostream& operator<<(ostream& out, const Person& p1){
    out << right << setw(12) << p1.lastname  << right << setw(10)<< p1.name  
        << std::right << std::setw(15) << (p1.fathername == "-" ? "" : p1.fathername);
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
    int countryCode, cityCode, additionalNumber;
    string number;
    PhoneNumber (int cc, int city, string n, int an) :
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
ostream& operator<<(ostream& out, const PhoneNumber& pn){
    if (pn.countryCode != -1){
        out << '+' << pn.countryCode << '(' << pn.cityCode << ')' << pn.number;
        if (pn.additionalNumber != -1) out <<' ' << pn.additionalNumber;
    }
    return out;
}

// Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер
// телефона. Конструктор этого класса должен принимать параметр типа ifstream – поток данных,
// полученных из файла. В теле конструктора происходит считывание данных из файла и
// © geekbrains.ru 25
// заполнение контейнера. Класс PhoneBook должен содержать перегруженный оператор
// вывода, для вывода всех данных из контейнера в консоль.

class PhoneBook{
    vector<pair<Person, PhoneNumber>> book;
public:
    PhoneBook(ifstream& file) {
        if (file){
            string ln, n, fn;
            while(file >> ln >> n >> fn){
                Person cur(ln, n, fn);
                int country, city, addit;
                string number;
                file >> country >> city >> number;
                string additnl;
                file >> additnl;
                if (additnl != "-"){
                    addit = atoi(additnl.c_str());
                }
                else addit = -1;
                PhoneNumber curPerson (country, city, number, addit);
                book.push_back({cur, curPerson});
            }
        }
    }
    friend ostream& operator<<(ostream& out, const PhoneBook& pn);

// В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы
// контейнера по фамилии людей в алфавитном порядке. Если фамилии будут одинаковыми, то
// сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка
// производится по отчествам. Используйте алгоритмическую функцию sort.
    void SortByName(){
        sort(book.begin(), book.end(), 
            [](pair<Person, PhoneNumber> per1, pair<Person, PhoneNumber> per2)
            {return per1.first < per2.first;});
    }
    
// Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по
// номерам телефонов. Используйте алгоритмическую функцию sort
    void SortByPhone(){
        sort(book.begin(), book.end(), 
            [](pair<Person, PhoneNumber> per1, pair<Person, PhoneNumber> per2)
            {return per1.second < per2.second;});
    }
    
// Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает
// кортеж из строки и PhoneNumber. Строка должна быть пустой, если найден ровно один
// человек с заданном фамилией в списке. Если не найден ни один человек с заданной
// фамилией, то в строке должна быть запись «not found», если было найдено больше одного
// человека, то в строке должно быть «found more than 1».
    tuple<string, PhoneNumber> GetPhoneNumber (const string& ln){
        PhoneNumber phone(-1, 0, "0", -1);
        int flag = 0;
        for (int i = book.size() - 1 ; i >= 0; --i){
            if (book[i].first.lastname == ln){
                ++flag;
                phone = book[i].second;
            }    
        }
        string text = "";
        if (!flag) text = "not found";
        else if (flag > 1) text = "found more than 1";
        return tie(text, phone);
    }
// Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер
// телефона и, если находит заданного человека в контейнере, то меняет его номер телефона на
// новый, иначе ничего не делает.
    void ChangePhoneNumber (Person p, PhoneNumber newNumber){
        for (auto& rec : book){
            if (rec.first == p){
                rec.second = newNumber;
                return;
            }
        }
    }
};

ostream& operator<<(ostream& out, const PhoneBook& pn){
    for (const auto& rec : pn.book){
        out << ' ' << rec.first << "\t" << rec.second << endl;
    }
    return out;
}



int main(){
    ifstream file ("book.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book (file);
    cout << book;
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;
    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона
    // этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else cout << get<0>(answer);
        cout << endl;
    };
    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                            PhoneNumber{7, 123, "15344458", -1}); // nullopt?
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                            PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
    
    return 0;
}
