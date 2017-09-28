#include "triDiagMatrix.h"

triDiagMatrix::triDiagMatrix( int _dim )
{
    if (_dim < 3)
        Error("triDiagMatrix::triDiagMatrix( int _dim ): \n dim < 3.");
    dim = _dim;
    a = VECT(dim-1);
    b = VECT(dim);
    c = VECT(dim-1);
}

triDiagMatrix::~triDiagMatrix()
{
    //dtor
}

// set
void triDiagMatrix::set_a_at(int pos, SCALAR val) {
    a[pos] = val;
}

void triDiagMatrix::set_b_at(int pos, SCALAR val) {
    b[pos] = val;
}

void triDiagMatrix::set_c_at(int pos, SCALAR val) {
    c[pos] = val;
}


// get
int triDiagMatrix::get_dim() const {
    return dim;
}

SCALAR triDiagMatrix::get_a_at( int pos) const {
    return a[pos];
}

SCALAR triDiagMatrix::get_b_at( int pos) const {
    return b[pos];
}

SCALAR triDiagMatrix::get_c_at( int pos) const {
    return c[pos];
}

//operations
VECT triDiagMatrix::operator* (const VECT& vec) const{
        if( dim != vec.get_dim( ) )
        Error("triDiagMatrix:::operator*(const VECT& vec) const : \n dimensions mismatched. ");

        VECT res(dim);
        res[0] = (vec[0] * b[0]) + (vec[1] * c[0]);
        for (int i = 1; i < dim - 1; i++){
            res[i] = (vec[i-1] * a[i-1]) + (vec[i] * b[i]) + (vec[i+1] * c[i]) ;
        }
        res[dim-1] = (vec[dim-2] * a[dim-2]) + (vec[dim-1] * b[dim -1]);
        return res;
}
VECT triDiagMatrix::Thomas_solver(const VECT& vec) const{
        /*  soliving the triagular linear system uing Thomas algerithim
            This method is only suitable for diagonally dominant matrix since pivoting is impossible in this method.
            See Wikipedia for the drivation of this method
            The indexing is
            a[ 0---> dim-2]
            b[ 0---> dim-1]
            c[ 0---> dim-2]
            right vector is vec[ 1---> dim-1]
        */

        if( dim != vec.get_dim( ) )
        Error("triDiagMatrix:::operator*(const VECT& vec) const : \n dimensions mismatched. ");
        VECT res(dim);
        VECT cprime(dim-1);

        // forward sweep
        cprime[0] = c[0] / b [0];
        res[0] =  vec[0] / b[0];

        for (int i = 1; i < dim - 1; i++){
            double m = 1.0 / (b[i] - a[i -1 ] * cprime[i - 1]);
            cprime[i ] = c[i] * m;
            res[i] = (vec[i] - a[i-1] * res[i - 1]) * m;

        }
        double m = 1.0 / (b[dim -1 ] - a[dim -2 ] * cprime[dim - 2]);
        res[dim - 1] = (vec[dim - 1] - a[ dim -2 ] * res[dim- 2]) * m;
        //backward substitution

        for (int i = dim - 2; i >= 0; i--){
           res[i] = res[i] - cprime[i] * res[i + 1];
         }
        return res;
}


//for debugging

void triDiagMatrix::print() const {
        printf( "a: \n" );
        for (int i = 0; i< dim-1; i++)
            printf(" %8e", a[i]);

        printf( "\n b: \n" );
        for (int i = 0; i< dim; i++)
            printf(" %8e", b[i]);

        printf( "\n c: \n" );
        for (int i = 0; i< dim-1; i++)
            printf(" %8e", c[i]);
        printf( " \n" );
}
