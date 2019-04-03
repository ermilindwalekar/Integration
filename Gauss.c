#include "Gauss.h"

int integrateGauss(Integrate *intereg)
{
    double lowerLimit = intereg->lowerLimit;
    double upperLimit = intereg->upperLimit;
    
    double h = (upperLimit - lowerLimit) / 2.0; //step size
    double k = lowerLimit + h;
    double area = 0.0L; //our goal to find

    //using gauss method
    area = h*(intereg->func(k - h/sqrt(3)) + intereg->func(k + h/sqrt(3)));
    intereg->areaUnderCurve[0] = area;
    intereg->resultMatrix[--intereg->method][0] = intereg->areaUnderCurve[0];
    //Check for any errors here if there are any errors return the error code hence the return type is int
    return EXIT_SUCCESS;
}
