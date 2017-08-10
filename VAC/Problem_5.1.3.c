#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M1 0.08*(1.989*pow(10,30))
#define M2 0.85*(5.9722*pow(10,24))
#define G 6.67*pow(10,-11)

double f_r12(double x1, double x2, double y1, double y2)
{
    double v;
    v=sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
    return v;
}

double f_r1(double r1,double r2,double r12)
{
    double x;
    x=-((G*M2*(r1-r2))/pow(r12,3));

    return x;
}

double f_r2(double r1,double r2,double r12)
{
    double x;
    x=-((G*M1*(r1-r2))/pow(r12,3));

    return x;
}

double f_x1(double r12, double y1, double y2, double x2)
{
    double w;
    w=sqrt(r12*r12-(pow((y1-y2),2)))+x2;
    return w;
}

double funct(double r,double x)
{
    x=sqrt((sqrt((x*x)-(r*r)))-(r*r));

    return x;
}

double df(double r, double x)
{
    x=(1.0/2)*abs( pow( -pow(r,2) + pow( abs( pow(x,2)- pow(r,2) ),(1.0/2) ) ,-(1.0/2) ) *abs (2*r-(1.0/2)*(pow(pow(x,2)-pow(r,2),(-1.0/2)))) * abs(2*x-2*r) );

    return x;
}

double Raul(double x1, double r)
{
    x1=x1-((funct(r,x1))/df(r,x1));

    return x1;
}
//----------------------------------------------------------------------------------------------------------------------------------
double RK(double max,FILE *fptr)
{
    double X1star,X1starstar,X1starstarstar,Y1star,Y1starstar,Y1starstarstar,newX1,newY1,t=0.0;
    double X2star,X2starstar,X2starstarstar,Y2star,Y2starstar,Y2starstarstar,newX2,newY2;
    double X1star2,X1starstar2,X1starstarstar2,Y1star2,Y1starstar2,Y1starstarstar2,newX1_2,newY1_2;
    double X2star2,X2starstar2,X2starstarstar2,Y2star2,Y2starstar2,Y2starstarstar2,newX2_2,newY2_2;
    double r1,r2,newR1,newR2,newR1_2,newR2_2,newR1_4,newR2_4;
    double x1=0.0,y1=0.0,x2=0.0,y2=0.0, x1_2=1.9889*pow(10,8),y1_2=-1.651*pow(10,9),x2_2=79348.8,y2_2=9078.256,DT=0.01;

    fprintf(fptr,"%lf, %lf, %lf, %lf, %lf\n",t,x1,y1,x2,y2);

    for(t=DT;t<=max;t+=DT)
    {
        //r1
        X1star=x1+DT/2*f_x1(f_r12(x1,x1_2,y1,y1_2),y1,y1_2,x1_2);
        X2star=x1_2+DT/2*-(f_x1(f_r12(x1,x1_2,y1,y1_2),y1,y1_2,x1));
        Y1star=y1+DT/2*f_x1(f_r12(x1,x1_2,y1,y1_2),x1,x1_2,y1_2);
        Y2star=y1_2+DT/2*-(f_x1(f_r12(x1,x1_2,y1,y1_2),x1,x1_2,y1));

        X1starstar=x1+DT/2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),Y1star,Y2star,X2star);
        X2starstar=x1_2+DT/2*-(f_x1(f_r12(X1star,X2star,Y1star,Y2star),Y1star,Y2star,X1star));
        Y1starstar=y1+DT/2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),X1star,X2star,Y2star);
        Y2starstar=y1_2+DT/2*-(f_x1(f_r12(X1star,X2star,Y1star,Y2star),X1star,X2star,Y1star));

        X1starstarstar=x1+DT*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),Y1starstar,Y2starstar,X2starstar);
        X2starstarstar=x1_2+DT*-(f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),Y1starstar,Y2starstar,X1starstar));
        Y1starstarstar=y1+DT*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),X1starstar,X2starstar,Y2starstar);
        Y2starstarstar=y1_2+DT*-(f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),X1starstar,X2starstar,Y1starstar));

        newX1=x1+DT/6*(f_x1(f_r12(x1,x1_2,y1,y1_2),y1,y1_2,x1_2)+2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),Y1star,Y2star,X2star)+
                       2*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),Y1starstar,Y2starstar,X2starstar)+
                       f_x1(f_r12(X1starstarstar,X2starstarstar,Y1starstarstar,Y2starstarstar),Y1starstarstar,Y2starstarstar,X2starstarstar));
        newX2=x1_2+DT/6*(-f_x1(f_r12(x1,x1_2,y1,y1_2),y1,y1_2,x1)+2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),Y1star,Y2star,X1star)+
                       2*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),Y1starstar,Y2starstar,X1starstar)+
                       f_x1(f_r12(X1starstarstar,X2starstarstar,Y1starstarstar,Y2starstarstar),Y1starstarstar,Y2starstarstar,X1starstarstar));
        newY1=y1+DT/6*(f_x1(f_r12(x1,x1_2,y1,y1_2),x1,x1_2,y1_2)+2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),X1star,X2star,Y2star)+
                       2*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),X1starstar,X2starstar,Y2starstar)+
                       f_x1(f_r12(X1starstarstar,X2starstarstar,Y1starstarstar,Y2starstarstar),X1starstarstar,X2starstarstar,Y2starstarstar));
        newY2=y1_2+DT/6*(-f_x1(f_r12(x1,x1_2,y1,y1_2),x1,x1_2,y1)+2*f_x1(f_r12(X1star,X2star,Y1star,Y2star),X1star,X2star,Y1star)+
                       2*f_x1(f_r12(X1starstar,X2starstar,Y1starstar,Y2starstar),X1starstar,X2starstar,Y1starstar)+
                       f_x1(f_r12(X1starstarstar,X2starstarstar,Y1starstarstar,Y2starstarstar),X1starstarstar,X2starstarstar,Y1starstarstar));

        newR1=sqrt(newX1*newX1+newY1*newY1);
        newR2=sqrt(newX2*newX2+newY2*newY2);

