#include "network_arts_conjuncs.h"

network_arts_conjuncs::network_arts_conjuncs(const string& paraFolder)
{
    set_DAGFile(paraFolder+"/DAG.csv");
    set_paraFile(paraFolder+"/systemic_network.csv");
    set_reflecFile(paraFolder+"/leavesReflect.csv");
    set_outputFile(paraFolder+"/output.csv");
	set_inputFile(paraFolder+"/input.csv");
	set_timeSetupFile(paraFolder+"/timeSetup.csv");

	readDAG(DAGFile.c_str());
    readInput(inputFile.c_str());
    readTimeSetup(timeSetupFile.c_str());

    Parser fileParser(paraFile.c_str());
    ves_pros.resize(num_arteries);
    fileParser.setProperties(ves_pros, num_arteries);

    arts.resize(num_arteries,0);     // contains pointers to artery
    for (int i = 0; i < num_arteries; i++){
        appointSolver(arts[i], ves_pros[i]); //choiceSolver::
        arts[i]->set_label(i);
        arts[i]->set_dt(t_step);
        arts[i]->set_diffusionMatrix();
        }

    conjs.resize(num_conjuncs);

    for(int i=0; i<num_conjuncs; i++){
        conjs[i]= new conjunction();
        }

    for(int i = 0; i < num_arteries; i++){
        conjs[DAG(i,0)]->add_daughterArtery(arts[i]);
        conjs[DAG(i,1)]->add_parentArtery(arts[i]);
        }

    for(int i=0; i<num_conjuncs; i++){
        if ( !conjs[i]->set_root_leaves() )
            cerr << " the unproperly set conjunction is " << i <<endl;
        }

    readOutput(outputFile.c_str());
    readLeavesRefelcts(reflecFile.c_str());
    checkTimeStep();
}


network_arts_conjuncs::~network_arts_conjuncs()
{
    for(int i=0; i<num_arteries; i++)
        delete arts[i];
    for(int i=0; i<num_conjuncs; i++){
        delete conjs[i];
        }

    //dtor
}

void network_arts_conjuncs::readDAG(const char* _DAG){

	string ch;   // store temporarily read strings

	vector<string> str_DAG;
	num_arteries=0;

	ifstream entries(_DAG,ios::in);
	if (!entries){
		cerr << "Impossible to open the DAG file: " << _DAG <<"\n";
		exit(EXIT_FAILURE);
	}
//
	while (!entries.eof()){			// while the end of the file is not attained
		getline (entries, ch);		// read a line
		if(ch=="")
            break;
		str_DAG.push_back(ch);
		num_arteries ++;					// nblines is the number of lines of the parameter file
	}
	entries.close();


    DAG=matrix<int>(num_arteries,2);

    for(unsigned int i=0; i<str_DAG.size(); i++){
        vector<string> temp=split(str_DAG[i],",");
        DAG(i,0)=atoi(temp[0].c_str());
        DAG(i,1)=atoi(temp[1].c_str());
    }
    num_conjuncs=DAG.get_max_element()+1;
}

void network_arts_conjuncs::readLeavesRefelcts(const char* _leavesRef){

	string ch;   // store temporarily read strings
    vector<string> reflecs_data;
    ifstream entries(_leavesRef,ios::in);
	if (!entries){
		cerr << "Impossible to open the " << _leavesRef <<" file\n";
		exit(EXIT_FAILURE);
	}

	while (!entries.eof()){
		getline (entries, ch);		// the whole line is copied in the string ch
		reflecs_data.push_back(ch);
		}
	entries.close();

    int n_leaves=0;
    for(uint i=0; i<conjs.size(); i++){
        if( conjs[i]->isLeaf() ){
        vector<string> value;
        value = split( reflecs_data[n_leaves], ",");
        double refCeff = atof( value[1].c_str() );
        conjs[i]->set_reflective_coeff( refCeff );
        n_leaves++;

        if ( i != unsigned( atoi(value[0].c_str()) ) )
        cerr << " the leaf " << i << " is not matched with "<< atoi(value[0].c_str()) << " in leavesReflect.csv "<<endl;
        }
    }
}


void network_arts_conjuncs::readTimeSetup(const char* _timeSetup){
     ifstream entries(_timeSetup,ios::in);
	if (!entries){
		cerr << "Impossible to open the time setup file: " << _timeSetup <<"\n";
		exit(EXIT_FAILURE);
	}
    string tableTitle, tableRow;
    getline(entries,tableTitle);
    getline(entries,tableRow);
    vector<string> tableTitle_seperate=split(tableTitle,",");
    vector<string> tableRow_seperate=split(tableRow,",");

    int pos_temp=findPosition_inTable(tableTitle_seperate,"<t_step>");
    t_step=atof(tableRow_seperate[pos_temp].c_str());
    pos_temp=findPosition_inTable(tableTitle_seperate,"<t_final>");
    t_final=atof(tableRow_seperate[pos_temp].c_str());
    pos_temp=findPosition_inTable(tableTitle_seperate,"<record_start>");
    recordStart=atof(tableRow_seperate[pos_temp].c_str());
    pos_temp=findPosition_inTable(tableTitle_seperate,"<record_end>");
    recordEnd=atof(tableRow_seperate[pos_temp].c_str());

    if( recordStart<0 || recordEnd>t_final || recordStart> recordEnd){
    cerr<<" recording interval not properly assigned"<<endl;
    exit(1);
    }

    entries.close();
}

