#include "generalParemeters.h"

generalParemeters::generalParemeters()
{
    //ctor
}

generalParemeters::~generalParemeters()
{
    //dtor
}

void generalParameters::setParameters(const char* FILENAME){

	/**
	 * @details
	 * Gets all the parameters from the file FILENAME, check and affect them.
	 * The values used by FullSWOF\_1D are saved in the file parameters.dat.
	 * These values are also printed in the terminal when the code is run.
	 * @param[in] FILENAME name of the parameters file.
	 * @warning parameters.txt: ERROR: ***.
	 * @warning parameters.txt: WARNING: ***.
	 * @warning ERROR: the *** file *** does not exists in the directory Inputs.
	 * @warning Impossible to open the *** file. Verify if the directory *** exists.
	 * @note If a values cannot be affected correctly, the code will exit with failure termination code.\n
	 * If parameters.dat cannot be opened, the code will exit with failure termination code.
	 * @todo Exception should be treated.
	 */

	string path_input_directory ("./Inputs/");
	string path_output_directory ("./Outputs");
	Parser fileParser(FILENAME,NULL);

	cout << endl;

	//-----------------------------------------------------------------------------------------------------

	L = atof(fileParser.GetValue("<L>").c_str());
	if (L <= 0.0){
		cerr<< " parameters.txt: ERROR: the length of the domain must be (strictly) positive." << endl;
		exit(EXIT_FAILURE);
    }
	N = atoi(fileParser.GetValue("<N>").c_str());
	if (N < 1){
		cerr<< " parameters.txt: ERROR: the number of cells must be greater or equal to 1." << endl;
		exit(EXIT_FAILURE);
	}
	dx = L/N;
	//-----------------------------------------------------------------------------------------------------

	h = atof(fileParser.GetValue("<h>").c_str());
	if (h < 0.0){
		cerr<< " parameters.txt: ERROR: the thickness of vessel must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
    //-----------------------------------------------------------------------------------------------------

	E = atof(fileParser.GetValue("<E>").c_str());
	if (E < 0){
		cerr<< " parameters.txt: ERROR: the young's modulus must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------


	nu = atof(fileParser.GetValue("<nu>").c_str());
	if (nu <= 0.0){
		cerr<< " parameters.txt: ERROR: the density of the fluid must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}

	//-----------------------------------------------------------------------------------------------------

	c0=atof(fileParser.GetValue("c0").c_str());
	if (c0<0){
		cerr <<" parameters.txt: ERROR: the reference velocity must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------

	rho=atof(fileParser.GetValue("rho").c_str());
	if (rho<0){
		cerr <<" parameters.txt: ERROR: the density of the fluid must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------

	phi=atof(fileParser.GetValue("phi").c_str());
	if (phi<0){
		cerr <<" parameters.txt: ERROR: the viscosity of the vessel wall must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------------------

	fric=atof(fileParser.GetValue("<fric>").c_str());
	if (fric<0){	// if the friction law is empty
		cerr <<" parameters.txt: ERROR: the friction coefficients must be non-negative." << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------

    solver=atoi(fileParser.GetValue("<solver>").c_str());
	if (solver<0 || solver>2){	// if the friction law is empty
		cerr <<" parameters.txt: ERROR: sovler should be 1 or 2 " << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------
    orderFV=atoi(fileParser.GetValue("<orderFV>").c_str());
	if (orderFV<0 || orderFV>2){	// if the friction law is empty
		cerr <<" parameters.txt: ERROR: order of the finite volume is 1 or 2 " << endl;
		exit(EXIT_FAILURE);
	}
	//-----------------------------------------------------------------------------------------------------
}



SCALAR generalParameters::get_L() const {

	/**
	 * @details
	 * @return The length of the vessel.
	 */

	return L;
}

int generalParameters::get_N() const {

	/**
	 * @details
	 * @return The number of cells in space
	 */

	return N;
}

SCALAR generalParameters::get_h() const {

	/**
	 * @details
	 * @return The thickness of the vessel
	 */

	return h;
}

SCALAR generalParameters::get_E() const{

	/**
	 * @details
	 * @return The elatisity modulus
	 */

	return E;
}

SCALAR generalParameters::get_dx() const {

	/**
	 * @details
	 * @return The space step Parameters#dx.
	 */

	return dx;
}


SCALAR generalParameters::get_nu() const {

	/**
	 * @details
	 * @return kinematic viscocity of the blood.
	 */
	return nu;
}

SCALAR generalParameters::get_rho() const {

	/**
	 * @details
	 * @return The desity of the fluid.
	 */

	return rho;
}

SCALAR generalParameters::get_c0() const {

	/**
	 * @details
	 * @return The value reference velocity.
	 */

	return c0;
}

SCALAR generalParameters::get_fric() const {

	/**
	 * @details
	 * @return The value of friction coefficient.
	 */

	return fric;
}

SCALAR generalParameters::get_phi() const {

	/**
	 * @details
	 * @return The value viscosity value of the wall.
	 */

	return phi;
}

int generalParameters::get_solver() const {

	/**
	 * @details
	 * @return The value viscosity value of the wall.
	 */

	return solver;
}

int generalParameters::get_orderFV() const {

	/**
	 * @details
	 * @return The value viscosity value of the wall.
	 */
	return orderFV;
}

void generalParameters::printAll()const {
cout<<"-----------the parameters of the vessel---start----------"<<endl;
cout<<"h="<<h<<endl;
cout<<"L="<<L<<endl;
cout<<"c0="<<c0<<endl;
cout<<"fric="<<fric<<endl;
cout<<"E="<<E<<endl;
cout<<"nu="<<nu<<endl;
cout<<"rho="<<rho<<endl;
cout<<"phi="<<phi<<endl;
cout<<"N="<<N<<endl;
cout<<"dx="<<dx<<endl;
cout<<"-----------the parameters of the vessel---end----------"<<endl;
}
