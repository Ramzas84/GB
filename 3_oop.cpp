#include <iostream>
#include <math.h>

/*
1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм)
и Circle (круг). Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат),
Rhombus (ромб). Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную
функцию area() (площадь). Во всех остальных классах переопределить эту функцию, исходя из геометрических
формул нахождения площади.
*/

class Figure{
public:
    virtual float area () = 0;
};

class Parallelogram : public Figure {
protected:
    //float _sq;
    float _size1;
    float _height;
public:
    Parallelogram () {_size1 = 0; _height = 0;}
    Parallelogram (float size1, float heighInSize1)
    : _size1(size1), _height(heighInSize1)
    {}
    float area (){
    return _size1 * _height;
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle ()
    :Parallelogram()
    {}
    Rectangle (float a, float b)
    :Parallelogram(a, b)
    {}
};

class Square : public Parallelogram {
public:
    Square ()
    :Parallelogram ()
    {}
    Square (float a)
    : Parallelogram (a, 0)
    {}
    float area (){
    return _size1 * _size1;
    }
};

class Circle : public Figure {
    float _radius;
public:
    Circle () {_radius = 0;}
    Circle (float r)
    :_radius(r)
    {}
    float area() {
        return _radius*_radius*3.14;
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus ()
    :Parallelogram ()
    {}
    Rhombus (float size1, float heighInSize1)
    :Parallelogram (size1, heighInSize1)
    {}
};

/*
2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники:
PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн).
Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. Создать объекты для
каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание
на проблему «алмаз смерти».
*/

#include <string>

class Car {
protected:
    std::string _company;
    std::string _model;
public:
    Car ()
    :_company("Defolt"), _model("Defolt")
    {std::cout <<"Company: "<<_company <<".\tModel - " << _model<<std::endl;}
    Car (std::string company, std::string model)
    :_company(company), _model(model)
    {std::cout <<"Company: "<<_company <<".\tModel - " << _model<<std::endl;}

    void setCompany (std::string comany){
        _company = comany;
    }
};

class PassengerCar : virtual public Car {
protected:
    int _maxSpeed;
public:
    PassengerCar ()
    :_maxSpeed(0)
    {std::cout <<"Max speed "<<_maxSpeed << " km/h."<< std::endl;}
    PassengerCar (int speed)
    :_maxSpeed(speed)
    {std::cout <<"Max speed "<<_maxSpeed << " km/h."<< std::endl;}
};

class Bus : virtual public Car {
protected:
    int _passagirs;
public:
    Bus ()
    : _passagirs(0)
    {std::cout <<"Passenger seats "<<_passagirs << std::endl;}
    Bus (int passagirs)
    : _passagirs(passagirs)
    {std::cout <<"Passenger seats "<<_passagirs << std::endl;}

    Bus (int passagirs, std::string company)
    :Car (company, "Mod"), _passagirs(passagirs)
    {std::cout <<"Passenger seats "<<_passagirs << std::endl;}
};

class Minivan : public PassengerCar, public Bus {
    std::string _color;
public:
    Minivan ()
    : _color ("metall")
    {std::cout <<"Minivan color "<<_color << std::endl;}
    Minivan (std::string color)
    :_color (color)
    {std::cout <<"Minivan colorcompany "<<_color << std::endl;}

    //Minivan (std::string company, std::string color) - не пойму как конструктор сделать что б менял параметр прародителя
    //:_color (color),
    //:PassengerCar _company(company)

    //{std::cout <<"Minivan color "<<_color << std::endl;}
};

/*
3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
*/

class Fraction {
    int _numerator;
    int _denominator;
public:
    Fraction()
    :_numerator(1), _denominator(1)
    {}
    Fraction(int numerator, int denominator)
    : _numerator(numerator), _denominator(denominator)
    {
        if (_denominator == 0){
            printf("Error! Denominator cant be Null.\n");
            _denominator = 404;
        }
        while ((_numerator % 2 == 0) & (_denominator % 2 == 0)){
                _denominator /= 2;
                _numerator /=2;
            }
        int temp = _denominator / 2;
        for (int i = 3; i <= temp; i +=  2){
            while ((_numerator % i == 0) & (_denominator % i == 0)){
                _numerator /= i;
                _denominator /= i;
            }
            temp = _denominator / 2;
        }
    }

    void print (){
        if (_denominator == 0){
            printf("Error! Denominator cant be Null.\n");
        }
        else if (_numerator == 0) {
            printf("%d\n", 0);
        }
        else if (_denominator == 1) {
            printf("%d\n", _numerator);
        }
        else if (_numerator >= _denominator){
            printf("%d  %d/%d\n", _numerator / _denominator, _numerator, _denominator);
        }
        else printf("%d/%d\n", _numerator, _denominator);
    }

    void print (Fraction a){
        if (a._denominator == 0){
            printf("Error! Denominator cant be Null.\n");
        }
        else if (a._numerator == 0) {
            printf("%d", 0);
        }
        else if (a._denominator == 1) {
            printf("%d", a._numerator);
        }
        else if (a._numerator >= a._denominator){
            printf("%d and %d/%d", a._numerator / a._denominator, a._numerator, a._denominator);
        }
        else printf("%d/%d", a._numerator, a._denominator);
        printf ("\n");
    }

