#include <iostream>
#include <memory>

using namespace std;
/*
1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите
оператор вывода для данного класса. Создайте два "умных" указателя today и date.
Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям
класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.
Затем переместите ресурс, которым владеет указатель today в указатель date. Проверьте, являются ли нулевыми
указатели today и date и выведите соответствующую информацию об этом в консоль.
*/

class Date {
    int _day;
    int _month;
    int _year;
public:
    Date () {_day = 0; _month = 0; _year = 0;}
    Date (int day, int month, int year) :
        _day(day), _month(month), _year(year) {}
    void setDate (int day, int month, int year) {
        _day = day;
        _month = month;
        _year = year;
    }
    int getDay (){
        return _day;
    }
    int getMonth (){
        return _month;
    }
    int getYear (){
        return _year;
    }

    friend std::ostream& operator<< (std::ostream &out, Date &_date);
    friend Date moreLastDate (unique_ptr<Date>& a, unique_ptr<Date>& b);
};

 std::ostream& operator<< (std::ostream &out, Date &_date) {
    //return out << printf("%2d.%2d.%d", _date._day, _date._month, _date._year);
    if (_date._day < 10) {out << '0';}
    out << _date._day <<'.';
    if (_date._month < 10) {out << '0';}
    out << _date._month << '.'<< _date._year;
    return out;
}

/*
2. По условию предыдущей задачи создайте два умных указателя date1 и date2.

• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает
их между собой (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в
качестве параметров.
*/

Date moreLastDate (unique_ptr<Date>& a, unique_ptr<Date>& b) {
    if (a->_year != b->_year){
        if (a->_year > b->_year) return *a;
        else return *b;
    }
    else if (a->_month != b->_month){
        if (a->_month > b->_month) return *a;
        else return *b;
    }
    else if (a->_day != b->_day) {
        if (a->_day > b->_day) return *a;
        else return *b;
    }
    else {
        printf("Da oni zhe ravn#!!");
        return *a;
    }
}

    void swapUPtr (unique_ptr<Date> a, unique_ptr<Date> b) {
    unique_ptr<Date> temp = move (a);
    a = move(b);
    b = move(temp);
}

int main (){
//Задание 1
    unique_ptr<Date> today;
    unique_ptr<Date> date;
    today = make_unique<Date>(3, 2 , 2022);
    cout << today->getDay() << '.' << today->getMonth() << '.' << today->getYear() <<endl;
    cout << *today <<endl;
    cout <<"today = "<< &today <<endl;
    date = move(today);
    cout <<"today = "<< &today <<endl; //ссылка как была так и осталась, а сама дата переехала
    cout <<"date = "<< &date << '-'<< *date <<endl;
//Задание 2
    unique_ptr<Date> date1 = make_unique<Date>(13, 11, 1984);
    unique_ptr<Date> date2 = make_unique<Date>(3, 2 , 2022);
    date.get();
    // как то так. Функция обменивает их местами, но поскольку они умные, они после этого уничтожаются
    //

    cout << "d1 = " << *date1 <<",  d2 = " << *date2 <<endl;


    return 0;
}
