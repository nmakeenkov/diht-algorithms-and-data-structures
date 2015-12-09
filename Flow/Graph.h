#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<vector>
#include"Edge.h"

class Graph {
protected:
	std::vector<std::vector<Edge*> > e;
public:
	Graph() {}
	int getV() const;
};

#endif
