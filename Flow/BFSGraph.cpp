#ifndef _BFSGRAPH_CPP_
#define _BFSGRAPH_CPP_

#include"BFSGraph.h"
#include<queue>

template<class Graph, class IsValidEdgeFunction>
void BFSGraph::bfs(Graph const &graph, int start, std::vector<int> &distanceToVertex,
				   IsValidEdgeFunction const &isValidEdge) {
	distanceToVertex.resize(graph.getV());
	for (int i = 0; i < (int)distanceToVertex.size(); ++i) {
		distanceToVertex[i] = -1;
	}
	std::queue<int> vertexQueue;
	vertexQueue.push(start);
	distanceToVertex[start] = 0;
	while (!vertexQueue.empty()) {
		int v = vertexQueue.front();
		vertexQueue.pop();
		for (int i = 0; i < (int)graph.e[v].size(); ++i) {
			int to = graph.e[v][i]->getFinishVertex();
			if (distanceToVertex[to] == -1 && isValidEdge(graph.e[v][i])) {
				distanceToVertex[to] = distanceToVertex[v] + 1;
				vertexQueue.push(to);
			}
		}
	}
}

#endif
