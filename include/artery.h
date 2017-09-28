#ifndef ARTERY_H
#define ARTERY_H
#include <string>
#include <misc.h>
#include <generalParameters.h>
#include <vesselProperties.h>
#include "VECT.h"
#include "triDiagMatrix.h"
using namespace std;
class artery
{
    public:
      //  artery();
        artery(const vesselProperties& vP);

        virtual ~artery();

        void set_label(int _label);
        void set_dt(SCALAR _dt);
        void set_AQ_Left(SCALAR val1, SCALAR val2);
        void set_AQ_Right(SCALAR val1, SCALAR val2);
        void set_diffusionMatrix();

        int get_label() const;
        SCALAR get_dt() const;
        VECT get_x() const;
        VECT get_A() const;
        VECT get_Q() const;
        SCALAR read_A(int pos) const;
        SCALAR read_Q(int pos) const;
        SCALAR read_P(int pos) const;
        SCALAR get_beta() const;
        int get_N() const;
        SCALAR get_A0 () const;
        SCALAR get_cRef () const;
        SCALAR get_dx () const;
        void get_betaA0 (SCALAR &, SCALAR &) const;
        void get_AQW1_Right(SCALAR &, SCALAR &, SCALAR &) const;
        void get_AQW2_Left(SCALAR &, SCALAR &, SCALAR &) const;

        void printA() const;
        void printQ() const;
        virtual void printParameters(bool flag1=true, bool flag2=true) const=0;
        void update_source();
        virtual void stepMarch()=0;

        void BC_A_inflow(SCALAR in_A);
        void BC_Q_inflow(SCALAR in_Q);
        void BC_P_inflow(SCALAR in_P);
        void BC_reflective_outlow(SCALAR reflect);
        // data mangement methods

    protected:

    //mechanical properties units m, kg, s
    SCALAR L;            // length of the vessels;
    SCALAR A0;

    SCALAR beta;
    SCALAR Kr;
    SCALAR Cv;
    SCALAR nu_s;
    SCALAR cRef;
    SCALAR dt;

    int label_num;
    enum SOLVER_SCHEME{FV=1, MC=2};

    //mesh
    int N;
	double dx;
	VECT x;

    // A and Q
	VECT A;
    VECT Q;
    VECT P;
    VECT S1;  //source of mass equation
    VECT S2;  //source of momentum equation, diffusive term not included
    VECT A_previous;    // to compute contribution of wall viscosity to pressure

    triDiagMatrix Amatrix;
    triDiagMatrix Bmatrix;

    // help functions
    SCALAR W1(const SCALAR A_t, const SCALAR Q_t)const;
    SCALAR W2(const SCALAR A_t, const SCALAR Q_t)const;
    SCALAR lambda1(const SCALAR A_t, const SCALAR Q_t)const;
    SCALAR lambda2(const SCALAR A_t, const SCALAR Q_t)const;
    SCALAR W1_interpolate() const;
    SCALAR W2_interpolate() const;

    private:

};

#endif // ARTERY_H
