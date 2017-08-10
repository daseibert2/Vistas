#include <stdio.h>

void swap ( int *x, int *y )
{
    int temp;

    printf(" x=%d y=%d\n", x, y ) ; //prints x = 44, y = 77
    temp = *x; //temp = 44.
    *x = *y; //x = 77
    *y = temp; //y = 44
    printf(" x=%d y =%d\n", x, y ) ; //prints x=77 y=44

}

void main ( void )
{
    int a = 44, b = 77 ;

    printf("a=%d b=%d\n", a, b ) ; //prints a=44 b=77
                                   //prints x=44 y=77
    swap( &a, &b ) ;                 //prints x=77 y=44
    printf("a=%d b=%d\n", a, b ) ; //prints a=44 b=77
                                   //PROBLEM: doesn't swap a and b. Swaps x and y.

    system("pause") ;
}
