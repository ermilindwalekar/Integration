#include "headers.h"

#include "Trapazoidal.h"
#include "Gauss.h"
#include "Simpson.h"
/*
    We could use here a default function sin(x) but it is made flexible so that dev may define a function of his own
    and pass it to the below function (given the signature of function match) and it will work accordingly
*/
int integrationInitializer(Integrate *integrate, double(*function)(double), int method)
{
    integrate->lowerLimit = 0.0;
    integrate->upperLimit = M_PI;

    integrate->func = function;
    integrate->method = method;
    //integrate->intervals = intervals;

    if(integrate->method != 3)
    {
        integrate->areaUnderCurve = (double *) malloc(sizeof(double) * integrate->nIntervals);
    }
    else
    {
        integrate->areaUnderCurve = (double *) malloc(sizeof(double) * 1);
    }

    if(integrate->method == 1)
    {
        if(integrateTrapazoidal(integrate) != EXIT_FAILURE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\nError integrating <Trapazoidal>");
            free(integrate->areaUnderCurve);
            integrate->areaUnderCurve = NULL;

            free(integrate->intervals);
            integrate->intervals = NULL;

            return EXIT_FAILURE;
        }
    }
    if(integrate->method == 2)
    {
        if(integrateSimpson(integrate) != EXIT_FAILURE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\nError integrating <Simpson Method>");
            free(integrate->areaUnderCurve);
            integrate->areaUnderCurve = NULL;

            free(integrate->intervals);
            integrate->intervals = NULL;

            return EXIT_FAILURE;
        }
    }
    if(integrate->method == 3)
    {
        if(integrateGauss(integrate) != EXIT_FAILURE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\nError integrating <Gauss Method>");
            free(integrate->areaUnderCurve);
            integrate->areaUnderCurve = NULL;

            free(integrate->intervals);
            integrate->intervals = NULL;

            return EXIT_FAILURE;
        }
    }
    free(integrate->areaUnderCurve);
    free(integrate->intervals);

    integrate->intervals = NULL;
    integrate->areaUnderCurve = NULL;
    return EXIT_FAILURE;
}

//Printing Logic *Pretty Print*
void printStats(Integrate *integrate, bool tabulate, int method)
{
    int iLoop, jLoop;

    if(!tabulate)
    {
        if(method == 1)
        {
            printf("\nObservations for finding area under curve with Trapazoidal Rule");
        }
        if(method == 2)
        {
            printf("\nObservations for finding area under curve with Simpson's Rule");
        }
        if(method == 3)
        {
            printf("\nObservations for finding area under curve with Gauss Rule");
            printf("\nGauss method does not depend on intervals thus area under curve is: %lf", integrate->areaUnderCurve[0]);
            return;
        }
        for(iLoop = 0; iLoop < integrate->nIntervals; iLoop++ )
        {
            printf("\nArea under the curve evaluated with %d intervals is: %lf", integrate->intervals[iLoop], integrate->areaUnderCurve[iLoop]);
        }
    }
    else
    {
        printf("\nIntervals -> \t\t\t");
        for(jLoop = 0; jLoop < 4; jLoop++)
        {
            printf("%d\t\t\t", integrate->intervals[jLoop]);
        }
        printf("\n");
        for(iLoop = 0; iLoop < 3; iLoop++)
        {
            if(iLoop + 1 == 1)
            {
                printf("\nTrapazoidal Rule");
            }
            if(iLoop + 1 == 2)
            {
                printf("\nSimpson's 1/3 Rule");
            }
            if(iLoop + 1 == 3)
            {
                printf("\nGauss Rule\t");
            }
            for(jLoop = 0; jLoop < 4; jLoop++)
            {
                printf("\t\t%lf", integrate->resultMatrix[iLoop][jLoop]);
            }
            printf("\n");
        }
    }
}

void integrateReal(Integrate *integrate)
{
    getRealIntegration(integrate);
    printf("\n\nTrue area under the curve is %lf\n", integrate->areaUnderCurve[0]);
}

