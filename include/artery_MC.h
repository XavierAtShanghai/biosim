#ifndef ARTERY_MC_H
#define ARTERY_MC_H

#include <artery.h>
#include "misc.h"

class artery_MC : public artery
{
    public:
        artery_MC(const vesselProperties& vP); //
        virtual ~artery_MC();

        void printParameters(bool flag1=true, bool flag2=true) const;
        void update_flux();
        void stepMarch();

    protected:

    private:
    VECT flux1;
    VECT flux2;
};

#endif // ARTERY_MC_H
