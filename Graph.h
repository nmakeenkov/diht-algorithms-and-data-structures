#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<vector>
#include<iostream>
#include"Edge.h"

class Graph {
private:
	std::vector<std::vector<Edge*> > e;
public:
	Graph() {}
};

#include "Graph.cpp"

#endif