void network_arts_conjuncs::readInput(const char* _inputFile){
   ifstream entries(_inputFile,ios::in);
	if (!entries){
		cerr << "Impossible to open the time setup file " << _inputFile <<"\n";
		exit(EXIT_FAILURE);
	}

    string tableRow;
	getline(entries, tableRow);
	vector<string> tableRow_seperate=split(tableRow,",");
    if (tableRow_seperate[1].find("<Q_Input>")!=string::npos )
    input_type_net=Qinput;
    else if (tableRow_seperate[1].find("<P_Input>" )!=string::npos )
    input_type_net=Pinput;
    else if (tableRow_seperate[1].find("<A_Input>" )!=string::npos )
    input_type_net=Ainput;
    else {
        cerr<<"please specify the input type: <Q_Input>, <P_Input> or <A_Input>"<<endl;
        exit(1);
    }

	while (!entries.eof()){
	getline(entries, tableRow);
	if (tableRow=="")
        break;
	vector<string> tableRow_seperate=split(tableRow,",");
    input_net.push_back( atof(tableRow_seperate[1].c_str()) );
	}
    entries.close();
}

void network_arts_conjuncs::readOutput(const char* _outputFile){
ifstream entries(_outputFile,ios::in);
	if (!entries){
		cerr << "readOutput: Impossible to open the output set up file " << _outputFile <<"\n";
		exit(EXIT_FAILURE);
	}

    string tableRow;

	while (!entries.eof()){
	getline(entries, tableRow);
    if(tableRow.find("#")!=string::npos)
        continue;
	if (tableRow=="")
        break;
    vector<string> tableRow_seperate=split(tableRow,",");
    int art_num_temp=atoi(tableRow_seperate[0].c_str());
    if (art_num_temp>=num_arteries){
        cerr<<"readOutput: number of arteries is " <<num_arteries<< " the recorded artery cannot be " <<art_num_temp<<endl;
        exit(1);
        }
    artery_record.push_back( atoi(tableRow_seperate[0].c_str()) );
    int node_num_temp=atoi(tableRow_seperate[1].c_str());

    if (node_num_temp>=arts[art_num_temp]->get_N()){
        cerr<<"readOutput: number of nodes at artery " <<art_num_temp<< " is " << arts[art_num_temp]->get_N()<< ", the recorded nodes cannot be " <<node_num_temp<<endl;
        exit(1);
        }
    pos_record.push_back( atoi(tableRow_seperate[1].c_str()) );
	}
    entries.close();

}


 void network_arts_conjuncs::run(){// (const double dt, const double t_final, double recordStart, double recordEnd){

    int Nbr_timeStep = t_final / t_step;
    if (Nbr_timeStep > input_net.size() || Nbr_timeStep < input_net.size() -1 ){
    cerr << "network_arts_conjuncs::run_openMP: the size of input signal is " << input_net.size() << " the expected number of time steps is " << Nbr_timeStep << endl;
    cerr << "please may sure the time step in timeSetup file and input file are the same" << endl;
    exit(1);
    }
    cout << "number of time steps= " << Nbr_timeStep << endl;


    int storeStep = 100;
    int Nbr_stored = (recordEnd-recordStart)/t_step/storeStep-1;

    vector< vector<float> > histA(artery_record.size()+1 );
    vector< vector<float> > histQ(artery_record.size()+1 );
    vector< vector<float> > histP(artery_record.size()+1 );


    int n_stored = 0;  // for the recorded points
    printf("progress: ");
    int prin = 0;
    for (int n=0;n < Nbr_timeStep; n++){

          if ( int(0.05* prin * Nbr_timeStep) == n){
            printf("%5.2f%% ", 100*float(n)/Nbr_timeStep);
            fflush(stdout);
            prin++;
           }
        for(int i = 0; i < num_conjuncs; i++){
           if(conjs[i]->isRoot()){
                switch (input_type_net){
                    case Ainput:
                    conjs[i]->BC_A_inflow(input_net[n]);
                    break;
                    case Qinput:
                    conjs[i]->BC_Q_inflow(input_net[n]);
                    break;
                    case Pinput:
                    conjs[i]->BC_P_inflow(input_net[n]);
                    break;
                 }
           }
            else if(conjs[i]->isLeaf()){
                conjs[i]->BC_outflow();}
            else if(conjs[i]->isOrphan())
                continue;
            else {
                conjs[i]->stepMarch(); }
            }

       for(int i=0; i<num_arteries; i++) {
            arts[i]->stepMarch();
            }

        if(n%storeStep==0 && t_step*n>=recordStart && n_stored<Nbr_stored ){

            histA[0].push_back(n*t_step);
            histQ[0].push_back(n*t_step);
            histP[0].push_back(n*t_step);
            for(uint i=0; i<artery_record.size(); i++){
                histA[i+1].push_back( arts[artery_record[i]]->read_A(pos_record[i]) );
                histQ[i+1].push_back( arts[artery_record[i]]->read_Q(pos_record[i]) );
                histP[i+1].push_back( arts[artery_record[i]]->read_P(pos_record[i]) );
            }
         }

    }
    cout<<"computation completed. writing....."<<endl;
    writeHist( (dataFolder + '/' + Adatafile).c_str(), histA);
    writeHist( (dataFolder + '/' + Qdatafile).c_str(), histQ);
    writeHist( (dataFolder + '/' + Pdatafile).c_str(), histP);


}

