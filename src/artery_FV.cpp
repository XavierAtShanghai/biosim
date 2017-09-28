#include "artery_FV.h"

artery_FV::artery_FV(const vesselProperties& vP):artery(vP),
num_flux1(N+1,0), num_flux2(N+1,0), A_l(N+1,0),Q_l(N+1,0),A_r(N+1,0),Q_r(N+1,0), order(vP.get_orderFV()) {
    //ctor
}

artery_FV::~artery_FV()
{
    //dtor
}

void artery_FV::printParameters(bool flag1, bool flag2)const {

if(flag1)
     printf("%8s %16s %8s %16s %16s %16s %16s %8s %8s %12s %12s\n", "L(cm)" , "dx(cm)", "N", "A0(cm^2)", "beta(10^6Pa/cm)", "Cv(10^4cm^2/s)", "Kr(cm^2/s)", "Solver", "order" ,"c_ref(cm/s)","dt");
if(flag2)
     printf("%8.2f %16f %8d %16f %16f %16f %16f %8s %8d %12f %12f\n", L, dx, N,  A0, beta * 1e-4, Cv *1e-4, Kr, "FV", order, cRef,dt);
}

void artery_FV::stepMarch() {
    switch(order) {
    case 1:
        stepMarch_Euler();
        break;
    case 2:
        stepMarch_2order();
        break;
    default:
        cerr<<"order choosen not exist"<<endl;
    }
}

void artery_FV::stepMarch_Euler() {

    double tx=dt/dx;
     reconstruct();
     fluxRUS();

    A_previous=A;
     for(int i = 1; i < N; i++) {
           A[i] = A[i] - tx * (num_flux1[i] - num_flux1[i-1]);
           Q[i] = Q[i] - tx * (num_flux2[i] - num_flux2[i-1]);
        }


    if ( abs(Cv) > 0){
        Q = Amatrix.Thomas_solver( Bmatrix * Q );
        for(int i = 0; i < N+1; i++){
            P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100 + nu_s*(A[i]-A_previous[i])/dt ;   // Unit of pressure= pascal. since  [beta]=M/(TL^2)  kg/(s*cm^2) --> kg/((s(m*cm) )*100 ---> 100*pascal/cm
          }
       }
    else{
        for(int i = 0; i < N+1; i++){
          P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100;
          }
       }

 }

void artery_FV::stepMarch_2order(){

     VECT RHS1(N+1,0);
     VECT RHS2(N+1,0);
     VECT RHS1_star(N+1,0);
     VECT RHS2_star(N+1,0);
     eval_RHS(RHS1,RHS2);

     reconstruct_linear();
     fluxRUS();

     RHS1_star=RHS1;
     RHS2_star=RHS2;
     eval_RHS(RHS1,RHS2);

     A_previous=A;

     for(int i=1; i<N;i++){
        A[i] = A[i] + dt * (1.5 * RHS1[i] - 0.5 * RHS1_star[i]);
        Q[i] = Q[i] + dt* (1.5 * RHS2[i] - 0.5 * RHS2_star[i]);
        }

      for(int i = 0; i < N+1; i++){
        P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100;
       }

    if ( abs(Cv) > 0){
        Q = Amatrix.Thomas_solver( Bmatrix * Q );
        for(int i = 0; i < N+1; i++){
            P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100 + nu_s*(A[i]-A_previous[i])/dt ;
            }
       }
    else{
        for(int i = 0; i < N+1; i++){
          P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100;
          }
       }
}

void artery_FV::reconstruct() {
    for(int i = 0; i < N+1; i++) {
          A_l[i]=A[i];
          Q_l[i]=Q[i];
          A_r[i]=A[i];
          Q_r[i]=Q[i];
        }
}

void artery_FV::reconstruct_linear() {
    VECT dA(N+1,0);
    VECT dQ(N+1,0);
    double dA_fw;  //forward difference
    double dQ_fw;
    double dA_bw;  //backward difference
    double dQ_bw;

    dA[0]=A[1]-A[0];
    dA[N]=A[N]-A[N-1];

    dQ[0]=Q[1]-Q[0];
    dQ[N]=Q[N]-Q[N-1];

    for (int i = 1; i < N; i++) {
        dA_fw = A[i+1] - A[i];
        dA_bw = A[i] - A[i-1];
        dA[i] = minmod(dA_fw,dA_bw);

        dQ_fw = Q[i+1] - Q[i];
        dQ_bw = Q[i] - Q[i-1];
        dQ[i] = minmod(dQ_fw,dQ_bw);
    }

      for(int i = 0; i < N+1; i++) {
         A_l[i] = A[i] - 0.5 * dA[i];
         Q_l[i] = Q[i] - 0.5 * dQ[i];
         A_r[i] = A[i] + 0.5 * dA[i];
         Q_r[i] = Q[i] + 0.5 * dQ[i];
      }
 }

void artery_FV::eval_RHS(VECT& RHS1, VECT& RHS2) {
    update_source();
    for(int i = 1; i < N; i++) {
        RHS1[i] = -(num_flux1[i]-num_flux1[i-1])/dx+S1[i];
        RHS2[i] = -(num_flux2[i]-num_flux2[i-1])/dx+S2[i];
    }
}

void artery_FV::fluxRUS() {
     for(int i = 0; i < N; i++) {
     double a = lambda1(A_r[i],Q_r[i]);
     double b = lambda1(A_l[i+1],Q_l[i+1]);
     double c = MAX(a,b);

     num_flux1[i] = (Q_l[i+1] + Q_r[i]) * 0.5-c * (A_l[i+1]-A_r[i]) * 0.5;
     num_flux2[i] = (Q_l[i+1] * Q_l[i+1] / A_l[i+1] + beta / 3 / RHO_FLUID * pow(A_l[i+1],1.5)
      + Q_r[i] * Q_r[i] / A_r[i]+beta / 3 / RHO_FLUID * pow(A_r[i],1.5))  * 0.5 - c * (Q_l[i+1]-Q_r[i]) * 0.5;
     }

}

SCALAR artery_FV::minmod(const SCALAR a, const SCALAR b) {
    if (a > 0 && b > 0)
        return min(a,b);
    else if (a < 0 && b < 0 )
        return max(a,b);
    else
        return 0;
}

