#ifndef ARTERY_FV_H
#define ARTERY_FV_H

#include <artery.h>
#include <generalParameters.h>
#include <vesselProperties.h>


class artery_FV : public artery
{
    public:
        artery_FV(const vesselProperties& vP);
        virtual ~artery_FV();

        void printParameters(bool flag1=true, bool flag2=true) const;
        void stepMarch();
        void stepMarch_2order();
        void stepMarch_Euler();


    protected:

    VECT num_flux1;
    VECT num_flux2;
    VECT A_l;
    VECT Q_l;
    VECT A_r;
    VECT Q_r;
    int order;
    void reconstruct();
    void reconstruct_linear();
    void fluxRUS();
    void eval_RHS(VECT& RHS1, VECT& RHS2);
    SCALAR minmod(const SCALAR a, const SCALAR b);
    void upWinding();
    private:
};

#endif // ARTERY_FV_H
