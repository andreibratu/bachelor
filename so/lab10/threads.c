#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

void *uppercaseMeDaddy(void* context) {
	char* word = (char*) context;
	int j = 0;
	while(word[j]) {
		word[j] = toupper(word[j]);
		j++;
	}

	return NULL;
}


int main(int argc, char** argv) {
	pthread_t* threads = (pthread_t*) malloc(argc*sizeof(pthread_t));
	int i = 1;
	for(; i < argc; i++) {
		pthread_create(&threads[i], NULL, uppercaseMeDaddy, argv[i]);
	}

	for(i=1; i < argc; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d: %s\n", i, argv[i]);
	}
	
	free(threads);

	return 0;
}