void network_arts_conjuncs::run_openMP(){ //(const double dt, const double t_final, double recordStart, double recordEnd){

    int Nbr_timeStep = t_final / t_step;
    if (Nbr_timeStep > input_net.size() || Nbr_timeStep < input_net.size() -1 ){
    cerr << "network_arts_conjuncs::run_openMP: the size of input signal is " << input_net.size() << " the expected number of time steps is " << Nbr_timeStep << endl;
    cerr << "please may sure the time step in timeSetup file and input file are the same" << endl;
    exit(1);
    }
    cout << "number of time steps= " << Nbr_timeStep << endl;



    int storeStep = 100;
    int Nbr_stored = (recordEnd-recordStart)/t_step/storeStep-1;
    vector< vector<float> > histA(artery_record.size()+1 );
    vector< vector<float> > histQ(artery_record.size()+1 );
    vector< vector<float> > histP(artery_record.size()+1 );

    int n_stored=0;  // for the recorded points
    int prin = 0;     // count of progress  0.05*print

    char* p_OMP_NUM = NULL;
    p_OMP_NUM = getenv ("OMP_NUM_THREADS");
    if (p_OMP_NUM!=NULL){
        int omp_num = atoi(p_OMP_NUM);
        if( omp_num > arts.size() ){
            omp_set_num_threads(arts.size());
        }
    }


        #pragma omp parallel
        {
        int n_streads=omp_get_num_threads();

        #pragma omp single nowait
        {
        printf("number of threads %d \n", n_streads);
        printf("progress:  ");
        fflush(stdout);
        }

        // for the conjunctions
        int iStart1, iEnd1;
        int chunk1=ceil(num_conjuncs/float(n_streads) );

        int myID=omp_get_thread_num();
        iStart1=myID*chunk1;

        if( (myID+1)*chunk1-1 < num_conjuncs-1 )
            iEnd1=(myID+1)*chunk1-1;
        else
            iEnd1=num_conjuncs-1;

        // for the arteries
        int chunk2=ceil(num_arteries/float(n_streads));
        int iStart2=myID*chunk2;
        int iEnd2;
        if( (myID+1)*chunk2-1 < num_arteries-1 )
            iEnd2=(myID+1)*chunk2-1;
        else
            iEnd2=num_arteries-1;

        vector <int > i_artery_record;
        vector <int > i_pos_record;
        vector <int > i_record_loc;

        for(uint i=0; i<artery_record.size(); i++){
          if (artery_record[i] >= iStart2 && artery_record[i] <= iEnd2 ) {
            i_artery_record.push_back(artery_record[i]);
            i_pos_record.push_back(pos_record[i]);
            i_record_loc.push_back(i);
           }
        }

        for (int n=0;n<Nbr_timeStep; n++){
         #pragma omp single nowait
         {
            if ( int(0.05* prin * Nbr_timeStep) == n) {
            printf("%5.2f%% ", 100*float(n)/Nbr_timeStep);
            fflush(stdout);
            prin++;
            }
         }
        for(int i=iStart1; i<=iEnd1;i++){
            if(conjs[i]->isRoot()){
                switch (input_type_net){
                    case Ainput:
                    conjs[i]->BC_A_inflow(input_net[n]);
                    break;
                    case Qinput:
                    conjs[i]->BC_Q_inflow(input_net[n]);
                    break;
                    case Pinput:
                    conjs[i]->BC_P_inflow(input_net[n]);
                    break;
                    }
             }
            else if(conjs[i]->isLeaf())
                conjs[i]->BC_outflow();
            else if(conjs[i]->isOrphan())
                continue;
            else
               conjs[i]->stepMarch();
          }
        #pragma omp barrier

        for(int i=iStart2; i<=iEnd2; i++){
            arts[i]->stepMarch();
            }

        if(n%storeStep==0 && t_step*n>=recordStart && n_stored<Nbr_stored ){
            #pragma omp single nowait
            {
            histA[0].push_back(n*t_step);
            histQ[0].push_back(n*t_step);
            histP[0].push_back(n*t_step);
            }


            for(int i=0; i<i_artery_record.size(); i++){
               int ID_art=i_artery_record[i];
               histA[i_record_loc[i]+1].push_back( arts[ID_art]->read_A(i_pos_record[i]) );
               histQ[i_record_loc[i]+1].push_back( arts[ID_art]->read_Q(i_pos_record[i]) );
               histP[i_record_loc[i]+1].push_back( arts[ID_art]->read_P(i_pos_record[i]) );
         }
         }
        }
    }  //pragma parallel end

    cout<<"computation completed. writing....."<<endl;
    writeHist( (dataFolder+'/'+Adatafile).c_str(),histA);
    writeHist( (dataFolder+'/'+Qdatafile).c_str(),histQ);
    writeHist( (dataFolder+'/'+Pdatafile).c_str(),histP);

}

