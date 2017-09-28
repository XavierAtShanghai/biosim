#include "conjunction.h"

conjunction::conjunction(){
    //ctor
    }

conjunction::~conjunction(){

    //dtor
    }

void conjunction::add_parentArtery(artery* _pA){
    parentArtery.push_back(_pA);
    }

void conjunction::add_daughterArtery(artery* _dA){
    daughterArtery.push_back(_dA);
    }

bool conjunction::set_root_leaves(){
    if (parentArtery.size()==0 && daughterArtery.size() > 0  )
		my_type=root;
    else if(parentArtery.size() == 1 && daughterArtery.size()==0 )
        my_type=leaf;

    else if (parentArtery.size()==0 && daughterArtery.size()==0 ) {
        my_type=orphan;
        cerr<<" Warrning: this is an orphan conjunction" << endl;
        }
    else
        my_type=normal;

    return true;
}

void conjunction::set_reflective_coeff(SCALAR _refCoef){reflective_coeff=_refCoef;}

void conjunction::print(bool flag_title) const {
        if(flag_title){
        printf("%12s %12s %12s %12s \n", "Parent" , "daughter1", "dauther2", "Re_Coef");
        return;
        }

		if( isRoot() ){
			printf("%12s", " ");
            for(uint i = 0; i < daughterArtery.size(); i++)
            printf("%12d", daughterArtery[i]->get_label() );  // transform to human readable
            printf("\n");
			return;
			}
		else if( isLeaf() ){
			printf("%12d %12s %12s %12.2f \n", parentArtery[0]->get_label(), " ", " ", reflective_coeff );
			return ;
			}
        else if( isOrphan() ){
			printf("%12s  \n", " orphan ");
			return ;
			}
		else {
            printf("%12d", parentArtery[0]->get_label());
            for(uint i=0; i<daughterArtery.size();i++)
            printf("%12d", daughterArtery[i]->get_label() );
            printf("\n");
		}
}


void conjunction::BC_A_inflow(const SCALAR& _A){
    daughterArtery[0]->BC_A_inflow(_A);
    }

void conjunction::BC_Q_inflow(const SCALAR& _Q){
    daughterArtery[0]->BC_Q_inflow(_Q);
    }

void conjunction::BC_P_inflow(const SCALAR& _P){
    daughterArtery[0]->BC_P_inflow(_P);
    }


void conjunction::BC_outflow(){
    parentArtery[0]->BC_reflective_outlow(reflective_coeff);
    }



void conjunction::solve_conjunction_PD(artery* parent, artery* daughter1){
        VECT init_guess(4);
        VECT par(6);

        parent->get_AQW1_Right(init_guess[0], init_guess[1], par[0]);
        daughter1->get_AQW2_Left(init_guess[2], init_guess[3], par[1]);

        parent->get_betaA0(par[2], par[3]);
        daughter1->get_betaA0(par[4], par[5]);

//        cout<<"init="<<endl;
//        init_guess.print();
//        cout<<"par="<<endl;
//        par.print();
        VECT AQ_nplus1 = newtonRahpson(fun_conj_PD, init_guess, par);
//        cout<<"reslut after newtonRahpson"<<endl;
//        AQ_nplus1.print();
        parent->set_AQ_Right(AQ_nplus1[0], AQ_nplus1[1]);
        daughter1->set_AQ_Left(AQ_nplus1[2], AQ_nplus1[3]);
}

