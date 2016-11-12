#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <list>
#include <initializer_list>
#include <algorithm>

class vertex{
public:
	//Type definitions of the iterators.
	typedef std::list<int>::iterator iterator;

	//constructor - default.
	vertex(): nbrs(std::list<int>()), visited(false), source_of_DFS(0), finishing_time_DFS(0) { }
	
	//add/remove the neighbors.
	void add_nbr(int i);
	iterator remove_nbr(int i);
	bool has_nbr(int v);

	//Checks the current stats of the vertex.
	//THESE FUnCTIONS DO NOT CHECK FOR VALIDITY AND WORK ON const vertex.
	bool is_visited() { return visited; }
	void set_visited(bool b) { visited = b; }
	int get_src() { return source_of_DFS; }
	void set_src(int i) { source_of_DFS = i; }
	int get_fin_time() { return finishing_time_DFS; }
	void set_fin_time(int f) { finishing_time_DFS = f; }

	//Iterators for the vertex.
	iterator begin() { return nbrs.begin(); }
	iterator end() { return nbrs.end(); }
private:
	std::list<int> nbrs;
	mutable bool visited = false;
	mutable int source_of_DFS = 0;
	mutable int finishing_time_DFS = 0;
};

void vertex::add_nbr(int i){
	nbrs.push_back(i);
}

vertex::iterator vertex::remove_nbr(int i){
	auto pos = find(begin(), end(), i);
	if(pos != end())
		return nbrs.erase(pos);
	else
		return pos;
}

bool vertex::has_nbr(int v) {
	return (find(begin(), end(), v) != end());
}

#endif //_VERTEX_H_