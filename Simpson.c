#include "Simpson.h"

int integrateSimpson(Integrate *intereg)
{
    int i, j, last, foundOdd = 0;
    
    //Default size of below arrays is 1, this is being done in order to make sure we do the allocation
    //and freeing of memory while we are in loop
    double *tempOne = (double *) malloc(sizeof(double) * 1);
    double *tempTwo = (double *) malloc(sizeof(double) * 1);

    double *checkTempOne = NULL;
    double *checkTempTwo = NULL;


    double dx, sumOdd, sumEven, area;

    double lowerLimit = intereg->lowerLimit;
    double upperLimit = intereg->upperLimit;
    int *intervals = intereg->intervals;
    int nIntervals = intereg->nIntervals;
    int method = intereg->method;

    for(j = 0; j < nIntervals; j++ )
    {
        //Taking this size considering all intervals provided were odd
        if(intervals[j] % 2 != 0)
        {
            printf("\nFound odd interval %d, adding 1 to make it even", intervals[j]);
            foundOdd = 1;
            intervals[j] = intervals[j] + 1;
        }

        checkTempOne = (double *) realloc(tempOne, sizeof(double) * intervals[j]);
        if(checkTempOne != NULL)
        {
            tempOne = checkTempOne;
        }
        else
        {
            free(checkTempOne);
            TRACE("Could not realloc memory to temporary array one");
            return EXIT_FAILURE;
        }

        checkTempTwo = (double *) realloc(tempOne, sizeof(double) * intervals[j]);
        if(checkTempTwo != NULL)
        {
            tempTwo = checkTempTwo;
        }
        else
        {
            free(checkTempTwo);
            TRACE("Could not realloc memory to temporary array two");
            return EXIT_FAILURE;
        }

        dx = (upperLimit - lowerLimit) / intervals[j];
        for(i = 0; i < intervals[j]; i++)
        {
            tempOne[i] = lowerLimit + i * dx;
            tempTwo[i] = intereg->func(tempOne[i]);
        }

        sumOdd = 0;
        sumEven = 0;

        for(i = 1; i < intervals[j]; i++)
        {
            if(i % 2 == 1)
            {
                sumOdd +=  tempTwo[i];
            }
            else
            {
                sumEven += tempTwo[i];
            }
        }

        if(foundOdd == 1)
        {
            //Adjusting the last index in case we have incremented the interval by 1
            //Else this will result in OOB access corrupting the memory which will result in realloc to fail
	    //intervals[j] = intervals[j] - 1 ;
            last = intervals[j] - 2;
            //We handled the odd interval, good job foundOdd, thankyou!
	    foundOdd = 0;
        }
        else
        {
            last = intervals[j] - 1;
        }
        area = dx / 3 * (tempTwo[0] + tempTwo[last] + 4 * sumOdd + 2 * sumEven);
        intereg->areaUnderCurve[j]  = area;
        intereg->resultMatrix[method - 1][j] = intereg->areaUnderCurve[j];
    }

    intervals = NULL;
    return EXIT_SUCCESS;
}
