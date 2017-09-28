#ifndef GENERALPAREMETERS_H
#define GENERALPAREMETERS_H


class generalParemeters
{
public:
        generalParemeters();
        virtual ~generalParemeters();

    /** @brief Sets the parameters */
	void setParameters(const char*);

    void printAll() const;
    /** @brief Gives the length of the vessel */
	SCALAR get_L() const;

	/** @brief Gives the number of cells in space */
	int get_N() const;

	/** @brief Gives the thickness of the vessel */
	SCALAR get_h() const;

	/** @brief Gives the elatisity modulus */
	SCALAR get_E() const;

	/** @brief Gives the kinematic  viscocity of the blood */
	SCALAR get_nu() const;

	/** @brief Gives the density of the fluid */
	SCALAR get_rho() const;

	/** @brief Gives the reference velocity */
	SCALAR get_c0() const;

	/** @brief Gives the friction coefficient */
	SCALAR get_fric() const;

	/** @brief Gives the viscosity coefficients of the wall */
	SCALAR get_phi() const;

	/** @brief Gives the size of the cell */
	SCALAR get_dx() const;

    /** @brief Gives the solver */
	int get_solver() const;

    /** @brief Gives the order of the finite volume */
	int get_orderFV() const;

protected :

	/** thickness of the vessel */
    SCALAR h;
    /** length of the vessel */
    SCALAR L;
    /**the reference velocity */
    SCALAR c0;
    /** friction coefficient */
    SCALAR fric;
    /**elatisity modulus */
    SCALAR E;
    /**kinematic  viscocity of the blood */
    SCALAR nu;
    /** density of the fluid */
    SCALAR rho;
    /** viscosity coefficient of the vessel wall */
    SCALAR phi;

	/** Number of cells in space.*/
	int N;

	/** choice of solver*/
	int solver;

    /** order of finit volume*/
	int orderFV;

	/** Space step.*/
	SCALAR dx;


private:

	string namefile;
	string parser_output, parser_output2;

};


/** @class Parameters
 * @brief Gets parameters
 * @details
 * Class that reads the parameters, checks their values and
 * contains all the common declarations to get the values of the parameters.
 */





#endif // GENERALPAREMETERS_H
