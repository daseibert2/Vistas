#include <stdio.h>

int main() {

	int n;
	int i;
	int j;

	printf("Please enter a number: \n");
	scanf("%d", &n);

	char m[n][n];

	for(i = 0; i <= n ; i++)
	{
	    printf("\n"); //figure out spacing issue

	    for(j = 0; j <= n ; j++)
	    {
	        //need four diff if statements here corresponding to four quads
	        if(i < (n / 2) && j < (n / 2))
	            printf("a");
	        else if(i > (n / 2) && j < (n / 2))
	            printf("c");
	        else if(i < (n / 2) && j > (n / 2))
	            printf("b");
	        else if(i > (n / 2) && j > (n / 2))
	            printf("d");

	    }

	}


	return 0;
}

