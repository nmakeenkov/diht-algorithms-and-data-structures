#ifndef _BFSGRAPH_H_
#define _BFSGRAPH_H_

#include<vector>
#include"Graph.h"

namespace BFSGraph {
	template<class Graph, class IsValidEdgeFunction>
	void bfs(Graph const &graph, int start, std::vector<int> &distanceToVertex,
			 IsValidEdgeFunction const &isValidEdge);
};

#include"BFSGraph.cpp"

#endif
