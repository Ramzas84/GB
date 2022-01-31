#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

/*
1. Создать программу, которая считывает целое число типа int. И поставить «защиту от дурака»: если
пользователь вводит что-то кроме одного целочисленного значения, нужно вывести сообщение об ошибке
и предложить ввести число еще раз.
*/

using namespace std;

unsigned int fullProtected (){
    printf("Enter a positive 9-digit number: ");
    bool flag;
    stringstream strim;
    char temp[10];
    do {
        flag = true;
        cin >> setw(10)>> temp;
        for (int i = 0; temp[i] != '\0'; ++i){
            if ((temp[i] == '0') || (temp[i] == '1') || (temp[i] == '2') || (temp[i] == '3') || (temp[i] == '4') ||
            (temp[i] == '5') || (temp[i] == '6') || (temp[i] == '7') || (temp[i] == '8') || (temp[i] == '9')) {}
            else {
                flag = false;
                printf("Its not positive 9-digit number! Try again: ");
                break;
            }
        }
    } while (flag == false);
    strim << temp;
    unsigned int numb;
    strim >> numb;
    return numb;
}

/*
2. Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода
строки и сбрасывает буфер.
*/

ostream &endll (ostream &stream){
    printf("\n");
    cout << endl;
}

/*
3. Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
*/

enum rank1 {
    ACE = 1,
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK,
    QUEEN,
    KING
    };
enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

class Card {
public:
    suit _mst;
    rank1 _value;
    bool _isFaceApp;

    Card () : _mst(CLUBS), _value (TWO), _isFaceApp(false)
    {}
    Card (rank1  value, suit mst, bool chest) :
    _mst(mst), _value (value), _isFaceApp(chest)
    {}

    void flip () {
        if (_isFaceApp == false) {
            _isFaceApp = true;
        }
        else {_isFaceApp = false;}
    }
    int  getValue (){
        if (_isFaceApp){
            if (_value <= 10) {
                return _value;
            }
            else return 10;
        }
        else return 0;
    }
    bool chest () {return _isFaceApp;}

    friend ostream& operator<< (ostream& os, const Card& aCard);
};

ostream& operator<< (ostream& os, Card& aCard) {
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string SUITS[] = {"c", "d", "h", "s"};
    if (aCard._isFaceApp) { // не видит cd._isFaceApp из privata
        os << RANKS[aCard._value] << SUITS[aCard._mst];
    }
    else {
        os <<"XX";
    }
    return os;
}

class Hand {
protected:
    vector <Card*> _collection;
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
protected:
    string _name;
public:
    GenericPlayer () : Hand() {}
    GenericPlayer (string a) : Hand(), _name(a) {}
    bool IsHitting () { // не пойму пока какая идея с этой функцией, поэтому пока так напишу
        printf("Do you wan card? y // n:");
        char a;
        cin >> a ;
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
    string getName () {return _name;}

    friend ostream& operator<< (ostream& os, GenericPlayer& gp);
};

ostream& operator<< (ostream& os, GenericPlayer& gp) {
    os <<gp._name << ": ";
    for (int i = 0; i < gp._collection.size(); ++i){
        os << *gp._collection[i] << " ";
    }
    os << "\t Points - " << gp.GetValue()<<".";
    return os;
}


class Player : public GenericPlayer {
public:
/*
• virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса. Метод спрашивает
у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
• void Win() const- выводит на экран имя игрока и сообщение, что он выиграл.
• void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
• void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
*/
    Player () : GenericPlayer () {_name = "Player";}
    Player (string name) : GenericPlayer (name) {}

    virtual bool IsHitting() const {
        printf("Do u want another card? Y/N");
        char flag = '0';
        cin >> flag;
        if ((flag == 'y') || (flag == 'Y')){
            return true;
        }
        else return false;
    }

    void Win() const {
        cout << GenericPlayer::_name << " congratulation!! U win!!" << endl;
    }
    void Lose() const {
        cout << GenericPlayer::_name << ". You r lose!! Xa-xa-xa!" << endl;
    }
    void Push() const {
        cout << GenericPlayer::_name << " draw. Dont fish, dont met :-(." << endl;
    }
  /*
  4. Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer.
  У него есть 2 метода:

• virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не
больше 16 очков, то он берет еще одну карту.
• void FlipFirstCard() - метод переворачивает первую карту дилера.
  */
};

class House : public GenericPlayer {
public:
    House () : GenericPlayer () { _name = "House1";}
    virtual bool IsHitting() { // не работает с const
        if (GetValue() < 16) {return true;}
        else return false;
    }
    void FlipFirstCard() {
        Card first = *_collection[0];
        first.flip ();
        *_collection[0] = first;
    }
/*
5. Написать перегрузку оператора вывода для класса Card. Если карта перевернута рубашкой вверх (мы ее не видим),
вывести ХХ, если мы ее видим, вывести масть и номинал карты. Также для класса GenericPlayer написать перегрузку
оператора вывода, который должен отображать имя игрока и его карты, а также общую сумму очков его карт.
*/
};


int main (){
//Задание 1
    //cout << fullProtected () << endl;
//Задание 2
    //cout << endll <<"Doubl /n " << 5 << endll;
//Задание 3
    Player player1 ("Roman");
    player1.Push();
//Задание 4 и 5
    House a;
    Card c1 (FIVE, DIAMONDS, 1);
    Card c2 (JACK, DIAMONDS, 1);
    Card c3 (TEN, DIAMONDS, 0);
    Card c4 (ACE, DIAMONDS, 1);

    cout << c2 << c1;
    cout << endl;


    cout << a.getName() << ". Point - "<< a.GetValue() << endll;
    //a.add(&c1);
    a.add(&c2);
    //a.add(&c1);
    a.add(&c3);
    a.add(&c4);

    cout << a;
    cout <<endl;
    a.FlipFirstCard();
    cout << a;
    cout <<endl;
    a.FlipFirstCard();
    cout << a;
    cout <<endl;
    player1.add(&c1);
    player1.add(&c2);
    player1.add(&c3);
    Player player2;
    cout << player2 << endll << a;



    return 0;
}
