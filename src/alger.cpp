#include "alger.h"

VECT alger::gaussElimin(const MATR& a, const VECT& v){
MATR A=a;
VECT b=v;
int n=v.get_dim();
for(int k=0;k<n-1;k++){
    for(int i=k+1;i<n;i++){
        if(A(i,k)!=0){
            double lam=A(i,k)/A(k,k);
            for(int j=k+1;j<n;j++){
            A(i,j)=A(i,j)-lam*A(k,j);
            }
            b[i]=b[i]-lam*b[k];
        }
    }

}

//back substituion
b[n-1] = b[n-1] / A(n-1,n-1);
for(int k=n-2;k>=0;k--){
        for(int j=k+1;j<n;j++)
            b[k]-=A(k,j)*b[j];
        b[k]=b[k]/A(k,k);
}

return b;
}

VECT alger::gaussPivot(const MATR& a_p, const VECT& v_p, double tol){

    MATR A = a_p;
    VECT b = v_p;
    int n = v_p.get_dim();

    VECT s(n,0);

    for(int k = 0; k < n; k++){
        for( int j = 0; j < n-1; j++ ){
        if( abs(A(k,j)) > s[k] ) s[k] = abs( A(k,j) );
        }
    }


    for(int k = 0; k < n-1; k++){
        //pivoting
        int P = k;
        for(int i = k+1; i < n; i++){
        if( abs(A(i,k)) > abs(A(k,k)) ) P = i;
        }

        if( abs(A(P,k)) < tol )
        cerr << "the matrix is singular" << endl;

        if( P != k ){
        swapRows(A, k, P);
        swapRows(b, k, P);
        swapRows(s, k, P);
        }
        //elimination
        for(int i = k+1; i < n; i++){
            if(A(i,k) != 0){
                double lam = A(i,k) / A(k,k);
                for(int j = k+1; j < n; j++){
                A(i,j) = A(i,j) - lam * A(k,j);
                }
                b[i] = b[i]-lam * b[k];
            }
        }

    }

    if( abs(A(n-1, n-1) ) < tol )
        cerr << "the matrix is singular" << endl;

    //back substituion
    b[n-1] = b[n-1] / A(n-1, n-1);
    for(int k = n-2; k >= 0; k--){
            for(int j = k+1; j < n; j++)
                b[k] -= A(k,j) * b[j];
            b[k] = b[k]/A(k,k);
    }

    return b;
}

void alger::swapRows(VECT& a, const int i, const int j){
    SCALAR temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void alger::swapRows(MATR& a, const int i, const int j){
SCALAR temp;
    for(uint k=0; k < a.get_numOfCols(); k++){
        temp = a(i,k);
        a(i,k) = a(j,k);
        a(j,k) = temp;
    }
}

void alger::swapCols(MATR& a, const int i, const int j){
    SCALAR temp;
    for(uint k = 0; k < a.get_numOfRows(); k++){
        temp = a(k,i);
        a(k,i) = a(k,j);
        a(k,j) = temp;
    }
}


VECT alger::func(const VECT& x, const VECT& par){
    VECT res(x.get_dim(),0);
    res[0] = pow(x[0],2) + pow(x[1],2) - 3;
    res[1] = x[0] * x[1] - 1;
    return res;
}


MATR alger::Jacobian_approx(VECT (*f) (const VECT&, const VECT&), const VECT& x, const VECT& par){
    int n = x.get_dim();
    MATR res(n, n, 0);
    VECT f0 = (*f) (x,par);
    double h = 1e-4;
    for(int j = 0; j < n; j++){
        double temp = x[j];
        x[j] = temp + h;
        VECT f1 = (*f) (x,par);
        VECT df = (f1 - f0) / h;
       // cout<<"df==";
       // df.print();
        for (int i = 0; i < n; i++)
            res(i,j) = df[i];
        x[j] = temp;
    }
    return res;
}


VECT alger::newtonRahpson(VECT (*f)(const VECT&, const VECT& ), const VECT& init_guess,const VECT& par,
                         int maxIter, double tol){
    VECT x = init_guess;
    VECT dx;
    VECT fval;
    MATR jac;
    int i;
    for( i= 0; i < maxIter; i++) {
        fval=(*f) (x,par);
        //int norm_x = x.Norm_indef();
        //fval.print();
        //cout<<fval*fval<<endl;
        if ( abs(fval * fval )< tol )
        return x;
        jac = Jacobian_approx(f, x, par);
        //jac.print();
        dx = gaussPivot(jac, -fval);
        //x.print();
        x = x + dx;
    }
    cerr << "waring: number of interations of newtonRaphson = " << i <<endl;
    return x;
}



