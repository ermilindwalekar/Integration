#ifndef COMMON_H
#define COMMON_H
//Header guardd to avoid multiple inclusion of header files

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//I thought of using it but couldn't, instead I used EXIT_SUCCESS and EXIT_FAILURE for connsistency
#include <stdbool.h>

//Used to printf TRACE of running program, we may choose to not use it by setting some flags while compile time
//May be when the debug is on we can print it but not in release builds
#define TRACE(x) printf("\n%s",x) 

//Used to find real area under curve, higher the N more is the precision
#define N 1000

//Structure that holds all the required values for the integration as well as for pretty output
struct Integration
{
    int* intervals;
    double upperLimit;
    double lowerLimit;
    double (*func)(double);
    double* areaUnderCurve;
    int method;
    int nIntervals;
    double** resultMatrix;
};

//Typedef used to avoid typing long struct names e.g. struct HilbertMatrix and struct Integration
typedef struct HilbertMatrix Hilbert;
typedef struct Integration Integrate;

//This is the function we need to find AUC of, it will be passed as function pointer to the structure above
double sinFunction(double);

//Returns the true area under curve to compare it with the approximated methods used
void getRealIntegration(Integrate*);

//Initializes the resulting matrix which holds the results for n different intervals
int initializeResultMatrix(Integrate*);

//Making sure I release the memory allocated using malloc
void freeResultMatrix(Integrate*);

//Explanations and observations
void explainObservations(int);
#endif
