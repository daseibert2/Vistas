#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dx=(M_PI/10);
double Y=0.4;
double x_end=M_PI;
double t_end=1.0;
double D=1.0;
double n_initial=1.0;
int x_size=(int)(x_end/dx+1);
double dt=((Y*dx)/D);
int t_size=(int)(t_end/dt+1);

int F(double t,double x)
{
    return 0;
}

double exact(double t,double x)
{
    return exp(-n_initial*n_initial*t)*sin(n_initial*x);
}

double error(double exact,double approx)
{
    return (fabs(exact-approx)/exact)*100;
}

void printAll(double u[t_size][x_size])
{
    double ex=0,err=0;

    for(int n=1;n<t_size;n++)
    {
        for(int j=1;j<x_size;j++)
        {
            ex=exact(n*dt,j*dx);
            err=error(ex,u[n][j]);
            printf("u(%d)(%d): %3.20lf\t",n,j,u[n][j]);
            printf("Exact(%d): %3.20lf\t",j,ex);
            printf("Error(%d): %3.20lf\n",j,err);
        }
        printf("\n\n");
    }
}

void zeroesU(double u[t_size][x_size])
{
    for(int i=0;i<x_size;i++)
    {
        u[0][i]=sin(i*dx*n_initial);
    }
}

void boundaries(double u[t_size][x_size],int row)
{
    u[row][0]=0;
    u[row][x_size-1]=0;
}

/*void tridiagonal(u[t_size][x_size])
{
    int i,j;
    double h=(double)L/N;
    //int N=(int)L/h;
    #define N 50
#define L 1
#define Q 10
#define A 1
#define u0 0
#define uL 0

    static float mat[N][N]={{0}},alpha[N],g[N],result[N],u[N],err=0,e[N];

    mat[0][0]=1+Y;
    mat[0][1]=-Y;

    for (i=1;i<N-1;i++)
    {
        mat[i][i]=1+Y;
        mat[i][i-1]=-Y;
        mat[i][i+1]=-Y;
    }
    mat[N-1][N-2]=-Y;
    mat[N-1][N-1]=1+Y;
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
}*/

void fill(double u[t_size][x_size],int row)                          //Explicit
{
    for(int j=1;j<x_size-1;j++)
    {
        u[row][j]=u[row-1][j]+Y*(u[row-1][j-1]-2*u[row-1][j]+u[row-1][j+1])+dt*F(j*dt,j*dx);
    }
}

void fill_1(double u[t_size][x_size],int row)                       //Implicit
{
    //u=tridiagonal();
}

void fill_2(double u[t_size][x_size],int row)                       //C-N
{
    for(int j=1;j<x_size-1;j++)
    {
       u[row][j]=((Y/2)*u[row+1][j-1]+(1/Y)*u[row+1][j]-(Y/2)*u[row+1][j+1]
                  +(Y/2)*u[row][j-1]+(Y/2)*u[row][j+1])/(1-Y);
    }
}

void Explicit()
{
    printf("\nPart 1: Explicit\n\n");

    double u[t_size][x_size];

    zeroesU(u);

    for(int n=1;n<t_size;n++)
    {
        //boundaries(u,n);
        fill(u,n);
    }

    printAll(u);

    if(Y<=0.5)
        printf("\nAlgorithm is unstable, so the results are too.\nLambda (D*dt)/(dx^2)=%lf\n",Y);
    else
        printf("Lambda: %lf\n",Y);
}

void Implicit()
{
    printf("\n\nPart 2: Implicit\n\n");

    double u_1[t_size][x_size];

    zeroesU(u_1);

    for(int n=1;n<t_size;n++)
    {
        boundaries(u_1,n);
        fill_1(u_1,n);
    }

    //printAll(u_1);
}

void CrankNicolson()
{
    printf("\nPart 3: Crank-Nicolson\n\n");

    double u_2[t_size][x_size];

    zeroesU(u_2);

    for(int n=1;n<t_size;n++)
    {
        boundaries(u_2,n);
        fill_2(u_2,n);
    }

    //printAll(u_2);
}

int main()
{
//-----------------------------------------Part 1: Explicit---------------------------------------------

    Explicit();

//-----------------------------------------Part 2: Implicit---------------------------------------------

    Implicit();

//-----------------------------------------Part 3: Crank-Nicolson---------------------------------------

    CrankNicolson();

    return 0;
}
