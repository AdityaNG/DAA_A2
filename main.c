#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node* link;
} node_t;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	
	fp = fopen("adjacencylist.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	int n;
	fscanf(fp, "%d\n", &n);
	node_t *adjL = (node_t*) malloc(sizeof(node_t) * n);

	int count = 0;

	while ((read = getline(&line, &len, fp)) != -1) {
		char * token = strtok(line, " ");
		
		node_t* head = &adjL[count];
		node_t* p = head;
		// loop through the line to extract all other tokens
		while( token != NULL ) {
			int d;
			sscanf(token, "%d", &d);
			//printf( " %d ", d ); //printing each token
			token = strtok(NULL, " ");

			p->data = d;
			p->link = malloc(sizeof(node_t));
			p = p->link;

		}
		//printf("\n");
		p->link = NULL;
		count++;
	}
	
	fclose(fp);
	if (line)
		free(line);
	
	for (int i=0; i<n; i++) {
		printf("%d -> ", i);
		node_t* p = &adjL[i];
		while (p != NULL) {
			printf("%d ", p->data);
			p = p->link;
		}
		printf("\n");
	}

	exit(EXIT_SUCCESS);
	return 0;
}
