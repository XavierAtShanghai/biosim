#ifndef CONJUNCTION_H
#define CONJUNCTION_H
#include "artery.h"
#include "artery_FV.h"
#include "artery_MC.h"
#include "alger.h"
using namespace alger;
class conjunction
{
    public:
        conjunction();
        virtual ~conjunction();

        void add_parentArtery(artery*);
        void add_daughterArtery(artery*);
        bool set_root_leaves();
        void set_reflective_coeff(SCALAR );
        void print(bool flag=false) const;

        bool isRoot()const {return my_type == root; };
        bool isLeaf()const {return my_type == leaf;};
        bool isOrphan()const {return my_type == orphan;};


        void BC_A_inflow (const SCALAR& _A);
        void BC_Q_inflow (const SCALAR& _Q);
        void BC_P_inflow(const SCALAR& _P);
        void BC_outflow ();

        void solve_conjunction_PD(artery* parent, artery* daughter1);
        void solve_conjunction_PDD(artery* parent, artery* daughter1, artery* daughter2);
		void solve_conjunction_PDDD(artery* parent, artery* daughter1, artery* daughter2, artery* daughter3);
        void solve_conjunction_PPD(artery* parent1, artery* parent2, artery* daughter);
        void solve_conjunction_PP(artery* parent1, artery* parent2);
        void stepMarch();

    protected:
    private:
    vector<artery*> parentArtery;
    vector<artery*> daughterArtery;

    enum con_type{root=1, leaf=2, orphan=3, normal=4};
	con_type my_type;

    double reflective_coeff;

    static VECT fun_conj_PD(const VECT& AQ, const VECT& par);
    static VECT fun_conj_PP(const VECT& AQ, const VECT& par);
    static VECT fun_conj_PDD(const VECT& AQ, const VECT& par);
    static VECT fun_conj_PDDD(const VECT& AQ, const VECT& par);
    static VECT fun_conj_PPD(const VECT& AQ, const VECT& par);
};

#endif // CONJUNCTION_H
