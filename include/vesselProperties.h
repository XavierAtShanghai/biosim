#ifndef VESSELPROPERTIES_H
#define VESSELPROPERTIES_H

#include "misc.h"

/** @class Parameters
 * @brief Gets parameters
 * @details
 * Class that reads the parameters, checks their values and
 * contains all the common declarations to get the values of the parameters.
 */

class vesselProperties
{
    public:
    vesselProperties();
    //vesselProperties(Parser& fileParser);
    virtual ~vesselProperties();

    /** @brief Sets the parameters */

    void printAll(bool, bool) const;

    /** @brief Gives the length of the vessel */
	SCALAR get_L()const {return L;}
	void set_L(SCALAR _L){L=_L;}

	/** @brief Gives the number of cells in space */
	SCALAR get_A0()const  {return A0;}
	void set_A0 (SCALAR _A0){A0=_A0;}

    SCALAR get_LRef() const {return LRef;}
    void set_LRef(SCALAR _LRef) {LRef=_LRef;}

    SCALAR get_cRef() const {return cRef;}
    void set_cRef(SCALAR _cRef) {cRef=_cRef;}


	/** @brief Gives the elatisity modulus */
	SCALAR get_beta()const {return beta;}
	void set_beta(SCALAR _beta){beta=_beta;}

	/** @brief Gives the reference velocity */
	SCALAR get_Cv() const {return Cv;}
	void set_Cv(SCALAR _Cv){Cv=_Cv;}

	/** @brief Gives the friction coefficient */
	SCALAR get_Kr() const {return Kr;}
	void set_Kr(SCALAR _Kr){Kr=_Kr;}


	/** @brief Gives the size of the cell */
	int get_N() const{return N;}
	void set_N(SCALAR _N){N=_N;}

	string get_solver() const  {return solver;}
    void set_solver (const string & _solver) {solver=_solver;}

    int get_orderFV() const {return orderFV;}
    void set_orderFV (int _orderFV) {orderFV=_orderFV;}

protected :

    /** length of the vessel */
    SCALAR L;
    /**the reference velocity */
    SCALAR A0;
    /** friction coefficient */

    SCALAR LRef;
    SCALAR cRef;

    SCALAR beta;
    /**elatisity modulus */
    SCALAR Cv;
    /** viscosity coefficient of the vessel wall */
    SCALAR Kr;
	/** Number of cells in space.*/

	int N;

	string solver;

    int orderFV;

private:

	string namefile;
	string parser_output, parser_output2;
};

#endif // VESSELPROPERTIES_H
