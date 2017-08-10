#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G 6.67*pow(10,-11)
#define M1 .08*1.989*pow(10,30)
#define M2 .85*5.9722*pow(10,24)

double f1(double v);
double f2(double r1, double r2);
double f3(double r1, double r2);
double r12(double x1, double x2, double y1, double y2);

void main()
{
    double t=0.0,dt=60.0,tMax=1.509*(24*60*60);

    double x1=0,x2=1.9889*pow(10,8),y1=0,y2=-1.651*pow(10,9),r=r12(x1,x2,y1,y2),r1,r2,r3;
    double v1=0,v2=79348.8,u1=0,u2=9078.256;
    double X1star,X1starstar,X1starstarstar,X2star,X2starstar,X2starstarstar,Y1star,Y1starstar,Y1starstarstar,Y2star,Y2starstar,Y2starstarstar;
    double X1star2,X1starstar2,v13,v21,v22,v23,u11,u12,u13,u21,u22,u23;

    FILE *fPointer = fopen("Problem_7_3.csv","w");

    printf("t: %.lf\tx1: %e\ty1: %e\tx2: %e\ty2: %e\n",t,x1,y1,x2,y2);
    fprintf(fPointer,"Time, X1, Y1, X2, Y2\n%lf, %.15lf, %.15lf, %.15lf, %.15lf",t,x1,y1,x2,y2);

    for(t=dt;t<tMax;t+=dt)
    {
        //r12 for star
        r = r12(x1,x2,y1,y2);

        //use f1 for set 1
        X1star = x1 + .5*dt*f1(v1);
        Y1star = y1 + .5*dt*f1(u1);
        X2star = x2 + .5*dt*f1(v2);
        Y2star = y2 + .5*dt*f1(u2);

        //use f2 for set 1
        X1star2 = v1 + .5*dt*f2(x1,x2)/r;
        u11 = u1 + .5*dt*f2(y1,y2)/r;

        //use f3 for set 1
        v21 = v2 + .5*dt*f3(x1,x2)/r;
        u21 = u2 + .5*dt*f3(y1,y2)/r;

        //r12 for starstar
        r1 = r12(X1star,X2star,Y1star,Y2star);

        //use f1 for set 2
        X1starstar = x1 + .5*dt*f1(X1star2);
        Y1starstar = y1 + .5*dt*f1(u11);
        X2starstar = x2 + .5*dt*f1(v21);
        Y2starstar = y2 + .5*dt*f1(u21);

        //use f2 for set 2
        X1starstar2 = v1 + .5*dt*f2(X1star,X2star)/r1;
        u12 = u1 + .5*dt*f2(Y1star,Y2star)/r1;

        //use f3 for set 2
        v22 = v2 + .5*dt*f3(X1star,X2star)/r1;
        u22 = u2 + .5*dt*f3(Y1star,Y2star)/r1;

        //r12 for starstarstar
        r2 = r12(X1starstar,X2starstar,Y1starstar,Y2starstar);

        //use f1 for set 3
        X1starstarstar = x1 + dt*f1(X1starstar2);
        Y1starstarstar = y1 + dt*f1(u12);
        X2starstarstar = x2 + dt*f1(v22);
        Y2starstarstar = y2 + dt*f1(u22);

        //use f2 for set 3
        v13 = v1 + dt*f2(X1starstar,X2starstar)/r2;
        u13 = u1 + dt*f2(Y1starstar,Y2starstar)/r2;

        //use f3 for set 3
        v23 = v2 + dt*f3(X1starstar,X2starstar)/r2;
        u23 = u2 + dt*f3(Y1starstar,X2starstar)/r2;

        //r12 for final new values
        r3 = r12(X1starstarstar,X2starstarstar,Y1starstarstar,Y2starstarstar);

        x1 = x1 + dt/6*(f1(v1) + 2*f1(X1star2) + 2*f1(X1starstar2) + f1(v13));                                  //f1
        v1 = v1 + dt/6*(f2(x1,x2)/r + 2*f2(X1star,X2star)/r1 + 2*f2(X1starstar,X2starstar)/r2 + f2(X1starstarstar,X2starstarstar)/r3);    //f2
        y1 = y1 + dt/6*(f1(u1) + 2*f1(u11) + 2*f1(u12) + f1(u13));                                  //f1
        u1 = u1 + dt/6*(f2(y1,y2)/r + 2*f2(Y1star,Y2star)/r1 + 2*f2(Y1starstar,Y2starstar)/r2 + f2(Y1starstarstar,Y2starstarstar)/r3);    //f2
        x2 = x2 + dt/6*(f1(v2) + 2*f1(v21) + 2*f1(v22) + f1(v23));                                  //f1
        v2 = v2 + dt/6*(f3(x1,x2)/r + 2*f3(X1star,X2star)/r1 + 2*f3(X1starstar,X2starstar)/r2 + f3(X1starstarstar,X2starstarstar)/r3);    //f3
        y2 = y2 + dt/6*(f1(u2) + 2*f1(u21) + 2*f1(u22) + f1(u23));                                  //f1
        u2 = u2 + dt/6*(f3(y1,y2)/r + 2*f3(Y1star,Y2star)/r1 + 2*f3(Y1starstar,Y2starstar)/r2 + f3(Y1starstarstar,Y2starstarstar)/r3);    //f3

        printf("t: %.lf\tx1: %e\ty1: %e\tx2: %e\ty2: %e\n",t,x1,y1,x2,y2);
        fprintf(fPointer,"\n%lf, %.15lf, %.15lf, %.15lf, %.15lf",t,x1,y1,x2,y2);
    }
    fclose(fPointer);
}

double f1(double v)
{
    return v;
}

double f2(double r1, double r2)
{
    double a = -1*G*M2*(r1-r2);
    return a;
}

double f3(double r1, double r2)
{
    double a = -1*G*M1*(r2-r1);
    return a;
}

double r12(double x1, double x2, double y1, double y2)
{
    double r = pow((pow((x1-x2),2) + pow((y1-y2),2)),1.5);
    return r;
}