    Fraction sum (Fraction a, Fraction b){
        if (a._denominator == b._denominator){
            a._numerator += b._numerator;
            return a;
        }
        else {
            int temp = a._denominator;
            a._denominator *= b._denominator;
            a._numerator *= b._denominator;
            b._denominator *= temp;
            b._numerator *= temp;
            a._numerator += b._numerator;

            while ((a._numerator % 2 == 0) & (a._denominator % 2 == 0)){
                a._denominator /= 2;
                a._numerator /=2;
            }
            temp = a._denominator / 2;
            for (int i = 3; i <= temp; i +=  2){
                while ((a._numerator % i == 0) & (a._denominator % i == 0)){
                    a._numerator /= i;
                    a._denominator /= i;
                }
                temp = a._denominator / 2;
            }
            return a;
        }
    }

    Fraction multiplication (Fraction a, Fraction b){
        a._numerator *= b._numerator;
        a._denominator *= b._denominator;

        while ((a._numerator % 2 == 0) & (a._denominator % 2 == 0)){
                a._denominator /= 2;
                a._numerator /=2;
            }
        int temp = a._denominator / 2;
        for (int i = 3; i <= temp; i +=  2){
            while ((a._numerator % i == 0) & (a._denominator % i == 0)){
                a._numerator /= i;
                a._denominator /= i;
            }
            temp = a._denominator / 2;
        }
        return a;
    }

    friend Fraction operator+ (Fraction a, Fraction b);
    friend Fraction operator+ (Fraction a, int b);
    friend Fraction operator- (Fraction a, Fraction b);
    friend Fraction operator* (Fraction a, Fraction b);
    friend Fraction operator* (int a, Fraction b);
    friend Fraction operator/ (Fraction a, Fraction b);
    friend Fraction operator- (Fraction a);
    friend bool operator== (Fraction a, Fraction b);
    friend bool operator!= (Fraction a, Fraction b);
    friend bool operator> (Fraction a, Fraction b);
    friend bool operator< (Fraction a, Fraction b);
    friend bool operator>= (Fraction a, Fraction b);
    friend bool operator<= (Fraction a, Fraction b);
};

Fraction operator+ (Fraction a, Fraction b) {
    return a.sum (a, b);
}

Fraction operator+ (Fraction a, int b) {
    Fraction temp (b, 1);
    return a.sum(a, temp);
}

Fraction operator- (Fraction a, Fraction b) {
    b._numerator *=-1;
    return a.sum (a, b);
}

Fraction operator* (Fraction a, Fraction b){
    return a.multiplication (a, b);
}

Fraction operator* (int a, Fraction b){
    Fraction temp (a, 1);
    return temp.multiplication (temp, b);
}

Fraction operator/ (Fraction a, Fraction b){
    int temp = b._denominator;
    b._denominator = b._numerator;
    b._numerator = temp;
    return a.multiplication (a, b);
}

Fraction operator- (Fraction a) {
    a._numerator *= -1;
    return a;
}

bool operator== (Fraction a, Fraction b){
    a = a - b;
    if (a._numerator == 0){
        return true;
    }
    else return false;
}

bool operator!= (Fraction a, Fraction b){
    if (a == b){
        return false;
    }
    else return true;
}

bool operator> (Fraction a, Fraction b){
    a = a - b;
    if ((a._denominator > 0) & (a._numerator > 0)) return true;
    if ((a._denominator < 0) & (a._numerator < 0)) return true;
    return false;
}

bool operator< (Fraction a, Fraction b){
    if (a > b) return false;
    return true;
}

bool operator>= (Fraction a, Fraction b){
    if (a > b || a == b) return true;
    return false;
}

bool operator<= (Fraction a, Fraction b){
    if (a < b || a == b) return true;
    return false;
}

/*
4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: масть,
значение карты и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение карты типом
перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода:

метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает
лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
*/

enum mast {
        PIKI = 0,
        CHERVY,
        KRESTY,
        BUBY
    };

enum nominal {
        DVOIKA = 2,
        TROIKA,
        CHETVERKA,
        PYTERKA,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        VALET = 10,
        DAMA = 10,
        KOROL = 10,
        TUZ = 1
    };

class Card {
    mast _mst;
    nominal _value;
    bool _chest;
public:
    Card () : _mst(PIKI), _value (DVOIKA), _chest(false)
    {}
    Card (nominal  value, mast mst, bool chest) :
    _mst(mst), _value (value), _chest(chest)
    {}

    void flip () {
        if (_chest == false) {
            _chest = true;
        }
        else _chest = false;
    }
    int  getValue (){
        return _value;
    }
};

int main (){
//Задание 1
    Parallelogram p1(2,3);
    std::cout<< "Parallel "<< p1.area() << std::endl;

    Circle c2(2);
    std::cout<< "Circle "<< c2.area() << std::endl;

    Rectangle r1(2, 5);
    std::cout<<"Rectangle "<< r1.area() << std::endl;

    Square s(5);
    std::cout<<"Square "<< s.area() << std::endl;

    Rhombus rh(4, 10);
    std::cout<<"Rhombus "<< rh.area() << std::endl;

//Задание 2
    //Car tesla("Tesla", "Model S");
    //PassengerCar ferrari (300);
    Bus bus(28, "BadMobil");

    //Minivan van("Red!");

//Задание 3

    Fraction fr1(1, 2);
    Fraction fr2(50, 101);
    Fraction fr3 = -fr2;
    //std::cout << fr1 + fr2 << std::endl;
    fr3.print(10 * -fr2);

    if ((fr1 * fr2) >= fr3) {
        printf("true\n");
    }
    else printf("not true :-) ");

//Задание 4
    Card cart (DAMA, PIKI, 0); // значение, масть, рубашка
    printf("%d", cart.getValue());








    return 0;
}
