#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
#define tEND 1.0
#define xEND 3.1415926535897932384626433832795028841971
// These are up for variation to be more accurate
#define dt .1
#define dx 1
int xSize = xEND/dx +1;
int tSize = (double)tEND/dt +1;

// Constant
double lam = D*dt/(dx*dx);

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

int main()
{
    double U[tSize][xSize];

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
    if ( lam<=0.5 ){
        printf("\nThe results and therefore algorithm is unstable. Lambda (D*dt/(dx^2) = %1.5lf", lam);
    }
    printf("Lambda: %lf", lam);

    return 0;
}


// PRINTING FUNCTION
void printAll( double u[tSize][xSize] ){
    int i, j;
    for( i=0; i<tSize; i++ ){
        for( j=0; j<xSize; j++ ){
            printf("%3.3lf\t", u[i][j] );
        }
        printf("\n\n");
    }

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
        u[tRow][i] = u[tRow-1][i] + lam*( u[tRow-1][i-1] -
            2*u[tRow-1][i] + u[tRow-1][i+1] ) + dt*F(i*dt, i*dx);
    }
}
