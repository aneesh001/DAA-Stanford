#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <cstdio>
#include "graph.h"

//finish-times of vertices in reverse graph.
std::vector<int> finish_times;

//the SCCs of the graph.
std::map<int, int> scc;

void init_finish_times(graph::size_type);
void construct_rev_graph(graph &src, graph &dest);
void compute_finish_times(graph &g);
void DFS_finish_times(graph &g, int start_vertex, int &t);
void print_finish_times();
void compute_scc(graph &g);
void DFF_scc(graph &g, int start_vertex, int leader);
std::ostream& print_scc(std::ostream &);

int main(int argc, char *argv[]){
	if(argc != 2){
		std::cerr << "Usage: ./main <filename>\n";
		return EXIT_FAILURE;
	}

	std::ifstream input(argv[1]);
	// FILE *input = fopen(argv[1], "r");
	std::ofstream output("sccs.txt");
	int size = 875714;

	// input >> size;
	graph g1(size);
	input >> g1;
	std::cerr << "Input done!" << std::endl;
	// std::cout << g1;

	compute_scc(g1);
	print_scc(output);

	return 0;
}

void init_finish_times(graph::size_type sz){
	for(decltype(sz) i = 0; i <= sz; ++i)
		finish_times.push_back(0);
}

void print_finish_times(){
	for(int i = 1; i < finish_times.size(); ++i)
		std::cout << finish_times[i] << " ";
	std::cout << std::endl;
}

void construct_rev_graph(graph &src, graph &dest){
	for(auto iter = src.begin(); iter != src.end(); ++iter){
		for(auto i: iter->second)
			dest.add_edge(i, iter->first);
	}
}

void compute_finish_times(graph &g){
	init_finish_times(g.size());
	graph g_rev(g.size());
	construct_rev_graph(g, g_rev);
	std::cerr << "Reverse graph made!" << std::endl;
	int t = 0;
	for(auto it = g_rev.rbegin(); it != g_rev.rend(); ++it){
		if(!it->second.is_visited()){
			DFS_finish_times(g_rev, it->first, t);
		}
	}

	std::cerr << "Finish times found!" << std::endl;
}

void DFS_finish_times(graph &g, int start_vertex, int &t){
	g[start_vertex].set_visited(true);
	for(auto iter = g[start_vertex].begin(); iter != g[start_vertex].end(); ++iter){
		if(!g[*iter].is_visited())
			DFS_finish_times(g, *iter, t);
	}
	++t;
	g[start_vertex].set_fin_time(t);
	finish_times[t] = start_vertex;
}

void compute_scc(graph &g){
	compute_finish_times(g);
	// print_finish_times();
	int cur_leader = 0;
	for(auto iter = finish_times.rbegin(); iter != finish_times.rend() - 1; ++iter){
		// std::cout << "vertex " << *iter << std::endl;
		if(!g[*iter].is_visited()){
			cur_leader = *iter;
			// std::cout << "cur_leader: " << cur_leader << std::endl;
			DFF_scc(g, *iter, cur_leader);
		}
	}

	std::cerr << "SCCs found!" << std::endl;
}

void DFF_scc(graph &g, int start_vertex, int leader){
	g[start_vertex].set_visited(true);
	g[start_vertex].set_src(leader);
	scc[leader] += 1;
	for(auto iter = g[start_vertex].begin(); iter != g[start_vertex].end(); ++iter){
		if(!g[*iter].is_visited())
			DFF_scc(g, *iter, leader);
	}
}

std::ostream& print_scc(std::ostream &output){
	for(auto item: scc){
		output /*<< "Leader: " << item.first << " : "*/ << item.second << std::endl;
	}
	std::cerr << "DONE!" << std::endl;
}