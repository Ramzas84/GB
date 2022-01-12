#include <iostream>
#include <cstdint>

/*
1. Создать класс Power, который содержит два вещественных числа. Этот класс должен иметь две переменные-члена
для хранения этих вещественных чисел. Еще создать два метода: один с именем set, который позволит присваивать значения
объявленным в классе переменным, второй — calculate, который будет выводить результат возведения первого числа в степень
второго числа. Задать значения этих двух чисел по умолчанию.
*/

class Power{
    int p_num;
    int p_pow;

public:
    //Power(int a) {printf("%c\n", "По умолчанию:");} не соображу как два конструктора написать
    Power() {p_num = 100; p_pow = 0;}
    void setPower(int num, int pow){
        p_num = num;
        p_pow = pow;
    }
    void calculate (){
        printf("%d ^ (in pow) %d = ", p_num, p_pow);
        if (p_pow == 0) {
            printf("%d", 1);
            return;
        }
        bool sig = true;
        if (p_pow < 0){
            sig = false;
            p_pow *= -1;
        }

        unsigned long long tempPow = p_num;
        unsigned long long temp = 1;
        while (p_pow != 1){
            if (p_pow %2 == 1){
                temp *= tempPow;
            }
            tempPow *= tempPow;
            p_pow /= 2;
        }
        if (sig == true){
            printf("%d\n", tempPow * temp);
            return;
        }
        else {
            printf("1/%d", tempPow * temp);
            printf(" or %f\n", 1 / (float (tempPow) * temp));
        }
    }
};

/*
2. Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t: m_red, m_green,
m_blue и m_alpha (#include cstdint для доступа к этому типу). Задать 0 в качестве значения по умолчанию для m_red,
m_green, m_blue и 255 для m_alpha. Создать конструктор со списком инициализации членов, который позволит
пользователю передавать значения для m_red, m_blue, m_green **и **m_alpha. Написать функцию print(), которая будет
выводить значения переменных-членов.
*/

class RGBA {
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;

public:
    RGBA(){m_red = 0; m_green = 0; m_blue = 0; m_alpha = 0;}
    RGBA(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
    : m_red (red), m_green (green), m_blue (blue), m_alpha (alpha)
    {}
    RGBA(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
    : m_red (red), m_green (green), m_blue (blue), m_alpha (0)
    {}
    RGBA(std::uint8_t red, std::uint8_t green)
   : m_red (red), m_green (green), m_blue (0), m_alpha (0)
    {}
     RGBA(std::uint8_t red)
    : m_red (red), m_green (0), m_blue (0), m_alpha (0)
    {}

    void print (){
        printf("Red = %d,\t Green = %d\n", m_red, m_green);
        printf("Blue = %d,\t Alpha = %d\n", m_blue, m_alpha);
    }
};

/*
3. Написать класс, который реализует функциональность стека. Класс *Stack *должен иметь:

• private-массив целых чисел длиной 10;

• private целочисленное значение для отслеживания длины стека;

• public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;

• public-метод с именем push(), который будет добавлять значение в стек. push() должен возвращать значение
false, если массив уже заполнен, и true в противном случае;

• public-метод с именем pop() для вытягивания и возврата значения из стека. Если в стеке нет значений, то
должно выводиться предупреждение;

• public-метод с именем print(), который будет выводить все значения стека.
*/

class Stack {
    int s_st[10] = {NULL};
    int s_now = 0;

public:
    void reset(){
        /*
        for (int i = 0; i < s_now; ++i){  - когда слышу резет хочется так сделать, но именно под эту задачу мне кажется
            s_st[i] = NULL;                 правильнее без этого.
        }
        */
        s_now = 0;
    }

    bool push (int num){
        if (s_now == 10) {
            printf ("Error!! Stack full.");
            return false;
        }
        s_st[s_now++] = num;
        return true;
    }

    int pop (){
        if (s_now == 0) {
            printf("Error!! Stek empty.");
        }
        else {
            return s_st[s_now--];
        }
    }

    void print(){
        printf("%c", '(');
        for (int i = 0; i < s_now - 1; ++i){
            printf("%d, ", s_st[i]);
        }
        if (s_now > 0) printf("%d", s_st[s_now - 1]);
        else printf("empty");
        printf(")\n");
    }
};

int main (){
// Задание 1
std::cout << "   --TASK 1--" <<std::endl;
    Power first;
    first.setPower (2, -1);
    first.calculate();

// Задание 2
std::cout <<std::endl<<  "   --TASK 2--"  <<std::endl;
    RGBA green1 (7, 0,1);
    green1.print();

// Задание 3
std::cout <<std::endl<<  "   --TASK 3--"  <<std::endl;
    Stack stack1;
    stack1.push(3);
    stack1.push(7);
    stack1.push(5);
    stack1.print();
    //stack1.reset();
    stack1.print();
    stack1.pop();
    stack1.print();
    stack1.pop();
    stack1.print();
    stack1.pop();
    stack1.print();
    stack1.pop();
    stack1.print();
    stack1.push(485);
    stack1.print();

   return 0;
}
