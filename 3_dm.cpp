#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 1. Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого 
// равно среднему арифметическому всех его элементов.

void midleINList(list<float>& a){
    float sum = 0;
    for (auto& i : a)
        sum += i;
    a.push_back(sum / a.size());
}

void printList(list<float>& a){
    for (float& i : a){
        cout << i << ' ';
    }
    cout << endl;
}

// 3. Реализовать собственный класс итератора, с помощью которого можно будет
// проитерироваться по диапазону целых чисел в цикле for-range-based.

class DynamicArr{
    size_t size = 5;
    int* arr;
    size_t current = 0;
    void moreSize(){
        if ((current + 1) == size){
            size *= 2;
            int* newArr = new int[size];
            for (int i = 0; i < current; ++i){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
    }
public:
    DynamicArr() : size(5), current(0) {
        arr = new int[5];
    };
    
    void push_b(const int& a){
        moreSize();
        arr[current++] = a;
    }
    
    class Iterator{
        size_t pos;
        const DynamicArr* dArr;
        
      public:
        Iterator(size_t a, const DynamicArr* d) : pos(a), dArr(d) { }
        Iterator& operator++ () {
            pos++;
            return *this;
        }
        int operator* () const {
            return dArr-> arr[pos];
        }
        bool operator!= (const Iterator& A) const {
            return A.pos != pos;
        }
    };
    Iterator begin() const {
        return Iterator(0, this);
    }
    Iterator end() const {
        return Iterator(current, this);
    }
    void print() const {
        for (const int i : *this){
            cout << i << ' ';
        }
        printf("\n");
    }
};

// 2. Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы. 
// Для реализации используйте контейнеры из STL.
class Matrix{
    size_t size;
    vector<vector<double>> mat;
public:
    Matrix() : size(0) {}
    Matrix(size_t s) : size(s) {
        for (int i = 0; i < size; ++i){
            mat.push_back(vector<double>(size));
            for (double& a : mat.back()) a = rand() % 10;
        }
    }
    
    void print(){
        for (const auto& line : mat){
            for(const double i : line){
                cout << i << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    
    double determinant(){
        vector<vector<double>> temp = mat;
        const double EPS = 1E-9;
        int n = size;
        double det = 1;
        for (int i=0; i<n; ++i) {
        	int k = i;
        	for (int j=i+1; j<n; ++j)
        		if (abs (mat[j][i]) > abs (mat[k][i]))
        			k = j;
        	if (abs (mat[k][i]) < EPS) {
        		det = 0;
        		break;
        	}
        	swap (mat[i], mat[k]);
        	if (i != k)
        		det = -det;
        	det *= mat[i][i];
        	for (int j=i+1; j<n; ++j)
        		mat[i][j] /= mat[i][i];
        	for (int j=0; j<n; ++j)
        		if (j != i && abs (mat[j][i]) > EPS)
        			for (int k=i+1; k<n; ++k)
        				mat[j][k] -= mat[i][k] * mat[j][i];
        }
        mat = temp;
        return det;
    }
};

int main(){
    list<float> a {5, 7.8, 3.2};
    printList(a);
    midleINList(a);
    printList(a);
    DynamicArr dArr;
    dArr.push_b(4);

     for (int i = 0; i < 5; ++i){
        dArr.push_b(i * 2 + 1);
    }
    for (auto i : dArr)
        cout << i << ' ';
    cout << endl;
    
    cout << "Matrix\n"; 
    Matrix m(5);
    m.print();
    cout << m.determinant() << endl;
    m.print();

    return 0;
}
