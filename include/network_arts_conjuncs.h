#ifndef NETWORK_ARTS_CONJUNCS_H
#define NETWORK_ARTS_CONJUNCS_H
#include "artery.h"
#include "artery_FV.h"
#include "artery_MC.h"
#include "alger.h"
#include "conjunction.h"
#include "parser.h"
#include <omp.h>

class network_arts_conjuncs
{
    public:
        network_arts_conjuncs(const string&);
        virtual ~network_arts_conjuncs();

        //set functions
        void readDAG(const char* _DAG);
        void readLeavesRefelcts(const char* _leavesRef);
        void readTimeSetup(const char* _timeSetup);
        void readInput(const char* _inputFile);
        void readOutput(const char* _outputFile);


        void run();
        void run_openMP();

        void print() const;
        void writeHist(const char* desti_File, vector< vector<float> >& data) const;
        void set_dataFolder(const string&);
        void set_Adatafile(const string&);
        void set_Qdatafile(const string&);
        void set_Pdatafile(const string&);
        void set_DAGFile(const string&);
        void set_paraFile(const string&);
        void set_reflecFile(const string&);
        void set_outputFile(const string&);
        void set_inputFile(const string&);
        void set_timeSetupFile(const string&);


        int get_arts_num() const;

    protected:

    double t_final;
    double t_step;

    double recordStart;
    double recordEnd;

    vector<double> input_net;
    enum Input_type{Qinput=1,Ainput=2,Pinput=3};
    Input_type input_type_net;

    vector<vesselProperties> ves_pros;    //vessel properties
    matrix<int> DAG;

    int num_arteries;
    int num_conjuncs;
    vector<artery*> arts;
    vector<conjunction*> conjs;

    vector <int> artery_record;
    vector <int> pos_record;

    void checkTimeStep();
    void appointSolver(artery*& art, vesselProperties& vP );

    private:

    string dataFolder;
    string Adatafile;
    string Qdatafile;
    string Pdatafile;
    string DAGFile;
    string paraFile;
    string reflecFile;
    string outputFile;
    string inputFile;
    string timeSetupFile;
};

#endif // NETWORK_ARTS_CONJUNCS_H