//--------------------------------------------------------------------------------------------------------------------------------------------

        //r2
        X1star2=x2+DT/2*f_x1(f_r12(x2,x2_2,y2,y2_2),y2,y2_2,x2_2);
        X2star2=x2_2+DT/2*-(f_x1(f_r12(x2,x2_2,y2,y2_2),y2,y2_2,x2));
        Y1star2=y2+DT/2*f_x1(f_r12(x2,x2_2,y2,y2_2),x2,x2_2,y2_2);
        Y2star2=y2_2+DT/2*-(f_x1(f_r12(x2,x2_2,y2,y2_2),x2,x2_2,y2));

        X1starstar2=x2+DT/2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),Y1star2,Y2star2,X2star2);
        X2starstar2=x2_2+DT/2*-(f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),Y1star2,Y2star2,X1star2));
        Y1starstar2=y2+DT/2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),X1star2,X2star2,Y2star2);
        Y2starstar2=y2_2+DT/2*-(f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),X1star2,X2star2,Y1star2));

        X1starstarstar2=x2+DT*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),Y1starstar2,Y2starstar2,X2starstar2);
        X2starstarstar2=x2_2+DT*-(f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),Y1starstar2,Y2starstar2,X1starstar2));
        Y1starstarstar2=y2+DT*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),X1starstar2,X2starstar2,Y2starstar2);
        Y2starstarstar2=y2_2+DT*-(f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),X1starstar2,X2starstar2,Y1starstar2));

        newX1_2=x2+DT/6*(f_x1(f_r12(x2,x2_2,y2,y2_2),y2,y2_2,x2_2)+2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),Y1star2,Y2star2,X2star2)+
                       2*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),Y1starstar2,Y2starstar2,X2starstar2)+
                       f_x1(f_r12(X1starstarstar2,X2starstarstar2,Y1starstarstar2,Y2starstarstar2),Y1starstarstar2,Y2starstarstar2,X2starstarstar2));
        newX2_2=x2_2+DT/6*(-f_x1(f_r12(x2,x2_2,y2,y2_2),y2,y2_2,x2)+2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),Y1star2,Y2star2,X1star2)+
                       2*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),Y1starstar2,Y2starstar2,X1starstar2)+
                       f_x1(f_r12(X1starstarstar2,X2starstarstar2,Y1starstarstar2,Y2starstarstar2),Y1starstarstar2,Y2starstarstar2,X1starstarstar2));
        newY1_2=y1_2+DT/6*(f_x1(f_r12(x1_2,x2_2,y1_2,y2_2),x1_2,x2_2,y2_2)+2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),X1star2,X2star2,Y2star2)+
                       2*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),X1starstar2,X2starstar2,Y2starstar2)+
                       f_x1(f_r12(X1starstarstar2,X2starstarstar2,Y1starstarstar2,Y2starstarstar2),X1starstarstar2,X2starstarstar2,Y2starstarstar2));
        newY2_2=y2_2+DT/6*(-f_x1(f_r12(x2,x2_2,y2,y2_2),x2,x2_2,y2)+2*f_x1(f_r12(X1star2,X2star2,Y1star2,Y2star2),X1star2,X2star2,Y1star2)+
                       2*f_x1(f_r12(X1starstar2,X2starstar2,Y1starstar2,Y2starstar2),X1starstar2,X2starstar2,Y1starstar2)+
                       f_x1(f_r12(X1starstarstar2,X2starstarstar2,Y1starstarstar2,Y2starstarstar2),X1starstarstar2,X2starstarstar2,Y1starstarstar2));

        newR1_2=sqrt(newX1_2*newX1_2+newY1_2*newY1_2);
        newR2_2=sqrt(newX2_2*newX2_2+newY2_2*newY2_2);


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
        newR1_4=f_r1(newR1,newR2,f_r12(newX1,newX2,newY1,newY2));

        newR2_4=f_r2(newR1_2,newR2_2,f_r12(newX1_2,newX2_2,newY1_2,newY2_2));

        //Figure out how to find new x and y's
        //r=sqrt(x^2+y^2)
        r1=newR1_4;
        r2=newR2_4;

        x1=Raul(newX1,r1);
        x2=Raul(newX2,r1);
        y1=Raul(newY1,r2);
        y2=Raul(newY2,r2);

        fprintf(fptr,"%lf, %lf, %lf, %lf, %lf\n",t,x1,y1,x2,y2);
        printf("x1(%lf): %lf\t\ty1(%lf): %lf\t\tx2(%lf): %lf\t\ty2(%lf): %lf\n\n",t,x1,t,y1,t,x2,t,y2);
    }

}

int main()
{
    FILE *fptr;
    //remove("Planet_Data.csv");
    fptr=fopen("Planet_Data.csv","w");
    fprintf(fptr,"t, x1, y1, x2, y2\n");
   // printf("Problem 7.1.1\n\n");


    RK(10,fptr);

    fclose(fptr);

    return 0;
}

