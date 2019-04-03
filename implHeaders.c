/*
This file implements all the function defined in headers.h
*/

#include "headers.h"

double sinFunction(double x)
{
    return sin(x);
}

void getRealIntegration(Integrate *integ)
{
    double iTemp;
    double area = 0;
    double lowerLimit = integ->lowerLimit;
    double upperLimit = integ->upperLimit;

    if (lowerLimit > upperLimit)
    {
        iTemp = lowerLimit;
        lowerLimit = upperLimit;
        upperLimit = iTemp;
    }

    for (iTemp = lowerLimit; iTemp < upperLimit; iTemp += (upperLimit - lowerLimit) / N)
    {
        /* Define your function below, and include the suitable header files */
        area += integ->func(iTemp) * (upperLimit - lowerLimit) / N;
    }
    integ->areaUnderCurve[0] = area;
}

int initializeResultMatrix(Integrate *integ)
{
    int i;
    integ->resultMatrix = (double **) malloc(3 * sizeof * integ->resultMatrix);
    if(integ->resultMatrix != NULL)
    {
        for (i = 0; i < integ->nIntervals; i++)
        {
            integ->resultMatrix[i] = (double *) malloc(integ->nIntervals * sizeof * integ->resultMatrix[i]);
        }
    }
    return EXIT_SUCCESS;
}

void freeResultMatrix(Integrate *integ)
{
    int i;
    for (i = 0; i < integ->nIntervals; i++)
    {
        free(integ->resultMatrix[i]);
    }
    free(integ->resultMatrix);
    integ->resultMatrix = NULL;
}

void explainObservations(int method)
{
    switch(method)
    {
        case 4:
            printf("\n\nWe see that with the number of intervals increasing the approximated area\ngoes much closer to the actual area. Although actual area is a bit misleading\nhere as we are using C to compute it but from our prior knowledge we know that\nIntegration of sin(x) is cos(x) which under the limits 0 - PI gives AUC as 2\nand thus we may consider the area returned by function getRealIntegration is\nactually the actual area\n\n");
        break;

        case 1:
            printf("\n\nTrapazoidal rule works by dividing the ara into trapaziums with N Equidistant\npoints. Thus the more the number of intervals higher the precision\nof the method. We can observe from the output that the higher the number\nmore close the area is to the actual area calculated by us.\n\n");
        break;
        
        case 2:
            printf("\n\nSimpson rule works on quadrtic polynomial (i.e., parabolic arcs instead of the\nstraight line segments used in the trapezoidal rule).points. Thus,\nthe lower the number of intervals lower the precision of the method\nand we overshoot the area.We can observe from the output that the higher the number more close\nthe area is to the actual area calculated by us.\n\n");
        break;

        case 3:
            //printf("\n\nTrapazoidal rule works by dividing the ara into trapaziums with N Equidistant\npoints. Thus the more the number of intervals higher the precision\nof the method. We can observe from the output that the higher the number\nmore close the area is to the actual area calculated by us.\n\n");
        break;

        default:
            printf(" ");
    }
}