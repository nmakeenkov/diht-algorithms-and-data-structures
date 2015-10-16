#ifndef _BFSGRAPH_H_
#define _BFSGRAPH_H_

#include<vector>
#include"Graph.h"

template<typename Graph, typename EdgeExists>
class BFSGraph {
public:
	static void bfs(Graph const &g, int s, std::vector<int> &dist);
};

#include"BFSGraph.cpp"

#endif
