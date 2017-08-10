#include <stdio.h>
#include <math.h>
#define DT 0.01

double fa(double t, double u)
{
    double x;
    x=(pow(t,3)*u)-((3.0/2)*u);
    return x;
}

double fb(double x, double u)
{
    double y;
    y=(1+2*x)*sqrt(u);
    return y;
}

double Euler(double max)
{
    double u=1,nu,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        nu=u+DT*fa(t,u);
        x=exp((1.0/4)*pow(t,4)-(3.0/2)*t);
        u=nu;
    }
    printf("Euler's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double Midpoint(double max)
{
    double u=1,nu,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        nu=u+DT*fa(t+DT/2,u+DT/2*fa(t,u));
        x=exp((1.0/4)*pow(t,4)-(3.0/2)*t);
        u=nu;
    }
    printf("Midpoint: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double Heun(double max)
{
    double u=1,nu,ustar,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        ustar=u+DT*fa(t,u);
        nu=u+DT/2*(fa(t,u)+fa(t+DT,ustar));
        x=exp((1.0/4)*pow(t,4)-(3.0/2)*t);
        u=nu;
    }
    printf("Heun's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double RK(double max)
{
    double u=1,nu,ustar,ustarstar,ustarstarstar,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        ustar=u+DT/2*fa(t,u);
        ustarstar=u+DT/2*fa(t+DT/2,ustar);
        ustarstarstar=u+DT*fa(t,ustarstar);
        nu=u+DT/6*(fa(t,u)+2*fa(t+DT/2,ustar)+2*fa(t+DT/2,ustarstar)+fa(t,ustarstarstar));
        x=exp((1.0/4)*pow(t,4)-(3.0/2)*t);
        u=nu;
    }
    printf("Runge-Kutta's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}


double Euler2(double max)
{
    double u=1,nu,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        nu=u+DT*fb(t,u);
        x=(1.0/4)*pow((2+t+(t*t)),2);
        u=nu;
    }
    printf("Euler's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double Midpoint2(double max)
{
    double u=1,nu,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        nu=u+DT*fb(t+DT/2,u+DT/2*fb(t,u));
        x=(1.0/4)*pow((2+t+(t*t)),2);
        u=nu;
    }
    printf("Midpoint: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double Heun2(double max)
{
    double u=1,nu,ustar,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        ustar=u+DT*fb(t,u);
        nu=u+DT/2*(fb(t,u)+fb(t+DT,ustar));
        x=(1.0/4)*pow((2+t+(t*t)),2);
        u=nu;
    }
    printf("Heun's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

double RK2(double max)
{
    double u=1,nu,ustar,ustarstar,ustarstarstar,x,t;

    for(t=DT;t<=max;t+=DT)
    {
        ustar=u+DT/2*fb(t,u);
        ustarstar=u+DT/2*fb(t+DT/2,ustar);
        ustarstarstar=u+DT*fb(t,ustarstar);
        nu=u+DT/6*(fb(t,u)+2*fb(t+DT/2,ustar)+2*fb(t+DT/2,ustarstar)+fb(t,ustarstarstar));
        x=(1.0/4)*pow((2+t+(t*t)),2);
        u=nu;
    }
    printf("Runge-Kutta's: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",t,nu,x);
}

void PartA()
{
    double max=2;
    printf("Part A:\n\n");
   Euler(max);
   printf("\n\n");
   Midpoint(max);
   printf("\n\n");
   Heun(max);
   printf("\n\n");
   RK(max);
   printf("\n\n\n");
}

void PartB()
{
    double max=1;
    printf("Part B:\n\n");
   Euler2(max);
   printf("\n\n");
   Midpoint2(max);
   printf("\n\n");
   Heun2(max);
   printf("\n\n");
   RK2(max);
}

double funct(double u,double e)
{
    double y=1.0/(e*u*u);

    return y;
}

double df(double u, double e)
{
    double y=-2.0/(e*pow(u,3));

    return y;
}

double Raul(double u, double e)
{
    u=u-((funct(u,e))/df(u,e));

    return u;
}

double Trapezoidal(double e)
{
    double t,x,nu,tempu,u=1.0;
    for(t=DT;t<=1.0;t+=DT)
    {
       tempu=Raul(u,e);
       nu=u+(DT/2)*(funct(u,e)+funct(tempu,e));
       x=cbrt(1+3*t/e);
       u=nu;
    }
    printf("Trapezoidal for e=%lf: u(%lf):\tApprox.: %lf\t\tExact: %lf\n",e,t,nu,x);

    return u;
}

void trape(double e)
{
    Trapezoidal(e);
    printf("\n\n");
}

int main()
{
    printf("Problem 5.1.4\n\n");
   PartA();
   PartB();
   printf("\n\nProblem 5.1.5\n\n");
   trape(1);
   trape(pow(10,-3));
    return 0;
}
