#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 3
#define L 1
#define Q 10
#define A 1

int main()
{
    int i,j;
    double h=(double)L/N;

    static float a[N][N]={{0}},f[4],u[N][4],e[N];
    double err=0;

    a[0][0]=2+(A*A*h*h);
    a[0][1]=-1.0;

    for (i=1;i<N-1;i++)
    {
        a[i][i]=2+(A*A*h*h);
        a[i][i-1]=-1.0;
        a[i][i+1]=-1.0;
    }
    a[N-1][N-2]=-1.0;
    a[N-1][N-1]=2+(A*A*h*h);

    /*for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("a(%d)(%d): %lf\t",i,j,a[i][j]);
        }
        printf("\n");
    }*/


    u[0][0]=1;
    u[0][1]=1;
    u[0][2]=1;

    for(j=0;j<N-1;j++)
    {
        for(i=0;i<N;i++)
        {
            f[i]=u[j][i];
            //printf("f(%d): %lf\n",i,f[i]);
        }
        u[j+1][0]=(f[0]-(a[0][1]*u[j][1])-(a[0][2]*u[j][2]))/a[0][0];
        u[j+1][1]=(f[1]-(a[1][0]*u[j+1][0])-(a[1][2]*u[j][2]))/a[1][1];
        u[j+1][2]=(f[2]-(a[2][0]*u[j+1][0])-(a[3][1]*u[j+1][1]))/a[2][2];

    }

    /*for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("u(%d)(%d): %lf\t",i,j,u[i][j]);
        }
        printf("\n");
    }*/

    for(int k=0;k<N;k++)
    {
        for(int l=0;l<N;l++)
        {
            e[k]=2*A*cosh(h*k)-2*Q*sinh(A*k)-2*A*exp(-Q*h);
        }
    }

   for(i=0;i<N;i++)
    {
            err=(fabs(e[i]-u[i][j])/fabs(e[i]))*100;
            printf("\nu(%d): %lf\tExact: %lf\tError: %lf\n",i,u[i][N-1],e[i],err);

    }

    return 0;
}
