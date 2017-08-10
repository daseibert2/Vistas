#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 50
#define L 1
#define Q 10
#define A 1
#define u0 0
#define uL 0
//#define h 0.0005
//#define N L/h
int main()
{
    int i,j;
    double h=(double)L/N;
    //int N=(int)L/h;


    static float mat[N][N]={{0}},alpha[N],g[N],result[N],u[N],err=0,e[N];

    mat[0][0]=2+(A*A*h*h);
    mat[0][1]=-1.0;

    for (i=1;i<N-1;i++)
    {
        mat[i][i]=2+(A*A*h*h);
        mat[i][i-1]=-1.0;
        mat[i][i+1]=-1.0;
    }
    mat[N-1][N-2]=-1.0;
    mat[N-1][N-1]=2+(A*A*h*h);
    result[0]=h*h*exp(-Q*h*0)+u0;

    for(i=1;i<N-1;i++)
    {
        result[i]=h*h*exp(-Q*h*i);
    }
    result[N-1]=h*h*exp(-Q*(N-1)*h)+uL;

    alpha[0]=mat[0][0];
    g[0]=result[0];

    for(j=1;j<N;j++)
    {
        alpha[j]=mat[j][j]-(mat[j][j-1]/alpha[j-1])*mat[j-1][j];
        g[j]=result[j]-(mat[j][j-1]/alpha[j-1])*g[j-1];
    }
    u[N-1]=g[N-1]/alpha[N-1];

    for(int w=N-2;w>-1;w--)
    {
        u[w]=(g[w]-mat[w][w+1]*u[w+1])/alpha[w];
    }
    for(int k=0;k<N;k++)
    {
       //e[k]=u0*sinh(A*(L-k*h))/sinh(A*L);//ok
        //e[k]=e[k]-((-pow(exp(-Q*k*h),2)/A)*((A*cosh(A*k*h)+Q*sinh(A*k*h)-A)/(A*A-Q*Q)));
       // e[k]=e[k]-(1/A)*((exp(-Q*(k-(k*h)))/A)*exp(-Q*((k*h)-k)));
        //e[k]=e[k]+(sinh(A*k*h)/sinh(A*1))*(uL+(-pow(exp(-Q*L),2)/(A*A-Q*Q)))*(A*cosh(A*L)+Q*sinh(A*L)-A);
       // e[k]=e[k]+(sinh(A*k*h)/sinh(A*L))*(uL+(1/A)*(((exp(-Q*(L-(k*h)))/A)*exp(-Q*((k*h)-L)))));
        e[k]=2*A*cosh(h*k)-2*Q*sinh(A*k)-2*A*exp(-Q*h);
    }

   for(i=0;i<N;i++)
    {
        if(e[i]!=0)
        err=(fabs(e[i]-u[i])/fabs(e[i]))*100;
        else
            err=fabs(e[i]-u[i])*100;
        printf("\nu(%d): %.20lf\tExact: %lf\tError: %.20lf\n",i,u[i],e[i],err);
    }

    return 0;
}
