#ifndef GENERALPARAMETERS_H
#define GENERALPARAMETERS_H

/** @class Parameters
 * @brief Gets parameters
 * @details
 * Class that reads the parameters, checks their values and
 * contains all the common declarations to get the values of the parameters.
 */
#include"misc.h"


class generalParameters
{
    public:

    /** @brief Constructor */
    generalParameters();

	/** @brief Destructor */
	virtual ~generalParameters();

    void printAll() const;

    /** @brief Gives the kinematic  viscocity of the blood */
	SCALAR get_nu() const;
    /** @brief Gives the density of the fluid */
	SCALAR get_rho() const;

    /** @brief Gives the solver */
	int get_solver() const;
    void set_solver(int _solver);

    /** @brief Gives the order of the finite volume */
	int get_orderFV() const;
	void set_orderFV(int _orderFV);

protected :

	/** choice of solver*/
	int solver;
    /** order of finit volume*/
	int orderFV;

private:

	string namefile;
	string parser_output, parser_output2;

};


#endif // GENERALPARAMETERS_H
