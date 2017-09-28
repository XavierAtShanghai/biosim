
#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "generalParameters.h"
#include "vesselProperties.h"
#include "stringManage.h"

using namespace std;
using namespace stringManage;

/** @class Parser
 * @brief %Parser to read the entries
 * @details
 * Class that reads the input file writen as
 * description <variable>:: value # comment
 * and keep the values after the "::" ignoring the comments that begin with a "#".
 */


class Parser {

public:

	/** @brief Constructor */
	Parser(const char* vP);

   // void setParameters(generalParameters& );
	int setProperties(vector<vesselProperties>& ,int n);

	/** @brief Destructor */
	virtual ~Parser();

private :
	int nblines_generalPara, nblines_vesselProp; // length of data

	string * dataGeneralParameters; // tabular that contains the strings "description <variable>:: value"
	string * dataVesselProperties;
	vector<string> tableColumn;
	//size_t found;
};


#endif // PARSER_H
