#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

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
    ~Hand() {
        for (int i = 0; i < _collection.size(); ++i){
            delete _collection[i];
        }
    }

    void add (Card * cd){
        _collection.push_back(cd);
    }

    void clear (){
        for (int i = 0; i < _collection.size(); ++i){
            delete _collection[i];
        }
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
    void printCard (int a){
        for (int i = 0; i < a; ++i) {
            cout << *_collection[i]<<' ';
        }
        printf("\n");
    }
};

class GenericPlayer : public Hand {
protected:
    string _name;
public:
    GenericPlayer () : Hand() {}
    GenericPlayer (string a) : Hand(), _name(a) {}
    virtual bool IsHitting() {return false;}

    bool IsBoosted() {
        if (GetValue() > 21) {return true;}
        return false;
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
    os << ".\t Points - " << gp.GetValue()<<".";
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
    Player () : GenericPlayer () {}
    Player (string name) : GenericPlayer (name) {}

    bool IsHitting() {
        cout << _name;
        printf(",  do u want another card? Y/N  ");
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
    House () : GenericPlayer () { _name = "House";}
    bool IsHitting() { // не работает с const
        if (GetValue() < 16) {return true;}
        else return false;
    }
    void FlipFirstCard() {
        Card first = *_collection[0];
        first.flip ();
        *_collection[0] = first;
    }
};

class Deck : public Hand {
public:
    Deck() {
        _collection.reserve(52); // хз что это
        populate();
        //shuffle ();
    }
    ~Deck(){}

    void populate () {
        clear();
        for (int s = suit::CLUBS; s <= suit::SPADES; ++s) {
            for (int r = rank1::ACE; r <= rank1::KING; ++r) {
                add(new Card(static_cast<rank1>(r), static_cast<suit>(s), 1));
            }
        }
    }

    void shuffle () {
        random_shuffle(_collection.begin(), _collection.end());
    }

    void deal (Hand& hand) {
        if (!_collection.empty()){
            hand.add(_collection.back());
            _collection.pop_back();
        }
        else {
            printf("Deck is emty!! Upss! It was too long game! ;-)");
        }
    }

    void additionalCards (GenericPlayer& genPlayer){
        cout <<endl;
        while (!(genPlayer.IsBoosted()) && (genPlayer.IsHitting())){
            deal (genPlayer);
            cout << genPlayer << endl;
            if (genPlayer.IsBoosted()){
                genPlayer.Bust();
            }
        }
    }
};

class Game {
    Deck _desk;
    House _house;
    vector<Player> _players;
public:
    Game (const vector<string>& names) {
        vector<string>::const_iterator namePlayer;
        for (namePlayer = names.begin(); namePlayer != names.end(); ++namePlayer){
            _players.push_back(Player(*namePlayer));
        }

        srand (static_cast<unsigned int>(time(0)));
        _desk.populate();
        _desk.shuffle();
    }
    ~Game (){}

    void play (){
        vector<Player>::iterator plr;
        for (int i = 0; i < 2; ++i){
            for (plr = _players.begin(); plr != _players.end(); ++plr){
                _desk.deal(*plr);
            }
            _desk.deal(_house);
        }
        _house.FlipFirstCard();

        for (plr = _players.begin(); plr != _players.end(); ++plr){
            cout << *plr << endl;
        }
        cout << _house << endl;

        for (plr = _players.begin(); plr != _players.end(); ++plr){

            _desk.additionalCards(*plr);
        }
        _house.FlipFirstCard();
        cout << endl << _house;

        _desk.additionalCards(_house);

        if (_house.IsBoosted()){
            for (plr = _players.begin(); plr != _players.end(); ++plr){
                if (!(plr->IsBoosted())){
                    plr->Win();
                }
            }
        }
        else {
            for (plr = _players.begin(); plr != _players.end(); ++plr){
                if (!(plr->IsBoosted())){
                    if (plr->GetValue() > _house.GetValue()){
                        plr->Win();
                    }
                    else if (plr->GetValue() < _house.GetValue()){
                        plr->Lose();
                    }
                    else {
                        plr->Push();
                    }
                }
            }
        }
        for (plr = _players.begin(); plr != _players.end(); ++plr){
            plr->clear();
        }
        _house.clear();
    }
};

vector<string> enterPlaters (vector<string> players){
    printf("Enter ur name: ");
    string name;
    cin >> name;
    players.push_back(name);
    printf("Do u want enter another one player? y / n ");
    cin >> name;
    while ((name == "y") || (name == "Y")){
        printf("Enter name: ");
        cin >> name;
        players.push_back(name);
        printf("Do u want enter another one player? y / n ");
        cin >> name;
    }
    return players;
}

int main (){

    vector<string> players;
    players = enterPlaters (players);
    char a = 'y';
    while ((a == 'y') || (a == 'Y')){
        system ("clear");
        Game g1 (players);
        g1.play();
        printf("Do u want play again? y / n  ");
        cin >> a;
    }
    printf("\n\nThanks for game.");
    return 0;
}
