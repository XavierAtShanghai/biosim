#include "vesselProperties.h"


vesselProperties::vesselProperties() :N(0)
{
    //ctor
}


vesselProperties::~vesselProperties()
{
    //dtor
}


void vesselProperties::printAll(bool flag1, bool flag2) const {
    if(flag1)
        printf("%8s %8s %16s %16s %16s %16s %16s \n", "L(cm)" ,  "N", "A0(cm^2)", "beta(10^6Pa/m)", "Cv(cm^2/s)","Kr", "c_ref(m/s)");
    if(flag2)
        printf("%8.2f %8d %16f %16f %16f %16f %16f \n", 1e2 * L,  N, 1e4 * A0, beta*1e-6, Cv, Kr, cRef);
}
