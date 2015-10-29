#ifndef _BFSGRAPH_H_
#define _BFSGRAPH_H_

#include<vector>
#include"Graph.h"

template<typename Graph, typename IsValidEdgeFunction>
class BFSGraph {
public:
	static void bfs(Graph const &graph, int start, std::vector<int> &distanceToVertex);
};

#include"BFSGraph.cpp"

#endif
