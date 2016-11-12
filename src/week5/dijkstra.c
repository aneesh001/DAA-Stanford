#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAXLINE 1000
#define NUL '\0'

//******* THE REPRESENTATION OF THE GRAPH *******

#ifndef SIZE
	//size of the graph.
	#define SIZE 12
#endif

typedef struct node{
	int head;
	int weight;
	struct node *next;
}NODE;

NODE *graph[SIZE+1];
int visited[SIZE+1];

//functuons to manipulate the graph.
void read_graph(NODE **, FILE *f);
void print_graph(NODE **);
void free_graph(NODE **);
void insert(NODE **, int, int, int);
void reset_visits();

//CHANGE ACC. TO INPUT SPECIFICATION
void read_graph(NODE **g, FILE *f){
	char a[MAXLINE];
	while(fgets(a, MAXLINE, f)){
		//remove the newline at the end
		a[strlen(a)-3] = NUL;

		int v, w, wt;

		char *ch = a;
		v = atoi(ch);

		//advance past the first tab
		while(*(ch++) != '\t')
			;

		//read pairs of w,wt.
		while(*ch != NUL){
			w = atoi(ch);

			while(*(ch++) != ',')
				;

			wt = atoi(ch);

			while(*ch != NUL && *ch != '\t')
				++ch;
			if(*ch == '\t')
				++ch;

			// printf("%d %d %d\n", v, w, wt);
			insert(g, v, w, wt);
		}
	}
}

void print_graph(NODE **g){
	printf("The Graph:\n");
	for(int i = 1; i <= SIZE; ++i){
		printf("%d: ", i);
		NODE *nbr = g[i];
		while(nbr != NULL){
			printf("%d ", nbr->head);
			nbr = nbr->next;
		}
		printf("\n");
	}
}

void free_graph(NODE **g){
	for(int i = 0; i <= SIZE; ++i){
		NODE *cur_node = g[i];
		while(cur_node != NULL){
			NODE *next_node = cur_node->next;
			free(cur_node);
			cur_node = next_node;
		}
	}
}

void insert(NODE **g, int v, int w, int weight){
	assert((v >= 1 && v <= SIZE) && (w >= 1 && w <= SIZE));

	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->head = w;
	new_node->weight = weight;
	new_node->next = NULL;

	if(g[v] == NULL){
		g[v] = new_node;
	}
	else{
		new_node->next = g[v];
		g[v] = new_node;
	}
}

void reset_visits(){
	for(int i = 0; i <= SIZE; ++i){
		visited[i] = FALSE;
	}
}

// **********************************************

//Dijkstra's shortest path.
void dsp(NODE **, int);

//array to store shortest paths.
int dist[SIZE + 1];
int size_of_x = 0;

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: ./main <filename>\n");
		exit(1);
	}

	FILE *input = fopen(argv[1], "r");
	read_graph(graph, input);
	print_graph(graph);

	dsp(graph, 1);
	for(int i = 1; i <= SIZE; ++i){
		printf("%d ", dist[i]);
	}
	printf("\n");

	int i;
	while(scanf("%d", &i) == 1)
		printf("%d,", dist[i]);
	printf("\n");

	free_graph(graph);
	return EXIT_SUCCESS;
}

void dsp(NODE **g, int source_vertex){
	reset_visits();
	size_of_x = 0;

	visited[source_vertex] = TRUE;
	size_of_x++;
	dist[source_vertex] = 0;

	while(size_of_x < SIZE){
		int to_be_added_to_x = 0;
		int cur_shortest = INT_MAX;

		for(int i = 1; i <= SIZE; ++i){
			if(visited[i] == TRUE){
				NODE *nbr = g[i];

				while(nbr != NULL){
					if(visited[nbr->head] == FALSE && (cur_shortest >= dist[i] + nbr->weight)){
						cur_shortest = dist[i] + nbr->weight;
						to_be_added_to_x = nbr->head;
					}

					nbr = nbr->next;
				}
			}
		}

		dist[to_be_added_to_x] = cur_shortest;
		visited[to_be_added_to_x] = TRUE;
		size_of_x++;
	}
}