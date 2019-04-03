#include "Trapazoidal.h"

int integrateTrapazoidal(Integrate *intereg)
{

    int i, j;
    double dx;
    double lowerLimit = intereg->lowerLimit;
    double upperLimit = intereg->upperLimit;
    int *intervals = intereg->intervals;
    int nIntervals = intereg->nIntervals;
    int method = intereg->method;
    double *area = (double *)malloc(sizeof(double) * nIntervals);

    if(!area){
        printf("\nCould not allocate Area");
        return EXIT_FAILURE;
    }

    //Finding area wrt every n passed bu user from Integration.c
    
    for(j = 0; j < nIntervals; j++)
    {
        dx = (upperLimit - lowerLimit) / intervals[j]; //step size or length of intervals
        //double area = 0.0L; //our goal to find
        area[j] = intereg->func(upperLimit) + intereg->func(lowerLimit);
        for (i = 1; i < intervals[j]; i++)
        {
            //area = area + (intereg->func(upperLimit + i * dx) + intereg->func(upperLimit + (i + 1) * dx)) * dx / 2.0; 
            area[j] += 2 * (intereg->func(lowerLimit + i * dx));
        }   
        intereg->areaUnderCurve[j] = dx / 2.0 * area[j];
        intereg->resultMatrix[method - 1][j] = intereg->areaUnderCurve[j];
    }
    
    free(area);
    area = NULL;
    //Check for any errors here if there are any errors return the error code hence the return type is int
    return EXIT_SUCCESS;

}