//parent + 2daughers
void conjunction::solve_conjunction_PDD(artery* parent, artery* daughter1, artery* daughter2){
        VECT init_guess(6);
        VECT par(9);
        parent->get_AQW1_Right(init_guess[0], init_guess[1], par[0]);
        daughter1->get_AQW2_Left(init_guess[2], init_guess[3], par[1]);
        daughter2->get_AQW2_Left(init_guess[4], init_guess[5], par[2]);

        parent->get_betaA0(par[3], par[4]);
        daughter1->get_betaA0(par[5], par[6]);
        daughter2->get_betaA0(par[7], par[8]);


        VECT AQ_nplus1 = newtonRahpson(fun_conj_PDD, init_guess, par);

        parent->set_AQ_Right(AQ_nplus1[0], AQ_nplus1[1]);
        daughter1->set_AQ_Left(AQ_nplus1[2], AQ_nplus1[3]);
        daughter2->set_AQ_Left(AQ_nplus1[4], AQ_nplus1[5]);

}

void conjunction::solve_conjunction_PDDD(artery* parent, artery* daughter1, artery* daughter2, artery* daughter3){
        VECT init_guess(8);
        VECT par(12);
        parent->get_AQW1_Right(init_guess[0], init_guess[1],  par[0]);
        daughter1->get_AQW2_Left(init_guess[2], init_guess[3], par[1]);
        daughter2->get_AQW2_Left(init_guess[4], init_guess[5], par[2]);
        daughter3->get_AQW2_Left(init_guess[6], init_guess[7], par[3]);


        parent->get_betaA0(par[4], par[5]);
        daughter1->get_betaA0(par[6], par[7]);
        daughter2->get_betaA0(par[8], par[9]);
		daughter3->get_betaA0(par[10], par[11]);


        VECT AQ_nplus1 = newtonRahpson(fun_conj_PDDD, init_guess, par);

        parent->set_AQ_Right(AQ_nplus1[0], AQ_nplus1[1]);
        daughter1->set_AQ_Left(AQ_nplus1[2], AQ_nplus1[3]);
        daughter2->set_AQ_Left(AQ_nplus1[4], AQ_nplus1[5]);
        daughter3->set_AQ_Left(AQ_nplus1[6], AQ_nplus1[7]);


}

//2parents + daugher
void conjunction::solve_conjunction_PPD(artery* parent1, artery* parent2, artery* daughter){
        VECT init_guess(6);
        VECT par(9);
        parent1->get_AQW1_Right(init_guess[0], init_guess[1], par[0]);
        parent2->get_AQW1_Right(init_guess[2], init_guess[3], par[1]);
        daughter->get_AQW2_Left(init_guess[4], init_guess[5], par[2]);

        parent1->get_betaA0(par[3], par[4]);
        parent2->get_betaA0(par[5], par[6]);
        daughter->get_betaA0(par[7], par[8]);

        VECT AQ_nplus1 = newtonRahpson(fun_conj_PPD, init_guess, par);

        parent1->set_AQ_Right(AQ_nplus1[0], AQ_nplus1[1]);
        parent2->set_AQ_Right(AQ_nplus1[2], AQ_nplus1[3]);
        daughter->set_AQ_Left(AQ_nplus1[4], AQ_nplus1[5]);

}


void conjunction::solve_conjunction_PP(artery* parent1, artery* parent2){
        VECT init_guess(4);
        VECT par(6);
        parent1->get_AQW1_Right(init_guess[0], init_guess[1], par[0]);
        parent2->get_AQW1_Right(init_guess[2], init_guess[3], par[1]);

        parent1->get_betaA0(par[2], par[3]);
        parent2->get_betaA0(par[4], par[5]);

        VECT AQ_nplus1 = newtonRahpson(fun_conj_PP, init_guess, par);

        parent1->set_AQ_Right(AQ_nplus1[0], AQ_nplus1[1]);
        parent2->set_AQ_Right(AQ_nplus1[2], AQ_nplus1[3]);

}


