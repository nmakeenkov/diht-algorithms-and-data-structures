#ifndef _BFSGRAPH_CPP_
#define _BFSGRAPH_CPP_

#include"BFSGraph.h"
#include<queue>

template <typename Graph, typename EdgeExists>
void BFSGraph<Graph, EdgeExists>::bfs(Graph const &g, int start, 
		std::vector<int> &dist) {
	dist.resize(g.getV());
	for (int i = 0; i < (int)dist.size(); ++i) {
		dist[i] = -1;
	}
	std::queue<int> q;
	q.push(start);
	dist[start] = 0;
	EdgeExists check;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < (int)g.e[v].size(); ++i) {
			int to = g.e[v][i]->getVert();
			if (dist[to] == -1 && check(g.e[v][i])) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
}

#endif
