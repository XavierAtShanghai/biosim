#ifndef VECT_H
#define VECT_H
#include "misc.h"
class VECT
{
    public:
        VECT();
        VECT(const VECT& );
        VECT(const int dim,const SCALAR COEFF=0);
        VECT& operator=(const VECT&);
        SCALAR operator*(const VECT&) const;
        friend VECT operator*(const VECT&, SCALAR sc);
        friend VECT operator*(SCALAR sc,const VECT&);
        friend VECT operator/(const VECT&,SCALAR sc);

        VECT& operator+=(const VECT&);
        VECT& operator-=(const VECT&);

        SCALAR& operator[] (int i);
        SCALAR& operator[] (int i) const;
        SCALAR Norm_indef() const;

        friend VECT operator-(const VECT& V_1,const VECT& V_2);
        friend VECT operator+(const VECT& V_1,const VECT& V_2);
        VECT operator-()const;

        int get_dim() const;
        void print() const;


        virtual ~VECT();
    protected:
    int dim;
    SCALAR *coeffi;
    private:
};

#endif // VECT_H
