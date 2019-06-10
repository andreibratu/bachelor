#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {
	int p2c[2];
	int c2p[2];
	pipe(p2c);
	pipe(c2p);
	if(fork() == 0) {
		close(p2c[1]);
		close(c2p[0]);

		int q;
		char word[20];
		
		read(p2c[0], &q, sizeof(int));

		while(q) {
			int n = 0;
			while(read(p2c[0], &word[n], 1) && word[n]) {
				n++;
			}
			
			int c = 0;
			int j = 0;
			
			while(word[j]) {
				if(word[j] == 'o') c++;
				j++;
			}
			
			write(c2p[1], &c, sizeof(int));
			
			q--;
		}

		exit(0);
	}
	else {
		close(p2c[0]);
		close(c2p[1]);

		int i = 1;
		write(p2c[1], &argc, sizeof(int));
		for(; i < argc; i++) {
			int how_many;
			
			printf("P -> C %s\n", argv[i]);
			
			write(p2c[1], argv[i], strlen(argv[i])+1);
			read(c2p[0], &how_many, sizeof(int));
			
			printf("%s %d\n", argv[i], how_many);
		}

		wait(0);
	}
	return 0;
}
