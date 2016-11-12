#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using std::string;
using std::vector;
using std::map;
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::istringstream;
using std::pair;
using std::make_pair;

//TO MAKE THIS FASTER, use list<int> instead of vector<int>
using Graph = map<int, vector<int>>;

istream& read_graph(Graph &, istream &);
ostream& print_graph(Graph &, ostream &);
void contract(Graph &g, int u, int v);
bool edge_exists(Graph &, int, int);
int cut(Graph &g);
int karger_min_cut(Graph &g);
void copy_graph(Graph &, Graph &);

int main(void){
	std::ifstream in("input.txt");

	Graph my_graph;
	read_graph(my_graph, in);
	print_graph(my_graph, cout);
	cout << karger_min_cut(my_graph) << std::endl;

	return 0;
}

bool edge_exists(Graph &g, int u, int v){
	auto it = g.find(u);
	if(it != g.end()){
		auto lt = find(it->second.begin(), it->second.end(), v);
		return lt != it->second.end();
	}
	else
		return false;
}

istream& read_graph(Graph &g, istream &input){
	string line;
	while(std::getline(input, line)){
		istringstream in(line);

		//add the vertex to the graph
		int vertex_number;
		in >> vertex_number;
		g.insert(make_pair(vertex_number, vector<int>()));

		//add all the neighbours of the vertex to it's list.
		int nbrs;
		while(in >> nbrs){
			g[vertex_number].push_back(nbrs);
		}
	}

	//cin is unreadable after this loop. So, clear all its flags to allow further use.
	input.clear();
	return input;
}

ostream& print_graph(Graph &g, ostream &output){
	output << "The graph : " << std::endl;

	for(auto it = g.begin(); it != g.end(); ++it){
		output << it->first << " ";
		for(auto i: it->second)
			output << i << " ";
		output << std::endl;
	}

	return output;
}

void contract(Graph &g, int u, int v){
	//This method assumes that a edge exists between u and v.
	auto &u_nbrs = g[u];
	auto &v_nbrs = g[v];

	//remove one edge between u and v
	u_nbrs.erase(find(u_nbrs.begin(), u_nbrs.end(), v));
	v_nbrs.erase(find(v_nbrs.begin(), v_nbrs.end(), u));

	//append all the neighbors of v to u.
	u_nbrs.insert(u_nbrs.end(), v_nbrs.begin(), v_nbrs.end());

	//remove vertex v from the graph
	g.erase(v);

	//replace all occurences of v from the graph with u.
	for(auto it = g.begin(); it != g.end(); ++it){
		auto &cur_nbrs = it->second;
		// auto lt = find(cur_nbrs.begin(), cur_nbrs.end(), v);
		// while(lt != cur_nbrs.end()){
		// 	*lt = u;
		// 	lt = find(cur_nbrs.begin(), cur_nbrs.end(), v);
		// }
		for(auto iter = cur_nbrs.begin(); iter != cur_nbrs.end(); ++iter){
			if(*iter == v)
				*iter = u;
		} 
	}

	//remove self loops associated with u(if any).
	//Maybe there is a better way to do this.
	// auto it = find(u_nbrs.begin(), u_nbrs.end(), u);
	// while(it != u_nbrs.end()){
	// 	u_nbrs.erase(it);
	// 	it = find(u_nbrs.begin(), u_nbrs.end(), u);
	// }
	auto it = u_nbrs.begin();
	it = find(it, u_nbrs.end(), u);
	while(it != u_nbrs.end()){
		it = u_nbrs.erase(it);
		it = find(it, u_nbrs.end(), u);
	}
}

int cut(Graph &g){
	int init_sz = g.size();
	while(g.size() > 2){
		int u, v;
		int sz = g.size();
		u = rand() % init_sz + 1;
		v = rand() % init_sz + 1;

		if(edge_exists(g, u, v) == 1){
			contract(g, u, v);
		}
	}

	return g.begin()->second.size();
}

int karger_min_cut(Graph &g){
	srand(static_cast<unsigned>(time(0)));
	int min_so_far = g.size();
	int init_sz = g.size();
	for(int i = 0; i < init_sz*init_sz*static_cast<int>(log(init_sz)); ++i){
		Graph copy;
		copy_graph(g, copy);
		int this_cut = cut(copy);
		min_so_far = std::min(min_so_far, this_cut);
	}

	return min_so_far;
}

void copy_graph(Graph &src, Graph &dest){
	for(auto it = src.begin(); it != src.end(); ++it){
		dest.insert(make_pair(it->first, vector<int>(it->second.begin(), it->second.end())));
	}
}