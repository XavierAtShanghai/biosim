#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include <vector>
#include<assert.h>
using namespace std;
template<class T>
class matrix{
    public:
        matrix();
        matrix(const unsigned int rows, const unsigned int colums, T COEFF=0);
        matrix(const matrix<T>& );
        T& operator()(const unsigned int R, const unsigned C);
        T operator()(const unsigned int R, const unsigned C) const;
        vector<T> operator*(const vector<T>& vec);
        matrix<T>& operator=(const matrix<T> &);
        unsigned int get_numOfRows();
        unsigned int get_numOfCols();
        T get_max_element()const;

        void print()const;
        virtual ~matrix();
    protected:
    unsigned int numOfRows;
    unsigned int numOfCols;
    unsigned int totalSize;
    T* coeffi;
    private:
};

#endif // MATRIX_H
