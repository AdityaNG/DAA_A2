#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	int weight;
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
		
		int index = -1;

		node_t* head = &adjL[count];
		node_t* p = head;
		// loop through the line to extract all other tokens
		while( token != NULL ) {


			if (index==-1) {
				int d;
				sscanf(token, "%d", &d);
				//printf( " %d ", d ); //printing each token
				token = strtok(NULL, " ");
				index = d-1;

				p = &adjL[index];
			} else {
				int d1, d2;
				sscanf(token, "%d", &d1);

				//printf( " %d ", d ); //printing each token
				token = strtok(NULL, " ");
				sscanf(token, "%d", &d2);
				token = strtok(NULL, " ");
				
				if (0<d1) {
					p->data = d1;
					p->weight = d2;
					p->link = malloc(sizeof(node_t));
					p = p->link;
				}
			}

		}
		//printf("\n");
		p->link = NULL;
		count++;
	}
	
	fclose(fp);
	if (line)
		free(line);
	
	for (int i=0; i<n; i++) {
		printf("%d -> ", i+1);
		node_t* p = &adjL[i];
		while (p->data != 0) {
			printf("%d ", p->data);
			p = p->link;
		}
		printf("\n");
	}

	exit(EXIT_SUCCESS);
	return 0;
}
