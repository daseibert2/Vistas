#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
    PROGRAM DISPLAYS THE DIFFUSION EQUATION FOR ENERGY? IN A BEAM THROUGH TIME
    _____EXPLICIT_METHOD__________EXPLICIT_METHOD__________EXPLICIT_METHOD_____
    Users Can Change the:
     - initializer multiple (n)     [defined]
     - density coefficient  (D)     [defined]
     - when time stops      (tEND)  [defined]               Meaning for calculation. Program does not help with midlife crises.
     - length of the board  (xEND)  [defined]
     - time step            (dt)    [defined]
     - position step        (dx)    [defined]
*/

// These are equation/situation specific definitions
#define n 1
#define D 1.0
#define tEND 1
#define xEND M_PI
// These are up for variation to be more accurate
#define lam .4
#define dx (M_PI/10)
#define dt (lam/D*dx*dx)

int xSize = xEND/dx +1;
int tSize = (double)tEND/dt +1;
char fileName[100];
char fileNameCSV[100];
char continu = 'y';

// Constant
//double lam = D*dt/(dx*dx);

/*
   x : 0->PI
   t : 0->1
*/

// MINI FUNCTION SET TO 0 BY DEFAULT CONDITIONS defined by problem
double F( double t, double x ){ return 0; }
// STEPWISE COMPUTATIONAL FUNCTIONS
void initializeU( double u[xSize][tSize] );
void boundaryConditions( double u[tSize][xSize], int tRow );
void fillRow( double[tSize][xSize], int );
// DISPLAY FUNCTION
void printAll( double u[tSize][xSize] );
// EXACT FUNCTION
double exact( double t, double x ){ return exp(-n*n*t)*sin(n*x); }

int main()
{
    double U[tSize][xSize];

    while (continu == 'y'){

        printf("Please Enter the file name in which these values will be stored: \n");
        scanf(" %s", fileName);
        strcpy(fileNameCSV, fileName);
        strcat(fileNameCSV, ".csv");


        /* STEP 1: Set the initial U at t=0 for the length of the beam x: 0->PI */
        initializeU( U );

        int i; // goes through all the time steps
        for( i=1; i<tSize; i++ ){
        /* STEP 2: Boundary Conditions for Next time Step */
            boundaryConditions( U, i );
        /* STEP 3: Filling in the rest of the current time Step */
            fillRow( U, i );
        }


        /* STEP 4: Displaying the Results */
        printAll( U );
        /* STEP 5: Special Case. If Blows Up, Explain and display lambda. */
        if ( lam>=0.5 ){
            printf("\n\nThe results and therefore algorithm is unstable. Lambda (D*dt/(dx^2) = %1.5lf", lam);
        }
        printf("\n\nLambda: %lf\n", lam);

        printf("\nWould you like to continue again? (y/n) ");
        scanf(" %c", &continu);
    }

    return 0;
}


// PRINTING FUNCTION
void printAll( double u[tSize][xSize] ){
    int i, j;
    FILE *f = fopen(fileNameCSV, "w");
    char errorFile[101];
    strcpy(errorFile, fileName);
    strcat(errorFile, "ERROR.csv");
    FILE *ef = fopen(errorFile, "w");

    fprintf(f,"t,x,exact,error\n");
    for( i=0; i<tSize; i++ ){
        //fprintf(f,"ESTIMATE: t=%lf", i*dt);
        for( j=0; j<xSize; j++ ){
            //if( j==0 )printf("ESTIMATE:\t");
            //printf("%lf", u[i][j] );
            //fprintf(f,",%lf", u[i][j]);
        }
       // fprintf(f,"\n");

        //fprintf(f,"ACTUAL: t=%lf", i*dt);
        for( j=0; j<xSize; j++ ){
           // if( j==0 )printf("\nACTUAL:\t\t");
            //printf("\t%lf", exact(i*dt, j*dx) );
            //fprintf(f,",%lf", exact(i*dt, j*dx) );
            printf("%lf %lf\n\n",i*dt,j*dx);
        }
       /* fprintf(f,"\n");

        fprintf(f,"ERROR: ");
        for( j=0; j<xSize; j++ ){
            if( j==0 )printf("\nPercent ERROR:\t");
            printf("\t%lf", (exact(i*dt,j*dx)-u[i][j])/exact(i*dt,j*dx)*100 );
            fprintf(f,",%lf", (exact(i*dt,j*dx)-u[i][j])/exact(i*dt,j*dx)*100 );
        }
        fprintf(f,"\n\n");
//        for( j=0; j<xSize; j++){
//            fprintf(f,"%lf,%lf,%lf,%lf\n", i*dt, u[i][j], exact(i*dt,j*dx), (exact(i*dt,j*dx)-u[i][j])/exact(i*dt,j*dx)*100);
//        }
        printf("\n\n\n\n");*/
    }

    fclose(f);
    fclose(ef);

}


void initializeU( double u[tSize][xSize] ){
    int i;
    for( i=0; i<xSize; i++ ){
        u[0][i] = sin(i*dx*n);
    }
}
void boundaryConditions( double u[tSize][xSize], int tRow ){
    u[tRow][0] = 0;
    u[tRow][xSize-1] = 0;
}
void fillRow( double u[tSize][xSize], int tRow){
    int i;
    for( i=1; i<xSize-1; i++ ){
        u[tRow][i] = u[tRow-1][i] + lam*( u[tRow-1][i-1] - 2*u[tRow-1][i] + u[tRow-1][i+1] ) + dt*F(i*dt, i*dx);
    }
}
