#include <iostream>

/*
1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
*/

using namespace std;

template <class T>
class Pair1 {
    T _first;
    T _second;
public:
    Pair1 (T a, T b) : _first(a), _second(b)
    {}

    T first () const {return _first;}
    T second () const {return _second;}
};

/*
2. Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
*/
#include <string>
template <class T ,class T2>
class Pair {
protected:
    T _first;
    T2 _second;
public:
    Pair (T a, T2 b) : _first(a), _second(b)
    {}

    T first () const {return _first;}
    T2 second () const {return _second;}
};

/*
3. Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе —
любого типа. Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором
первый параметр — string, а второй — любого типа данных.
*/
template <typename T>
class StringValuePair : public Pair <string, T> {
public:
    StringValuePair (string a, T b) : Pair <string, T> (a, b)
    {}
};

/*
4. Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс
GenericPlayer, который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.
Создать класс GenericPlayer, в который добавить поле name - имя игрока. Также добавить 3 метода:

• IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
• IsBoosted() - возвращает bool значение, есть ли у игрока перебор
• Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
*/

#include <vector>

enum rank1 {
    ACE = 1,
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK = 10,
    QUEEN = 10,
    KING = 10
    };
enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

class Card {
    suit _mst;
    rank1 _value;
    bool _isFaceApp;
public:
    Card () : _mst(CLUBS), _value (TWO), _isFaceApp(false)
    {}
    Card (rank1  value, suit mst, bool chest) :
    _mst(mst), _value (value), _isFaceApp(chest)
    {}

    void flip () {
        if (_isFaceApp == false) {
            _isFaceApp = true;
        }
        else _isFaceApp = false;
    }
    int  getValue (){
        if (!_isFaceApp)
        return _value;
    }
};

class Hand {
    std::vector <Card*> _collection;
public:
    Hand () : _collection(0)
    {}

    void add (Card * cd){
        _collection.push_back(cd);
    }

    void clear (){
        _collection.clear();
    }

    int GetValue (){
        int sum = 0;
        int numinator = 0;
        for (int i = 0; i < _collection.size(); ++i){
            Card a = *_collection[i];
            sum += a.getValue();
            if (a.getValue() ==1) {
                numinator++;
                sum +=10;
            }
        }
        if (sum <= 21) return sum;
        else {
            while (numinator--) {
                sum-= 10;
                if (sum <= 21) return sum;
            }
        }
        return sum;
    }
};

class GenericPlayer : public Hand {
    string _name;
public:
    GenericPlayer () : Hand() {}
    GenericPlayer (string a) : Hand(), _name(a) {}
    bool IsHitting () { // не пойму пока какая идея с этой функцией, поэтому пока так напишу
        printf("Do you wan card? y // n:");
        char a;
        cin >> a;
        if ((a == 'y') || (a == 'Y')) {return true;}
        return false;
    }

    bool IsBoosted() {
        if (GetValue() > 21) {return false;}
        return true;
    }
    void Bust () {
        if (!IsBoosted()) {
            cout << "The player" <<_name << "has bust.\n";
        }
    }
};

int main (){
//Задание 1
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

//Задание 2
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

//Задание 3
    StringValuePair<int> svp("Amazing", 7);
    cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

//Задание 4

    Card card1(JACK, DIAMONDS, 0);
    Card card2(ACE, DIAMONDS, 0);
    Card card3(TEN, DIAMONDS, 0);
    Card card4(EIGHT, DIAMONDS, 0);
    Card card5(QUEEN, DIAMONDS, 0);
    Card card6(ACE, DIAMONDS, 0);

    Hand player;
    printf("Ochki = %d\n", player.GetValue());

    GenericPlayer Roman ("Roman");
    Roman.add(&card1);
    Roman.add(&card2);
    Roman.add(&card3);
    Roman.add(&card4);
    Roman.add(&card5);
    Roman.add(&card6);
    printf("Roman Ochki = %d\n", Roman.GetValue());

    return 0;
}
