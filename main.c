#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	
	fp = fopen("adjacencylist.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	while ((read = getline(&line, &len, fp)) != -1) {
		//printf("Retrieved line of length %zu:\n", read);
		//printf("%s", line);

		char * token = strtok(line, " ");
		// loop through the string to extract all other tokens
		while( token != NULL ) {
			int d;
			sscanf(token, "%d", &d);
			printf( " %d ", d ); //printing each token
			token = strtok(NULL, " ");
		}
		printf("\n");
	}
	
	fclose(fp);
	if (line)
		free(line);
	
	exit(EXIT_SUCCESS);
	return 0;
}
