#include "VECT.h"

VECT::VECT(): dim(0) {
  coeffi=NULL;
}
VECT::VECT(const int DIM, const SCALAR COEFF):dim(DIM) {
    if(dim < 0)
        Error("wrong initial dimension of vector");

    coeffi = new SCALAR[dim];
    if(dim > 0)
    for(int i = 0; i < dim; i++)
        coeffi[i]=COEFF;
}

VECT::VECT(const VECT &COPY):dim(COPY.dim) {
    coeffi = new SCALAR[dim];
    for(int i = 0; i < dim; i++)
        coeffi[i] = COPY.coeffi[i];
}

VECT::~VECT() {
    if(NULL != coeffi)
        delete [] coeffi;
}

VECT&VECT::operator= (const VECT &COPY) {
    if(this ==& COPY)
        return *this;
    if(dim != COPY.dim) {
        if(NULL != coeffi) delete [] coeffi;
        dim = COPY.dim;
        coeffi = new SCALAR[dim];
        }

    for(int i = 0; i < dim; i++)
        coeffi[i] = COPY.coeffi[i];
    return *this;
}

SCALAR VECT::operator*(const VECT& V_2) const {
    if(dim!=V_2.dim)
        Error("SCALAR VECT::operator*(const VECT& V_2) const: \n dimension error on +=");
    SCALAR res=0;
    for(int i = 0; i < dim; i++) res += coeffi[i] * V_2.coeffi[i];
    return res;
}

VECT operator*(const VECT& v, SCALAR sc) {
    VECT res(v);
    for (int i = 0; i < v.dim; i++) res.coeffi[i] *= sc;
        return res;
}

VECT operator*(SCALAR sc, const VECT& v) {
    return v*sc;
}

VECT operator/ (const VECT &v, SCALAR sc) {
    if (sc == 0) Error( " error! zero encounterd in operator/ ");
    return v*(1/sc);
}

VECT& VECT::operator+= (const VECT &V_2) {
    if(dim!=V_2.dim)
        Error("dimension error on +=");
    for(int i = 0; i < dim; i++) coeffi[i] += V_2.coeffi[i];
    return *this;
}

VECT&VECT:: operator-= (const VECT &V_2) {
    if(dim!=V_2.dim)
        Error("dimension error on +=");
    for(int i = 0; i < dim; i++)
        coeffi[i] -= V_2.coeffi[i];
    return *this;
}

SCALAR& VECT::operator[] (int i) {
    if( i < 0 || i >= dim)
    Error("SCALAR& VECT::operator[](int i): \n index out bound in [] operator");
    return coeffi[i];
}

SCALAR& VECT::operator[](int i) const {
    if(i < 0 || i>= dim)
        Error(" SCALAR& VECT::operator[](int i)const:\n index out bound in [] operator ");
    return coeffi[i];
}

SCALAR VECT::Norm_indef() const{
    SCALAR res=abs(coeffi[0]);
    for (int i = 1; i < dim; i++)
        if (abs(coeffi[i] ) > res)
            res = abs( coeffi[i] );
    return res;
}


VECT operator- (const VECT &V_1, const VECT &V_2) {
    if(V_1.dim!=V_2.dim)
        Error("VECT operator-(const VECT& V_1,const VECT& V_2): \n dimension error in operator - of two VECT");

    VECT res(V_1.dim);
    for(int i=0;i<V_1.dim;i++)
        res.coeffi[i] = V_1.coeffi[i] - V_2.coeffi[i];
    return res;
}

VECT operator+(const VECT &V_1, const VECT &V_2) {
    if(V_1.dim != V_2.dim)
        Error("VECT operator+(const VECT& V_1,const VECT& V_2): \n dimension error in operator + of two VECT");
    VECT res(V_1.dim);
    for(int i = 0; i < V_1.dim; i++)
        res.coeffi[i]=V_1.coeffi[i]+V_2.coeffi[i];
    return res;
}

VECT VECT::operator-() const {
    VECT res(dim);
    for(int i = 0; i < dim; i++)
        res.coeffi[i]=-coeffi[i];
    return res;
}

int VECT::get_dim() const {
    return dim;
}

void VECT::print() const{
    for(int i = 0; i< dim; i++)
    printf("%8e\t", coeffi[i]);
    printf("\n");
}
