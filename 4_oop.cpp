#include <iostream>
#include <vector>
#include <set>

class ArrayInt {
private:
    int m_length;
    int *m_data;
public:
    ArrayInt(): m_length(0), m_data(nullptr)
    {}
    ArrayInt(int length) : m_length(length)
    {
        if (length < 0) {
            m_length = 0;
            printf("Error! Size array cant be less then Null.");
        }
        else if (length > 0) {
            m_data = new int[length];
        }
        else m_data = nullptr;
    }
    ~ArrayInt(){
        delete[] m_data;
    }

    void erase () {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    int getLength() {
        return m_length;
    }

    int& operator[] (int index) {
        if ((index >= 0) & (index < m_length)){
            return m_data[index];
        }
        else {
            printf("Error! Index not be in arrays.");
        }
    }

    void resize (int newLength){
        if (newLength == m_length){
            return;
        }
        if (newLength <= 0){
            erase ();
            return;
        }
        int *data = new int[newLength];
        if (m_length > 0) {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int index = 0; index < elementsToCopy; ++index){
                data[index] = m_data[index];
            }
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore (int value, int index){
        if ((index >= 0) & (index <= m_length)){
            int *data = new int[m_length + 1];
            for (int before = 0; before < index; ++before){
                data[before] = m_data[before];
            }
            data[index] = value;
            for (int after = index; after < m_length; ++after){
                data[after + 1] = m_data[after];
            }
            delete[] m_data;
            m_data = data;
            ++m_length;
        }
        else {
            printf("Incorrect index.");
        }
    }
    void push_back(int value){
        insertBefore(value, m_length);
    }

/*
1. Добавить в контейнерный класс, который был написан в этом уроке, методы:

• для удаления последнего элемента массива (аналог функции pop_back() в векторах)
• для удаления первого элемента массива (аналог pop_front() в векторах)
• для сортировки массива
• для вывода на экран элементов.
*/
    int getData (int index){return m_data[index];}
    void pop_back (){ // в задаче именно удаление. Специально делаю без возврата удаляемого элемента
        int *data = new int[--m_length];
        for (int i = 0; i < m_length; ++i){
            data[i] = m_data[i];
        }
        delete[] m_data;
        m_data = data; // пытался просто удалить память последнего элемента m_data  чтобы не копировать массив,
    }// но хз какой командой это делается. что то типа казалось бы логичного delete[m_length-1] m_data не работает

    void pop_front (){
        int *data = new int[--m_length];
        for (int i = 0; i < m_length; ++i){
            data[i] = m_data[i+1];
        }
        delete[] m_data;
        m_data = data;
    }

    int midlFrom3 (int a, int b, int c){
        int arr[3];
        arr[0] = a; arr[1] = b; arr[2] = c;
        for (int i = 1; i < 3; ++i){
            if (arr[i-1] > arr[i]){
                int temp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = temp;
            }
        }
        printf("\nAr = %d %d% d\n", arr[0], arr[1], arr[2]);
        if (arr[0] > arr[1]){return arr[0];}
        else return arr[1];
    }

    void swap (int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void sort(int start, int fin){
        if (fin < start){
            printf("Error! Wrong sort range.");
            return;
        }

        int oporni = m_data[(start + fin) / 2];

        int left = start;
        int rigth = fin;

        do {
            while (m_data[left] < oporni) left++;
            while (m_data[rigth] > oporni) rigth--;
            if (left <= rigth) {
                swap(m_data[rigth], m_data[left]);
                left++;
                rigth--;
            }
        } while (left < rigth);
        //printf("left = %d rigth = %d\n",left,rigth);

        if (left < fin) sort (left, fin);
        if (start < rigth) sort (start, rigth);
    }

    void sort(){
        if ((m_length == 0) || (m_length == 1)) {return;}
        sort (0, m_length-1);
    }

    void print () {
        for (int i = 0; i < m_length; ++i) {
            printf("%d ", m_data[i]);
        }
        printf("\n");
    }
};

/*
2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать
максимально быстрый алгоритм.
*/

struct Node {
    int data = NULL;
    Node *left = nullptr;
    Node *rigth = nullptr;
};

void addNodeInTree (int dat, Node *root) {
    if (root->data == NULL){
        root->data = dat;
    }
    else {
    Node *temp = root;
        while (temp->data != dat){
            if (dat > temp->data) {
                if (temp->rigth) {temp = temp->rigth;}
                else {
                    Node *newNode;
                    newNode = new Node;
                    temp->rigth = newNode;
                    newNode->data = dat;
                    return;
                }
            }
            else {
                if (temp->left) {temp = temp->left;}
                else {
                    Node *newNode;
                    newNode = new Node;
                    temp->left = newNode;
                    newNode->data = dat;
                    return;
                }
            }
        }
    }
}

void printTree (Node root){
    std::cout << root.data;
    if (root.rigth != nullptr){
        printf("(");
        printTree(*root.rigth);
        printf(")");
    }
    if (root.left!= nullptr){
        printf("(");
        printTree(*root.left);
        printf(")");
    }
}

int sumElements (Node *tree){
    //if (tree->data == NULL) return 0;
    int a = 0;
    a++;
    if (tree->left!= nullptr) {
        a += sumElements(tree->left);
    }
    if (tree->rigth!= nullptr) {
        a+= sumElements(tree->rigth);
    }
    return a;
}

void printVec (std::vector <int> a){
    for (int i = 0; i < a.size(); ++i){
        printf("%2d ", a[i]);
    }
    printf("\n");
}

/*
3. Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно поле: вектор
указателей карт (удобно использовать вектор, т.к. это по сути динамический массив, а тип его элементов
должен быть - указатель на объекты класса Card). Также в классе Hand должно быть 3 метода:
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
        if (!_chest)
        return _value;
    }
};

class Hand {
    std::vector <Card*> _collection;
/*
• метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве
параметра указатель на новую карту
• метод Clear, который очищает руку от карт
• метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз
может быть равен 11).
*/
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
            while (numinator) {
                sum-= 10;
                if (sum <= 21) return sum;
            }
        }
        return sum;
    }
};

