#include "parser.h"

Parser::Parser(const char* vP){

	/**
	 * @details
	 * Constructor: reads the input parameter and copy the data in a tabular.
	 * @param[in] FILENAME name of the paramters file.
	 * @warning Impossible to open the *** file.
	 * @note If the parameters file cannot be opened, the code will exit with failure termination code.
	 * @todo Exception should be treated.
	 */

	int i=0;
	int j=0;
    size_t found;

	string ch;   // store temporarily read strings

	nblines_vesselProp=0;

    ifstream entries(vP,ios::in);
	if (!entries){
		cerr << "Impossible to open the " << vP <<" file\n";
		exit(EXIT_FAILURE);
	}

	// the length of data is fixed equal to the number of lines of the parameter file
	// (even if the comment lines should be eliminated)
	// Find the number of lines of the parameters file

	while (!entries.eof()){			// while the end of the file is not attained
		getline (entries, ch);		// read a line
		nblines_vesselProp ++;					// nblines is the number of lines of the parameter file
	}

	entries.clear();
	entries.seekg(0,ios::beg);		// the file will be read again from the beginning

    dataVesselProperties= new string[nblines_vesselProp];

	// data is a tabular where the useful lines of the input parameter are copied

	while (!entries.eof()){
		getline (entries, ch);		// the whole line is copied in the string ch
		found = ch.find("#");
		j = int(found);				// j is the position of the first #
		if (ch!="" && j!=0){			// if the line is not empty and if it is not a comment line (which begins with a #)
			if (j>0){					// if there is a comment (which begins with a #) after the datas
				ch.erase (ch.begin()+j, ch.end());			// erase the comment
			}
			dataVesselProperties[i] = ch;
			i++;
		}
	}

	nblines_vesselProp=i;					// number of non-empty lines of data
	tableColumn=split(dataVesselProperties[0],",");

	entries.close();

}

Parser::~Parser(){
   delete [] dataVesselProperties;
}


int Parser::setProperties(vector<vesselProperties>& _vP, int n){

int n_data=nblines_vesselProp-1;
if(n>n_data){
cerr<<"error of vessel properties"<<endl;
cout<<"n="<<nblines_vesselProp-1<<endl;
cout<<"not enough proptertiy entreis are provided."<<n<<endl;
exit(1);
}


int L_pos=findPosition_inTable(tableColumn,"<Length>");
int A0_pos=findPosition_inTable(tableColumn,"<A0>");

int beta_pos=findPosition_inTable(tableColumn,"<beta>");
int fric_pos=findPosition_inTable(tableColumn,"<fric>");
int Cv_pos=findPosition_inTable(tableColumn,"<Cv>");

int solver_pos=findPosition_inTable(tableColumn,"<solver>");
int order_pos=findPosition_inTable(tableColumn,"<order>");
int N_pos = findPosition_inTable(tableColumn,"N");


vector<string> value;


double non_dim_dx=10000000;

for( int i=0;i<n; i++){

    value=split(dataVesselProperties[i+1],",");
    _vP[i].set_Kr( NU_FLUID * PI * atof( value[fric_pos].c_str()) );
    _vP[i].set_Cv(1e4* atof(value[Cv_pos].c_str()) );  // convert from m/s to cm/s

    _vP[i].set_solver( value[solver_pos] );
    _vP[i].set_orderFV( atoi((value[order_pos].c_str())) );

    double L= atof(value[L_pos].c_str());
     _vP[i].set_L(L);
    double A0= atof(value[A0_pos].c_str());
    _vP[i].set_A0(A0);
    double beta =1e4 * atof(value[beta_pos].c_str());   // because [pressure]= M/(T L), dimension of beta is: [beta] = M/(T L^2)   1e6*1e-2
    _vP[i].set_beta(beta);

    double cRef = sqrt( 0.5 * beta / RHO_FLUID * sqrt(A0));
    _vP[i].set_cRef( cRef );
    double LRef = L / cRef;
    _vP[i].set_LRef(LRef);

    if( non_dim_dx > LRef)
    non_dim_dx=LRef;
  }

if ( N_pos == -1){
    for (int i = 0; i < n; i++){
    int N= _vP[i].get_LRef() / non_dim_dx * 2;
    _vP[i].set_N( N + 1 );
    }
}
else {
    for (int i = 0; i < n; i++){
    value = split(dataVesselProperties[i+1],",");
    _vP[i].set_N( atoi((value[N_pos].c_str())) );
    }
}
  return 0;
}




