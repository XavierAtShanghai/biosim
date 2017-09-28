#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

/**
 * Defines the constants, the types used in the code and contains the `include'.

 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <assert.h>

#include "matrix.h"
#include "error.h"
#define MAX(a,b) (a>=b?a:b)
#define MIN(a,b) (a<=b?a:b)

#define ZERO 0.0
#define EPSILON 1.e-13
#define PI 3.1415926

#define VERSION "bloodflow_1D version 1.00.01, 2013-05"

using namespace std;

typedef double SCALAR;
typedef unsigned int uint;
typedef matrix<SCALAR> MATR;

/**kinematic  viscocity of the blood */
static   SCALAR NU_FLUID=1e-2;      //cm^2/s
    /** density of the fluid */
static  SCALAR RHO_FLUID=1.05e-3;     // kg/cm^3
static double ALPHA=1.1 ;       // momentum corrector coefficient

#endif // MISC_H_INCLUDED
