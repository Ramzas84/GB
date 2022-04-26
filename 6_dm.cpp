#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;

// 1. Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо, чтобы 
// несколько потоков могли обращаться к pcout и информация выводилась в консоль. Продемонстрируйте 
// работу pcout.

mutex m;

class ThreadSafeOStream {
private:
    ostream& os;
public:
    ThreadSafeOStream(ostream& o) : os(o) {}
    template <typename T>
    ThreadSafeOStream& operator<<(const T& s) {
        m.lock();
        os << s;
        m.unlock();
        return *this;
    }
};

ThreadSafeOStream pcout(cout);

void doSomething(int number) {
    pcout << "start thread " << number << "\n";
    this_thread::sleep_for(1s);
    pcout << "stop thread " << number << "\n";
}

// 2. Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое
// число равно 15485863). Вычисления реализовать во вторичном потоке. В консоли отображать
// прогресс вычисления (в основном потоке).

class PrimeComputer{
public:
    unsigned int current, count;
    int res = -1;
    unsigned int n;
    PrimeComputer (unsigned int a) : n(a) {}

    void nPrimeNum(){
        vector<unsigned int> simple;
        simple.reserve(n);
        simple.push_back(2);
        simple.push_back(3);
        for (count = 2, current = 5; count < n; current += 2) {
            bool is_prime = true;
            float temp = sqrt(current);
            for (int i = 1; simple[i] <= temp; ++i){
                if (current % simple[i] == 0){
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                simple.push_back(current);
                ++count;
            }
        }
        res = simple[n-1];
    }
};

// 3. Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. 
// Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 
// 1 раз в секунду). При этом у каждой вещи есть своя ценность. Вор забирает вещи (функция, которая 
// находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), каждый раз 

mutex th, mas;

class Thief{
    vector<int>& things;
public:
    Thief(vector<int>& a) : things(a) {}
    
    void thief (){
        while (things.size()){
            vector<int>::iterator m = max_element(things.begin(), things.end());
            int a = *m;
            copy(m + 1, things.end(), m);
            things.pop_back();
            th.lock();
            cout << "Thief: ";
            for (int i : things) cout << i << ' ';
            cout << " - " << a << endl;
            th.unlock();
            this_thread::sleep_for(500ms);
        }
    }
};

class Master{
    vector<int>& things;
public:
    Master(vector<int>& a) : things(a) {}

    void master (){
        while ((things.size()) || things.size() <= 50){
            int a = rand() % 100;
            things.push_back(a);
            swap(things[things.size() - 1], things[rand() % things.size()]);
            mas.lock();
            cout << "Master: ";
            for (int i : things) cout << i << ' ';
            cout << " - " << a << endl;
            mas.unlock();
            this_thread::sleep_for(1s);
        }
    }
};

int main(){
    thread th1(doSomething, 1);
    thread th2(doSomething, 2);
    thread th3(doSomething, 3);
    th1.join();
    th2.join();
    th3.join();
    
    // // Задание 2
    PrimeComputer pc(1000000);
    thread th(&PrimeComputer::nPrimeNum, &pc);
    th.detach();
    while(pc.res == -1){
        cout << pc.count << " - " << pc.current << " - " << pc.count * 100 / pc.n << '%' << endl;
        this_thread::sleep_for(500ms);
    }
    cout << pc.count << " - " << pc.res << endl;
    
    // //Задание 3
    int size = 5;
    vector<int> things(size);
    for (int i = 0; i < size; ++ i) things[i] = rand() % 100;
    for (int i : things) cout << i << ' ';
    cout << endl;
    
    Thief t(things);
    Master m(things);
    
    thread ms(&Master::master, &m);
    ms.detach();
    thread tf(&Thief::thief, &t);
    tf.detach();
    
    while((things.size()) && things.size() < 50);
    
    
    return 0;
}