int main()
{
    int method, i, nIntervals, iTemp;
    char inter;

    //Initializing the structure with default values
    Integrate integrate = {.intervals = NULL, .upperLimit = 0, .lowerLimit = 0, .func = NULL,
                           .areaUnderCurve = NULL, method = 0, nIntervals = 4, .resultMatrix = NULL
                          };

    int *intervals = (int *)malloc(sizeof(int) * 4);

    //These are the dafault values to be chosen
    intervals[0] = 2;
    intervals[1] = 8;
    intervals[2] = 16;
    intervals[3] = 64;

    integrate.intervals = intervals;

    printf("\nEnter 1 for Trapazoidal Method");
    printf("\nEnter 2 for Simpson Method");
    printf("\nEnter 3 for Gauss Method");
    printf("\nEnter 4 for to get stats for every method (default intervals{2, 8, 16, 64})");
    printf("\nEnter -1 to quit");

    printf("\n\nEnter your choice: ");
    scanf("%d", &method);

    //If user has not asked to exit, or not asked for Gauss rule and entered a valid choide we need to ask user to if he wants to specify parameters
    if(method != -1 && method != 3 && method < 4)
    {
        printf("\nDo you want to give in intervals?\nThe default intervals chosen are {2, 8, 16, 64}");
        printf("\nEnter 'y' for yes anything else otherwise: ");
        getchar();
        scanf("%c", &inter);

        //Checking for upper and lower case y,Y
        if(inter == 121 || inter == 89)
        {
            printf("\nAny invalid values (i.e. x <= 0) will be treated as 1");
            printf("\nHow many intervals?");
            scanf("%d", &nIntervals);
            if(nIntervals <= 0)
            {
                nIntervals = nIntervals - nIntervals + 1;
            }
            integrate.nIntervals = nIntervals;

            //Changinf the size of intervals from the initial default size 4
            intervals = (int *) realloc(intervals, nIntervals);

            //Checking if the memory was allocated
            if(!intervals)
            {
                //If not free resources the were already initialized
                intervals = NULL;
                printf("\nCould not resize the intervals array");
                return EXIT_FAILURE;
            }

            printf("\nEnter intervals one by one! Intervals cannot be negative or zero\n");
            for(i = 0; i < nIntervals; i++)
            {
                scanf("%d", &iTemp);
                if(iTemp <= 0)
                {
                    iTemp = iTemp - iTemp + 1;
                }
                intervals[i] = iTemp;
            }
            integrate.intervals = intervals;
        }
        else
        {
            printf("\nYou have chosen to move on with default intervals\n");
        }
    }

    //Question is, is switch required?
    //Yes as we are also giving user an option to use compute using all of the above method
    switch(method)
    {
    case 1:

    case 2:

    case 3:
        initializeResultMatrix(&integrate);
        if(integrationInitializer(&integrate, sinFunction, method) != EXIT_FAILURE)
        {
            printStats(&integrate, false, method);
            integrateReal(&integrate);
            explainObservations(method);
        }
        else
        {
            return EXIT_FAILURE;
        }
        break;

    case 4:
        initializeResultMatrix(&integrate);
        for(i = 1; i <= 3; i++)
        {
            if(integrationInitializer(&integrate, sinFunction, i) != EXIT_SUCCESS)
            {
                return EXIT_FAILURE;
            }
        }
        printStats(&integrate, true, method);
        integrateReal(&integrate);
        explainObservations(method);
        break;

    default:
        printf("\nInvalid Choice!\n");
        break;
    }

    //Freeing the resources so that we don't have any memory leaks
    //All we need to do is set intervals to NULL as we are freeing this memory in initialization by calling free(integrate->interval)
    //By this we are freeing the memory pointed by intervals and integrate->intervals
    if(integrate.resultMatrix != NULL)
    {
        //freeResultMatrix(&integrate);
    }
    intervals = NULL;
    return EXIT_SUCCESS;
}