int main (){
//Задание 1
    ArrayInt array1;
    for (int i = 0; i < 20; ++i){
        array1.push_back(rand()%100);
    }
    array1.push_back(10);
    array1.print();
    array1.sort();
    array1.print();
    //array1.pop_back();
    //array1.pop_front();
    //array1.print();
//Задание 2
    std::vector <int> vec;
    for (int i = 0; i < 50; ++i){
        vec.push_back(rand()%1000);
    }
    printVec(vec);
    Node tree;
    //printTree (tree);
    //addNodeInTree (5, &tree);
//Сетом скучно, пр\опробовал деревом сделать
    for (int i = 0; i < vec.size(); ++i){
        addNodeInTree (vec[i], &tree);
    }
    printTree (tree);
    printf("\nSum Differens Elements = %d\n", sumElements (&tree));
//Но решил проверить сетом
    std::set <int> set1;
    for (int i = 0; i < vec.size(); ++i){
        set1.insert(vec[i]);
    }
    printf("Summ in set = %d\n", set1.size());

    for(int i : set1)
        printf ("%d ", i);
    printf("\n");

//Задание 3
    Hand roman;
    Card a1(TEN, CHERVY, 0);
    Card a2(VALET, KRESTY, 0);
    Card a3(DAMA, BUBY, 0);
    Card a4(TUZ, PIKI, 0);
    Card a5(TUZ, KRESTY, 0);
    Card a6(NINE, BUBY, 0);
    printf("\na1? %d ", a1.getValue());

    //roman.add(&a6);
    //roman.add(&a2);
    roman.add(&a4);
    roman.add(&a4);
    roman.add(&a4);

    printf("\nOchko? %d ", roman.GetValue());

    return 0;
}
