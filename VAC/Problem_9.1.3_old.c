#include <stdio.h>
#include <math.h>

int main()
{
    int N=4;
    double A=1,Q=10,L=1,h=L/N;


    double alpha[N],g[N],a[N],f[N],b[N],c[N],u[N],error[N],e1,e2,e=0;
    f[0]=40.8;u[0]=0;u[1]=0;

    for (int i=0;i<N+1;i++)
    {
        a[i]=2+(A*A*h*h);
        b[i]=-1.0;
        c[i]=-1.0;
        f[i]=h*h*exp(-Q*i);
    }

    for(int j=1;j<N+1;j++)
    {
        a[j]=a[j]-((b[j]*c[j-1])/a[j-1]);
        f[j]=f[j]-(b[j]/a[j-1])*f[j-1];
    }

    u[N-1]=f[N-1]/a[N-1];
    f[0]+=u[0];
    f[N-1]+=u[N-1];

    for(int k=1;k<N-1;k++)
    {
        u[N-k]=(f[N-k]-(c[N-k]*u[N-k+1]))/a[N-k];
    }

    e1=exp(-Q*0)*(((A*cos(h)*(A*0))+(Q*sin(h)*(A*0)))/(A*A-Q*Q));
    e2=exp(-Q*1)*(((A*cos(h)*(A*1))+(Q*sin(h)*(A*1)))/(A*A-Q*Q));
    e=fabs(e1-e2);
    printf("Exact: %.20lf\n\n",e);

    for(int w=N-1;w>-1;w--)
    {

        u[w]=(f[w]-(c[w]*u[w+1]))/a[w];
        /*if(w>0)
            error[w]=fabs((e-u[w])/w)*100;
        else
            error[w]=fabs(e-u[w])*100;*/
        error[w]=fabs((e-u[w])/e);
        printf("\nu(%d): %.20lf\tError: %.20lf\n",w,u[w],error[w]);

    }

    return 0;
}
