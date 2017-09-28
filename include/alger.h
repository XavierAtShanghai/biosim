#ifndef ALGER_H
#define ALGER_H
#include "misc.h"
#include "VECT.h"
#include "generalParameters.h"
static const double sqrtPi=sqrt(PI);

namespace alger
{
        VECT gaussElimin(const MATR& a, const VECT& v);
        VECT gaussPivot(const MATR& a, const VECT& v,double tol=1.0e-9);

        void swapRows(VECT& a, const int i, const int j);
        void swapRows(MATR& a, const int i, const int j);
        void swapCols(MATR& a, const int i, const int j);

        VECT func(const VECT& x, const VECT & par);
        MATR Jacobian(const VECT& x);

        MATR Jacobian_approx(VECT (*f)(const VECT&, const VECT & par),const VECT& x,const VECT&);

        VECT newtonRahpson(VECT (*f)(const VECT&, const VECT& par),const VECT&, const VECT&, int maxIter=20,double tol=1e-10);
};

#endif // ALGER_H
