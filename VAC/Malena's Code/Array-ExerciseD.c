//c matrices
#include <stdio.h>

int main() {

	char letter[5] = {'A','B','C','D','E'};
	int i = 0;
	int j = 0;

	for(i = 0; i!=5; i++) {
	    for(j = i; j>=0; j--) {
	        printf("%c", letter[j]);
	    }
	    printf("\n");
	}

	return 0;
}
