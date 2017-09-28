#include "artery.h"

//artery::artery(){}

artery::artery(const vesselProperties& vP):
L(vP.get_L()), A0(vP.get_A0()),
beta(vP.get_beta()), Kr(vP.get_Kr()), Cv(vP.get_Cv()),
cRef( vP.get_cRef() ),
N(vP.get_N()),
x(N+1), A(N+1),
Q(N+1,0), P(N+1,0), S1(N+1,0), S2(N+1,0),
Amatrix(N+1), Bmatrix(N+1)
{
    //mechanical properties units m, kg, s
    dx = L / N;

    for(int i = 0; i < N+1; i++) {
        x[i] = dx * i;
        A[i] = A0;
        Q[i] = 0.0;  //400 * ( sin( 2 * PI * ( (x[i] / L) - 0.25) ) > 0?  sin( 2 * PI * ( (x[i] / L)-0.25) ):0);
    }
    A_previous=A;
    nu_s=Cv * RHO_FLUID / A0;
}

artery::~artery()
{

    //dtor
}

void artery::set_label(int _label) {
    label_num = _label;
}

void artery::set_dt(SCALAR _dt) {
    dt = _dt;
}

void artery::set_AQ_Left(SCALAR val1, SCALAR val2) {
    A[0] = val1;
    Q[0] = val2;
}

void artery::set_AQ_Right(SCALAR val1, SCALAR val2) {
    A[N] = val1;
    Q[N] = val2;
}

void artery::set_diffusionMatrix() {
    double  r = dt * Cv / (2 * dx * dx);
    double  diagA =  1 + 2 * r;
    double  diagB =  1 - 2 * r;

    for(int i = 0; i < N+1; i++) {
        Amatrix.set_b_at(i,diagA);
        Bmatrix.set_b_at(i,diagB);
    }

    // homogeneous Neumann B.C.

    for(int i = 0; i < N ; i++) {
        Amatrix.set_a_at( i, -r);
        Amatrix.set_c_at( i, -r);

        Bmatrix.set_a_at( i, r);
        Bmatrix.set_c_at( i, r);
    }

    Amatrix.set_c_at( 0, -2 * r);
    Amatrix.set_a_at( N - 1, -2 * r);

    Bmatrix.set_c_at( 0, 2 * r);
    Bmatrix.set_a_at( N - 1 , 2 * r);

}

int artery::get_label() const {
     return label_num;
}

SCALAR artery::get_dt() const {
     return dt;
}

void artery::update_source() {
    for(int i = 0; i < N+1; i++) {
    //S1[i]=0;
    S2[i] = -Kr * Q[i] / A[i];
    }
}

VECT artery::get_x() const {
    return x;
}

VECT artery::get_A() const {
    return A;
}

VECT artery::get_Q() const {
    return Q;
}

SCALAR artery::read_A (int pos) const {
    return A[pos];
}

SCALAR artery::read_Q(int pos) const {
    return Q[pos];
}

SCALAR artery::read_P(int pos) const {
    return P[pos];
}

SCALAR artery::get_beta() const {
    return beta;
}

int artery::get_N() const {
    return N;
}

SCALAR artery::get_A0 () const {
    return A0;
}

SCALAR artery::get_cRef () const {
    return cRef;
}
SCALAR artery::get_dx () const {
    return dx;
}

void artery::get_betaA0 (SCALAR & bt,SCALAR &a0) const {
    bt = beta;
    a0 = A0;
}

void artery::get_AQW1_Right(SCALAR & Av, SCALAR &Qv, SCALAR &W1v) const {
    Av = A[N]; Qv = Q[N];
    W1v = W1_interpolate();
}

void artery::get_AQW2_Left(SCALAR& Av, SCALAR& Qv, SCALAR& W2v) const {
    Av = A[0]; Qv=Q[0];
    W2v = W2_interpolate();
}

void artery::printA() const {
    A.print();
}
void artery::printQ() const {
    Q.print();
}


void artery::BC_A_inflow(SCALAR in_A) {
    SCALAR W2_nplus1 = W2_interpolate();
    A[0] = in_A;
    Q[0] = (W2_nplus1 + 4.0 * sqrt( beta / 2.0 / RHO_FLUID * sqrt(in_A) ) ) * in_A;
}


void artery::BC_Q_inflow(SCALAR in_Q) {
    SCALAR W2_nplus1 = W2_interpolate();
    A[0] = pow( RHO_FLUID / beta, 2.0) * pow( in_Q / A[0] - W2_nplus1, 4.0) / 64.0 ;
    Q[0] = in_Q;
}

void artery::BC_P_inflow(SCALAR in_P) {
    SCALAR in_A=pow( (in_P/beta/100.0+sqrt(A0) ), 2.0 );  // Unit of pressure= pascal. since  [beta]=M/(TL^2)  kg/(s*cm^2) --> kg/((s(m*cm) )*100 ---> 100*pascal/cm
    BC_A_inflow(in_A);
}



void artery::BC_reflective_outlow(SCALAR reflect) {

    SCALAR W1_nplus1 = W1_interpolate();
    SCALAR W2_0 = W2(A0,0);
    SCALAR W1_0 = W1(A0,0);
    SCALAR W2_nplus1 = W2_0-reflect*(W1_nplus1-W1_0);
    A[N] = pow(W1_nplus1 - W2_nplus1, 4.0) / 1024.0 * pow( RHO_FLUID / beta, 2.0);
    Q[N] = A[N] * 0.5 * (W1_nplus1 + W2_nplus1);
}

// help functions
SCALAR artery::W1(const SCALAR A_t, const SCALAR Q_t) const {
    return Q_t / A_t + 4.0 * sqrt( beta / 2.0 / RHO_FLUID * sqrt(A_t));
}

SCALAR artery::W2(const SCALAR A_t, const SCALAR Q_t) const {
    return Q_t / A_t - 4.0 * sqrt( beta / 2.0 / RHO_FLUID * sqrt(A_t) );
}

SCALAR artery::lambda1(const SCALAR A_t, const SCALAR Q_t)const {
    return ALPHA*Q_t / A_t + sqrt( beta / 2.0 / RHO_FLUID * sqrt(A_t) + ALPHA*(ALPHA-1)* pow( (Q_t / A_t),2 ) );
}

SCALAR artery::lambda2(const SCALAR A_t, const SCALAR Q_t) const {
    return ALPHA*Q_t /A_t - sqrt(beta / 2.0 / RHO_FLUID * sqrt(A_t)+ ALPHA*(ALPHA-1)* pow( (Q_t / A_t), 2 ) );
}

SCALAR artery::W1_interpolate() const {
    SCALAR Lam1 = lambda1(A[N],Q[N]);
    SCALAR proportion = Lam1 * dt / dx;
    assert ( proportion < 1 && proportion > 0);
    SCALAR W1_N = W1( A[N], Q[N]);
    SCALAR W1_Nminus1 = W1(A[N-1], Q[N-1]);
    return proportion * W1_Nminus1 + (1 - proportion) * W1_N;
}

SCALAR artery::W2_interpolate() const {

    SCALAR Lam2 = lambda2(A[0],Q[0]);
    SCALAR proportion = -Lam2 * dt / dx;
    assert( proportion < 1 && proportion > 0 );
    SCALAR W2_0 = W2(A[0], Q[0]);
    SCALAR W2_1 = W2(A[1],Q[1]);
    return (1 - proportion) * W2_0 + proportion * W2_1;
}

