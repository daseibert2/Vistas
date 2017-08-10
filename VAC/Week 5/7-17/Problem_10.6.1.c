#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define dx 1.0
#define dt 0.1
#define x_end M_PI
#define t_end 1.0
#define x_size x_end/dx+1
#define t_size t_end/dt+1
#define D 0.0
#define N 1.0
#define Y D*dt/(dx*dx)

void printAll(double)

void zeroesU(double u[t_size][x_size],int row)
{
    u
}

int main()
{
    double u[t_size][x_size];
    for(int x=0;i<x_size;x++)
    {
        u[x][0]=sin(x*dx*n);
    }

    for(int n=1;n<t_size;n++)
    {
        for(int j=1;j<x_size;j++)
        {
            u[n][j-1]=u[n-1]+Y*()
        }
    }

    return 0;
}