void conjunction::stepMarch(){

    if(parentArtery.size()==0 && daughterArtery.size()==0 ) {
        cout<<"igonred"<<endl;
        return;}
    else if(parentArtery.size() == 1 && daughterArtery.size() == 1)
        solve_conjunction_PD(parentArtery[0], daughterArtery[0]);

    else if(parentArtery.size() == 1 && daughterArtery.size() == 2)
        solve_conjunction_PDD(parentArtery[0], daughterArtery[0], daughterArtery[1]);

    else if(parentArtery.size() == 1 && daughterArtery.size() == 3)
        solve_conjunction_PDDD(parentArtery[0], daughterArtery[0], daughterArtery[1], daughterArtery[2]);

    else if(parentArtery.size() == 2 && daughterArtery.size() == 1)
        solve_conjunction_PPD(parentArtery[0], parentArtery[1], daughterArtery[0]);

	else if(parentArtery.size() == 2 && daughterArtery.size() == 0)
		solve_conjunction_PP(parentArtery[0], parentArtery[1]);
		
    else {
        cerr<<"conjunction::stepMarch():: unknown conjunction: "<< parentArtery.size() <<" parents and " << daughterArtery.size() << " daughters"<<endl;
        exit(1); }
    }

    VECT conjunction::fun_conj_PD(const VECT& AQ, const VECT& par){

    VECT A(2);    A[0] = AQ[0];    A[1] = AQ[2];
    VECT Q(2);    Q[0] = AQ[1];    Q[1] = AQ[3];

    VECT W(2);    W[0] = par[0];    W[1] = par[1];
    VECT beta(2); beta[0] = par[2]; beta[1] = par[4];
    VECT A0(2);   A0[0] = par[3];   A0[1] = par[5];

    VECT res(4);
    res[0] = Q[0] - Q[1];
    res[1] = beta[0] * (sqrt( A[0]) - sqrt(A0[0]) ) - beta[1] * (sqrt(A[1]) - sqrt(A0[1]));
    res[2] = Q[0] / A[0] + 4 * sqrt(beta[0] / 2 / RHO_FLUID * sqrt(A[0]) ) - W[0];
    res[3] = Q[1] / A[1] - 4 * sqrt( beta[1] / 2 / RHO_FLUID * sqrt(A[1]) ) - W[1];
    return res;
}

VECT conjunction::fun_conj_PDD(const VECT& AQ, const VECT& par){

    VECT A(3);    A[0] = AQ[0];    A[1] = AQ[2];  A[2] = AQ[4];
    VECT Q(3);    Q[0] = AQ[1];    Q[1] = AQ[3];  Q[2] = AQ[5];

    VECT W(3);    W[0] = par[0];    W[1] = par[1];  W[2] = par[2];
    VECT beta(3); beta[0] = par[3]; beta[1] = par[5]; beta[2] = par[7];
    VECT A0(3);   A0[0] = par[4];   A0[1] = par[6];  A0[2] = par[8];

    VECT res(6);
    res[0] = Q[0] - Q[1] - Q[2];
    res[1] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[1] * ( sqrt(A[1]) - sqrt(A0[1]) );
    res[2] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[2] * ( sqrt(A[2]) - sqrt(A0[2]) );

    res[3] = Q[0] / A[0] + 4 * sqrt( beta[0] / 2 / RHO_FLUID * sqrt(A[0]) ) - W[0];
    res[4] = Q[1] / A[1] - 4 * sqrt( beta[1] / 2 / RHO_FLUID * sqrt(A[1]) ) - W[1];

    res[5] = Q[2] / A[2] - 4 * sqrt( beta[2] / 2 / RHO_FLUID * sqrt(A[2]) ) -W[2];
    return res;
}

