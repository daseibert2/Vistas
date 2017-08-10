#include <stdio.h>

int main() {

	int i;
	int n;
	char word[20];

	printf("Enter a word (11 char max): ");

	gets(word);
	n = strlen(word);
	puts(word);

	printf("\nYour word backwards is: ");

	for(i = n-1; i >= 0; --i) {

	     printf("%c", word[i]);
	}

	return 0;
}


