#include <stdio.h>
#include <math.h>
#include <time.h>

#define BOUND 20000000

void* isPrime(void* context) {
	double* n = (double*) context;
	
	int* result;
	int k = sqrt(*n)+1;
	int i = 1;

	for(; i <= k; i++) {
		if((int)*n % i == 0) {
			*result = 0;
			return (void*)result;
		}
	}
	
	*result = 1;
	return (void*)result;
}

int main() {
	time_t t1 = time(NULL);
	
	int i = 2;
	int c = 0;

	for(; i < BOUND; i++) {
		if(isPrime(i)) {
			c++;
		}
	}
	
	printf("%d\n", c);

	time_t t2 = time(NULL);
	double delta = difftime(t2, t1);
	printf("%.0f\n", delta);

	return 0;
}