//parent + 3 daughers
VECT conjunction::fun_conj_PDDD(const VECT& AQ, const VECT& par){
	
    VECT A(4);    A[0] = AQ[0];    A[1] = AQ[2];  A[2] = AQ[4];  A[3] = AQ[6];
    VECT Q(4);    Q[0] = AQ[1];    Q[1] = AQ[3];  Q[2] = AQ[5];  Q[3] = AQ[7];
	  
    VECT W(4);    W[0] = par[0];    W[1] = par[1];  W[2] = par[2];  W[3] = par[3];	
	VECT beta(4); beta[0] = par[4]; beta[1] = par[6]; beta[2] = par[8]; beta[3] = par[10];
    VECT A0(4);   A0[0] = par[5];   A0[1] = par[7];  A0[2] = par[9]; A0[3] = par[11];

    VECT res(8);
    res[0] = Q[0] - Q[1] - Q[2] -Q[3];
    res[1] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[1] * ( sqrt(A[1]) - sqrt(A0[1]) );
    res[2] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[2] * ( sqrt(A[2]) - sqrt(A0[2]) );
	res[3] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[3] * ( sqrt(A[3]) - sqrt(A0[3]) );
	

    res[4] = Q[0] / A[0] + 4 * sqrt( beta[0] / 2 / RHO_FLUID * sqrt(A[0]) ) - W[0];
    res[5] = Q[1] / A[1] - 4 * sqrt( beta[1] / 2 / RHO_FLUID * sqrt(A[1]) ) - W[1];
    res[6] = Q[2] / A[2] - 4 * sqrt( beta[2] / 2 / RHO_FLUID * sqrt(A[2]) ) - W[2];
    res[7] = Q[3] / A[3] - 4 * sqrt( beta[3] / 2 / RHO_FLUID * sqrt(A[3]) ) - W[3];

    return res;
}

VECT conjunction::fun_conj_PPD(const VECT& AQ, const VECT& par){

    VECT A(3);    A[0] = AQ[0];    A[1] = AQ[2];  A[2] = AQ[4];
    VECT Q(3);    Q[0] = AQ[1];    Q[1] = AQ[3];  Q[2] = AQ[5];

    VECT W(3);    W[0] = par[0];    W[1] = par[1];  W[2] = par[2];
    VECT beta(3); beta[0] = par[3]; beta[1] = par[5]; beta[2] = par[7];
    VECT A0(3);   A0[0] = par[4];   A0[1] = par[6];  A0[2] = par[8];

    VECT res(6);
    res[0] = Q[0] + Q[1] - Q[2];
    res[1] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[1] * ( sqrt(A[1]) - sqrt(A0[1]) );
    res[2] = beta[0] * ( sqrt(A[0]) - sqrt(A0[0]) ) - beta[2] * ( sqrt(A[2]) - sqrt(A0[2]) );

    res[3] = Q[0] / A[0] + 4 * sqrt( beta[0] / 2 / RHO_FLUID * sqrt(A[0]) ) - W[0];
    res[4] = Q[1] / A[1] + 4 * sqrt( beta[1] / 2 / RHO_FLUID * sqrt(A[1]) ) - W[1];

    res[5] = Q[2] / A[2] - 4 * sqrt( beta[2] / 2 / RHO_FLUID * sqrt(A[2]) ) -W[2];
    return res;
}

VECT conjunction::fun_conj_PP(const VECT& AQ, const VECT& par){

    VECT A(2);    A[0] = AQ[0];    A[1] = AQ[2];
    VECT Q(2);    Q[0] = AQ[1];    Q[1] = AQ[3];

    VECT W(2);    W[0] = par[0];    W[1] = par[1];
    VECT beta(2); beta[0] = par[2]; beta[1] = par[4];
    VECT A0(2);   A0[0] = par[3];   A0[1] = par[5];

    VECT res(4);
    res[0] = Q[0] + Q[1];
    res[1] = beta[0] * (sqrt( A[0]) - sqrt(A0[0]) ) - beta[1] * (sqrt(A[1]) - sqrt(A0[1]));
    res[2] = Q[0] / A[0] + 4 * sqrt(beta[0] / 2 / RHO_FLUID * sqrt(A[0]) ) - W[0];
    res[3] = Q[1] / A[1] + 4 * sqrt( beta[1] / 2 / RHO_FLUID * sqrt(A[1]) ) - W[1];
    return res;
}
