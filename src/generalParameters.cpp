#include "generalParameters.h"

generalParameters::generalParameters()
{
    //ctor
}


generalParameters::~generalParameters()
{
    //dtor
}


SCALAR generalParameters::get_nu() const {

	/**
	 * @details
	 * @return kinematic viscocity of the blood.
	 */
	return NU_FLUID;
}

SCALAR generalParameters::get_rho() const {
	/**
	 * @details
	 * @return The desity of the fluid.
	 */

	return RHO_FLUID;
}


int generalParameters::get_solver() const {

	/**
	 * @details
	 * @return The value viscosity value of the wall.
	 */

	return solver;
}

void generalParameters::set_solver(int _solver){solver=_solver;}


int generalParameters::get_orderFV() const {
	/**
	 * @details
	 * @return The value viscosity value of the wall.
	 */
	return orderFV;
}
void generalParameters::set_orderFV(int _orderFV){orderFV=_orderFV;}


void generalParameters::printAll()const {
cout<<"nu="<<NU_FLUID<<"      rho="<<RHO_FLUID<<"     slover:";
switch(solver){
    case 1:
    cout<<" MacCormack";
    break;
    case 2:
    cout<<" FV";
    cout<<"       order:"<<orderFV;
    break;
    default:
    cout<<"not defined";
    }
cout<<endl;
}
