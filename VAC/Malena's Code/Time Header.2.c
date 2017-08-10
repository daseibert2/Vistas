#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {

	int i;
	int n;
	char word[20];
	time_t start;
	time_t end;
	double sec;

	printf("Enter a word (11 char max): ");

	gets(word);
	n = strlen(word);
	puts(word);

	printf("\nYour word backwards is: ");

    start = clock();

	for(i = n-1; i >= 0; --i) {

	     printf("%c", word[i]);
	}

	end = clock();
	sec = (double) (end - start)/CLOCKS_PER_SEC; //Not working

	printf("\nThe loop took %f sec", sec);

	return 0;
	}
