#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXSIZE 875714

#ifndef SIZE
#define SIZE MAXSIZE
#endif

#define TRUE 1
#define FALSE 0

typedef struct node{
	long head;
	struct node* next;
}NODE;

NODE *graph[SIZE + 1];
NODE *rev_graph[SIZE + 1];
int visited[SIZE + 1];
long t[SIZE + 1];
long curr_time = 0;
int cur_leader = 0;
long leaders_group_size[SIZE];
void reset_visits();

void read_graphs(FILE *f);
void insert(NODE **, int, int);
void print_graph(NODE **);
void free_graph(NODE **);

//Used to compute finishing times.
void compute_finishing_times(NODE **);
void DFS_ft(NODE **, int starting_vertex);
void print_finishing_times();

//Used to compute finals SCCs
void compute_scc(NODE **);
void DFS_scc(NODE **, int starting_vertex);
void print_leaders_group_size();
void top_5_scc();

//misc
int comp(const void *a, const void *b);

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: ./scc <filename>\n");
		exit(1);
	}

	FILE *input = fopen(argv[1], "r");
	read_graphs(input);
	// print_graph(graph);
	// print_graph(rev_graph);

	compute_finishing_times(rev_graph);
	// print_finishing_times();
	reset_visits();

	compute_scc(graph);
	// print_leaders_group_size();
	top_5_scc();

	free_graph(graph);
	free_graph(rev_graph);
}

void read_graphs(FILE *f){
	int v, w;
	while(fscanf(f, "%d %d", &v, &w) == 2){
		insert(graph, v, w);
		insert(rev_graph, w, v);
	}
}

void insert(NODE **g, int v, int w){
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->head = w;
	new_node->next = NULL;

	assert(v <= SIZE && w <= SIZE);

	if(g[v] == NULL){
		g[v] = new_node;
	}
	else{
		new_node->next = g[v];
		g[v] = new_node;
	}
}

void free_graph(NODE **g){
	for(int i = 0; i <= SIZE; ++i){
		if(g[i] == NULL)
			continue;
		else{
			// printf("In else\n");
			NODE *curr = g[i];
			NODE *after = NULL;

			while(curr != NULL){
				after = curr->next;
				free(curr);
				curr = after;
			}
		}
	}
}

void print_graph(NODE **g){
	printf("The Graph: \n");
	for(int i = 1; i <= SIZE; ++i){
		printf("%d ", i);
		NODE *curr = g[i];
		while(curr != NULL){
			printf("%d ", curr->head);
			curr = curr->next;
		}
		printf("\n");
	}
}

void reset_visits(){
	for(int i = 0; i <= SIZE; ++i)
		visited[i] = FALSE;
}

void compute_finishing_times(NODE **g){
	for(int i = SIZE; i >= 1; --i){
		if(visited[i] == FALSE){
			DFS_ft(g, i);
		}
	}
}

void DFS_ft(NODE **g, int starting_vertex){
	visited[starting_vertex] = TRUE;
	NODE *curr = g[starting_vertex];
	while(curr != NULL){
		if(visited[curr->head] == FALSE)
			DFS_ft(g, curr->head);
		curr = curr->next;
	}
	++curr_time;
	t[curr_time] = starting_vertex;
}

void print_finishing_times(){
	for(int i = 1; i <= SIZE; ++i)
		printf("%d ", t[i]);
	printf("\n");
}

void compute_scc(NODE **g){
	for(int i = SIZE; i >= 1; --i){
		if(visited[t[i]] == FALSE){
			cur_leader = i;
			DFS_scc(g, t[i]);
		}
	}
}

void DFS_scc(NODE **g, int starting_vertex){
	visited[starting_vertex] = TRUE;
	leaders_group_size[cur_leader]++;

	NODE *curr = g[starting_vertex];
	while(curr != NULL){
		if(visited[curr->head] == FALSE){
			DFS_scc(g, curr->head);
		}
		curr = curr->next;
	}
}

void print_leaders_group_size(){
	for(int i = 1; i <= SIZE; ++i){
		if(leaders_group_size[i] != 0)
			printf("%d\n", leaders_group_size[i]);
	}
}

//to sort in non increasing order.
int comp(const void *a, const void *b){
	return (*(long*)b - *(long*)a);
}

void top_5_scc(){
	qsort(leaders_group_size, SIZE + 1, sizeof(long), comp);
	for(int i = 0; i < 5; ++i)
		printf("%ld,", leaders_group_size[i]);
	printf("\n");
}