void network_arts_conjuncs::print()const{

    printf(" number of arteries = %-8d \t number of conjuncs = %-8d \n", num_arteries ,num_conjuncs);
	printf(" Final time = %-8f  \t", t_final);
	printf(" time step = %-8f \t", t_step);
	printf(" Number of time steps = %-8d \n", input_net.size());


	cout << " The DAG is: "  << endl;
	for (int i = 0; i< num_arteries; i++){
        printf(" %4d %4d \n", DAG(i,0), DAG(i,1));
        }

    cout<<"arts:"<<endl;
    arts[0]->printParameters(1,0);        // print title
    for (int i=0; i<num_arteries; i++){
        cout<<i<<":"<<endl;
        arts[i]->printParameters(0,1);     // print data
        }
    cout<<endl;
    printf("%-8s","nodes:");
    conjs[0]->print(1);                  // print title and data
    for (int i=0; i<num_conjuncs; i++){
        printf("%-8d",i);
        conjs[i]->print(0);
        }

    printf("%16s %16s \n","record_artery", "record_nodes");
    for (uint i = 0; i < artery_record.size(); i++){
    printf( "%16d  %16d \n", artery_record[i], pos_record[i]);
    }
}

void network_arts_conjuncs::writeHist(const char* desti_File, vector< vector<float> >& data)const {

    FILE *writfile;
    writfile=fopen(desti_File,"w");
    int m=data.size();
    int n=data[0].size();
    for( int j=0; j<n; j++){
        for (int i=0; i<m-1; i++){
            fprintf(writfile, "%.14e,\t", data[i][j]);
        }
        fprintf(writfile, "%.14e\n", data[m-1][j]);
    }
    fclose (writfile);
}

void network_arts_conjuncs::set_dataFolder(const string& destiFolder){
dataFolder=destiFolder;
}
void network_arts_conjuncs::set_Adatafile(const string& destiName){
Adatafile=destiName;
}
void network_arts_conjuncs::set_Qdatafile(const string& destiName){
Qdatafile=destiName;
}
void network_arts_conjuncs::set_Pdatafile(const string& destiName){
Pdatafile=destiName;
}
void network_arts_conjuncs::set_DAGFile(const string& destiName){
DAGFile=destiName;
}
void network_arts_conjuncs::set_paraFile(const string& destiName){
paraFile=destiName;
}
void network_arts_conjuncs::set_reflecFile(const string&destiName){
reflecFile=destiName;
}
void network_arts_conjuncs::set_outputFile(const string&destiName){
outputFile=destiName;
}
void network_arts_conjuncs::set_inputFile(const string&destiName){
inputFile = destiName;
}

void network_arts_conjuncs::set_timeSetupFile(const string&destiName) {
timeSetupFile = destiName;
}

void network_arts_conjuncs::checkTimeStep() {
    for (uint n = 0; n < arts.size(); n++) {
        if ( (arts[n]->get_cRef() * t_step) > 0.8 * arts[n]->get_dx() )
        Warning("Time step is too large.");
    }
}
void network_arts_conjuncs::appointSolver(artery*& art, vesselProperties& vP ){

        string solver=vP.get_solver();
        if(solver=="MC")
            art=new artery_MC(vP);
        else if(solver=="FV")
            art=new artery_FV(vP);
        else
            cerr<<" solver <"<< solver<<"> not defined"<<endl;

}

int network_arts_conjuncs::get_arts_num() const {
    return num_arteries;
}
