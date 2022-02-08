#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

/*
1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать
исключение DivisionByZero, если второй параметр равен 0. В функции main выводить результат вызова функции div
в консоль, а также ловить исключения.
*/

float separate (float numinator, float deniminator){
    if (deniminator == 0) {
        throw "Division By Zero";
    }
    return numinator / deniminator;
}

/*
2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу,
инициализирующий x значением параметра. Написать класс Bar, хранящий вещественное число y (конструктор по
умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a. Если y +
a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. В функции main
завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. Использовать его в
качестве параметра метода set до тех пор, пока не будет введено 0. В обработчике исключения выводить
сообщение об ошибке, содержащее данные объекта исключения.
*/

class Ex {
    float x;
public:
    Ex (float a) : x(a) {}

    friend ostream& operator << (ostream &out, Ex &ex);
};

ostream& operator << (ostream &out, Ex &ex){
        out << ex.x;
        return out;
    }

class Bar {
    float y;
public:
    Bar () : y(0) {}
    void set (int a) {
        if ((y + a) > 100){
            throw Ex (a*y);
        }
        y = a;
    }
    float get() {
        return y;
    }
};

int enterInt (){
    stringstream num;
    string a;
    cin >> a;
    int i = 0;
    int n;
    while (a[i] != '\0'){
        if ((int(a[i]) < int('0')) || (int(a[i]) > int ('9'))){
            printf ("In not number. Try again: ");
            cin >> a;
            i = 0;
        }
        else ++i;
    }
    num << a;
    num >> n;
    return n;
}
/*
3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,
означающий задание переместиться на соседнюю позицию. Эти методы должны запускать классы-исключения
OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда
(направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую
информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим
классом и перехватывающую все исключения от его методов, а также выводящую подробную информацию
о всех возникающих ошибках.
*/
class OffTheField{
    int _nowGoriz;
    int _nowVert;
    const string _err;
public:
    OffTheField (int a, int b, const string err) :
        _nowGoriz(b + 1), _nowVert(a + 1), _err(err) {
            cout << "You now in "<<_nowGoriz <<':'<<_nowVert<<'!'
            <<" You " << _err;
        }
};

class IllegalCommand{
    int _nowGoriz;
    int _nowVert;
    const string _err;
public:
     IllegalCommand (int a, int b, const string err) :
        _nowGoriz(b + 1), _nowVert(a + 1), _err(err) {
            cout << "You now in "<<_nowGoriz <<':'<<_nowVert<<'!'
            <<" You " << _err;
        }
};

class Robot {
    int _goriz;
    int _vert;
    //char _desk[10][10] = {' '};
public:
    Robot () : _goriz(0), _vert(0) {}
    Robot (int a, int b) : _goriz(--b), _vert(--a) {}
    Robot (int a) : _vert((a / 10) - 1), _goriz((a % 10) - 1) {}

    void roboMove (char a){
        if ((a == 'w') || (a == 'W')) {
            if ((_vert - 1) < 0){
                const string err = "cannot go to Up!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _vert--;
        }
        else if ((a == 's') || (a == 'S')) {
            if ((_vert + 1) >= 10){
                const string err = "cannot go to Down!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _vert++;
        }
        else if ((a == 'a') || (a == 'A')) {
            if ((_goriz -1) < 0){
                const string err = "cannot go to Left!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz--;
        }
        else if ((a == 'd') || (a == 'D')) {
            if ((_goriz + 1) >= 10){
                const string err = "cannot go to Right!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz++;
        }
        else if ((a == 'e') || (a == 'E')) {
             if (((_goriz + 1) >= 10) || ((_vert - 1) < 0)){
                const string err = "cannot go to Up and Right!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz++; _vert--;
        }
        else if ((a == 'q') || (a == 'Q')) {
            if (((_goriz - 1) < 0) || ((_vert - 1) < 0)){
                const string err = "cannot go to Up and Left!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz--; _vert--;
        }
        else if ((a == 'z') || (a == 'Z')) {
            if (((_goriz - 1) < 0) || ((_vert + 1) >= 10)){
                const string err = "cannot go to Down and Left!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz--; _vert++;
        }
        else if ((a == 'c') || (a == 'C')) {
            if (((_goriz + 1) >= 10) || ((_vert + 1) >= 10)){
                const string err = "cannot go to Down and Right!!";
                throw OffTheField (_goriz, _vert, err);
            }
            _goriz++; _vert++;
        }
        else {
            const string err = "want do not to one step! Use onli 'w' - for up, 's' - for down, 'e' - for up and right and t.p.";
            throw IllegalCommand (_goriz, _vert, err);
        }
    }
    friend ostream& operator << (ostream &out, Robot &robot);
};

ostream& operator << (ostream &out, Robot &robot){
        for (int i = 0; i < 10; ++ i){
            printf ("%2d ", 1+i);
            for (int j = 0; j < 10; ++j){
                if ((i == robot._vert) && (j == robot._goriz)) out << "|R";
                else out << "|_";
            }
            out << "|\n";
        }
        out <<"   ";
        for (int i = 1; i <= 10; ++i){
            printf ("%2d", i);
        }
        return out;
    }

int main (){
//Задание 1
    try {
        cout << separate (10, 0) << endl;
    }
    catch (const char* hzchto){
        cerr << "Error: " << hzchto << endl;
    }
//Задание 2
    Bar bar;
    int a;
    cout << "Enter y: ";
    a = enterInt();
        while (a != 0) {
            try {
                bar.set(a);
                cout << "Bar (y) = "<<bar.get() <<endl;
            }
            catch (Ex hz){
                cerr << "Error: exception of type Ex!! Ex = "<<bar.get()<<" * "<<a <<" = " <<hz <<endl;
            }
            cout << "Enter y again (0 for escape): ";
            a = enterInt();
        }
//Задание 3
    system ("clear");
    Robot robi(1, 3);
    cout << robi <<"\n"<<"Make move. (Like in game. Doom for example.): "<< endl;
    char coord;
    cin >> coord;
    while (coord != '0'){
        try {robi.roboMove(coord);
            system ("clear");
            cout << robi <<"\n"<<"Make move. (0 for escape): "<< endl;
        }
        catch (OffTheField err){
            cerr << endl;
        }
        catch (IllegalCommand err){
            cerr << endl;
        }
        cin >> coord;
    }
    return 0;
}
