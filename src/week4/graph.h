#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "vertex.h"
#include <map>
#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdio>

class graph{
	friend std::istream& operator>>(std::istream &in, graph &g);
	friend std::ostream& operator<<(std::ostream &out, graph &g);
	friend void read_using_scanf(FILE *, graph &g);
public:
	//type definitions.
	typedef std::map<int, vertex> _graph_type;
	typedef _graph_type::size_type size_type;
	typedef _graph_type::iterator iterator;
	typedef _graph_type::reverse_iterator reverse_iterator;

public:
	//constructors
	graph(size_type size): nodes(std::map<int, vertex>()) {
		for(size_type i = 1; i <= size; ++i){
			nodes.insert(std::make_pair(i, vertex()));
		}
	}

	//size operations.
	bool empty() { return nodes.size() == 0; }
	size_type size() { return nodes.size(); }
	
	//vertex and edge operations.
	bool has_vertex(int i);
	bool has_edge(int v, int w);
	void add_edge(int v, int w);

	//iterators
	iterator begin() { return nodes.begin(); }
	iterator end() { return nodes.end(); }
	reverse_iterator rbegin() { return nodes.rbegin(); }
	reverse_iterator rend() { return nodes.rend(); }

	//operators
	vertex& operator[](int i) { return nodes[i]; }
private:
	_graph_type nodes;
};

std::istream& operator>>(std::istream &in, graph &g);
std::ostream& operator<<(std::ostream &out, graph &g);

std::ostream& operator<<(std::ostream &out, graph &g){
	out << "The graph: \n";
	for(auto iter = g.begin(); iter != g.end(); ++iter){
		out << iter->first << " ";
		for(auto i: iter->second){
			out << i << " ";
		}
		out << std::endl;
	}

	return out;
}

bool graph::has_vertex(int v) {
	for(auto iter = begin(); iter != end(); ++iter){
		if(iter->first == v)
			return true;
	}
	return false;
}

bool graph::has_edge(int v, int w) {
	if(has_vertex(v) && has_vertex(w)){
		return nodes[v].has_nbr(w);
	}
}

void graph::add_edge(int v, int w){
	nodes[v].add_nbr(w);
}

std::istream& operator>>(std::istream &in, graph &g){
	int v, w, i = 0;
	while(in >> v >> w){
		g.add_edge(v, w);
	}

	in.clear();
	return in;
}

void read_using_scanf(FILE *in, graph &g){
	int v, w, i = 0;
	while(fscanf(in, "%d %d", &v, &w) == 2){
		++i;
		if(i % 1000 == 0)
			std::cerr << i << std::endl;
		g.add_edge(v, w);
	}
}

#endif //_GRAPH_H_