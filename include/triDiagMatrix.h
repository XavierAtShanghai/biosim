#ifndef TRIDIAGMATRIX_H
#define TRIDIAGMATRIX_H
#include "misc.h"
#include "VECT.h"
class triDiagMatrix
{
    public:
        triDiagMatrix( int dim );
        virtual ~triDiagMatrix();

        // seters
        void set_a_at(int pos, SCALAR val);
        void set_b_at(int pos, SCALAR val);
        void set_c_at(int pos, SCALAR val);

        //getters
        int get_dim() const;
        SCALAR get_a_at( int pos) const;
        SCALAR get_b_at( int pos) const;
        SCALAR get_c_at( int pos) const;


        //operations
        VECT operator* (const VECT& vec) const;
        VECT Thomas_solver(const VECT& vec) const;

        //for debuging
        void print() const;

    protected:

    private:
    VECT a, b, c;
    int dim;
};

#endif // TRIDIAGMATRIX_H
