#include "artery_MC.h"

artery_MC::artery_MC(const vesselProperties& vP): artery(vP),
flux1(N+1,0),flux2(N+1,0)//
{
    update_flux();
}

artery_MC::~artery_MC()
{

}

void artery_MC::printParameters(bool flag1, bool flag2) const {
    if(flag1)
        printf("%8s %16s %8s %16s %16s %16s %16s %8s %16s %16s\n","L(cm)" , "dx(cm)", "N", "A0(cm^2)", "beta(10^6Pa/cm)", "Cv(10^4cm^2/s)", "Kr(cm^2/s)", "Solver", " c_ref(cm/s)", "dt");
    if(flag2)
        printf("%8.2f %16f %8d %16f %16f %16f %16f %8s %16f %16f\n", L, dx, N, A0, beta*1e-4, Cv*1e-4, Kr, "MC", cRef, dt);
}

void artery_MC::update_flux()
{
    for(int i = 0; i < N+1; i++) {
        flux1[i] = Q[i];
        flux2[i] = ALPHA * Q[i] * Q[i] / A[i] + beta / 3.0 / RHO_FLUID * A[i] * sqrt(A[i]);
    }
}

void artery_MC::stepMarch()
{
    double tx=dt/dx;

    VECT A_temp(N+1,0);
    VECT Q_temp(N+1,0);


     for(int i=0;i<N+1;i++){
     A_temp[i]=A[i];
     Q_temp[i]=Q[i];
     }

     update_flux();
     update_source();

     A_previous=A;
     for(int i=1;i<N;i++){
         A[i] = A[i] - tx * (flux1[i+1]-flux1[i]);
         Q[i] = Q[i] - tx * (flux2[i+1]-flux2[i])+dt*S2[i];
     }

     update_flux();
     update_source();
     for(int i=1;i<N;i++){
      A[i]=0.5*(A_temp[i]+A[i])-0.5*tx*(flux1[i]-flux1[i-1]);
      Q[i]=0.5*(Q_temp[i]+Q[i])-0.5*tx*(flux2[i]-flux2[i-1])+0.5*dt*S2[i];
      }


    if ( abs(Cv) > 0){
        Q = Amatrix.Thomas_solver( Bmatrix * Q );
        for(int i = 0; i < N+1; i++){
            P[i] = beta * (sqrt(A[i]) - sqrt(A0)) * 100 + nu_s* (A[i]-A_previous[i]) / dt ;   // Unit of pressure= pascal. since  [beta]=M/(TL^2)  kg/(s*cm^2) --> kg/((s(m*cm) )*100 ---> 100*pascal/cm
          }
       }
    else{
        for(int i = 0; i < N+1; i++){
          P[i] = beta * ( sqrt(A[i]) - sqrt(A0) ) * 100;
          }
       }
}
