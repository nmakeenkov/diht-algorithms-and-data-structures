#ifndef _DINICFLOWSOLVER_CPP_
#define _DINICFLOWSOLVER_CPP_

#include"DinicFlowSolver.h"
#include"BFSGraph.h"
#include<queue>

class DinicFlowSolver::EdgeIsNotFull {
public:
	bool operator()(FlowEdge<long long> *edge) const {
		return (edge->getCapacity() - edge->getFlow());
	}
};

long long DinicFlowSolver::dfs(Net<long long> &graph, int vertex, int sink, long long flowToPush,
                                                std::vector<int> const &levelOfVertex,
                                                std::vector<int> &indexOfEdge) {
	if (vertex == sink) {
		return flowToPush;
	}
	long long ans = 0LL;
	for (;indexOfEdge[vertex] < (int)graph.e[vertex].size();
          ++indexOfEdge[vertex]) {
		FlowEdge<long long> *edge = graph.e[vertex][indexOfEdge[vertex]];
		int to = edge->getFinishVertex();
		if (levelOfVertex[to] != levelOfVertex[vertex] + 1) {
			continue;
		}
		long long flowAdded = dfs(graph, to, sink, std::min(flowToPush, edge->getCapacity() - edge->getFlow()),
                                  levelOfVertex, indexOfEdge);
		edge->incFlow(flowAdded);
		ans += flowAdded;
		flowToPush -= flowAdded;
		if (flowToPush == 0LL) { // everything pushed - do not increment the index
			return ans;
		}
	}
	return ans;
}

void DinicFlowSolver::runDinic(Net<long long> &graph, int source, int sink) {
    while (true) {
        std::vector<int> distanceToVertex;
        BFSGraph::bfs(graph, source, distanceToVertex, EdgeIsNotFull());
        if (distanceToVertex[sink] == -1) {
            break;
        }
        long long MaxFlowPossible = 0LL;
        for (int i = 0; i < (int)graph.e[source].size(); ++i) {
            FlowEdge<long long> *edge = (FlowEdge<long long> *)
                    graph.e[source][i];
            MaxFlowPossible += edge->getCapacity() - edge->getFlow();
        }
        std::vector<int> indexOfEdge(graph.e.size(), 0);
        long long pushed = dfs(graph, source, sink, MaxFlowPossible, distanceToVertex, indexOfEdge);
        graph.flow += pushed;
    }
}

void DinicFlowSolver::solve(int source, int sink) {
    long long maxCapacity = 0LL;
    for (int i = 0; i < (int)graph.e.size(); ++i) {
        for (int j = 0; j < (int)graph.e[i].size(); ++j) {
            maxCapacity = std::max(maxCapacity, graph.e[i][j]->getCapacity());
        }
    }
    for (long long minCapacity = maxCapacity; minCapacity > 0; minCapacity /= 2LL) {
        Net<long long> _graph(graph);
        std::vector<std::vector<FlowEdge<long long> *> > realEdges(graph.e.size());
        for (int i = 0; i < (int)_graph.e.size(); ++i) {
            _graph.e[i].clear();
        }
        _graph.flow = 0LL;
        for (int i = 0; i < (int)graph.e.size(); ++i) {
            for (int j = 0; j < (int)graph.e[i].size(); ++j) {
                if (graph.e[i][j]->getID() != -1 // direct edge
                    && (graph.e[i][j]->getCapacity() - graph.e[i][j]->getFlow()) >= minCapacity) {
                    FlowEdge<long long> *directEdge = new FlowEdge<long long>
                            (graph.e[i][j]->getID(),
                             graph.e[i][j]->getStartVertex(),
                             graph.e[i][j]->getFinishVertex(),
                             (graph.e[i][j]->getCapacity() - graph.e[i][j]->getFlow()) / minCapacity);
                    FlowEdge<long long> *reversedEdge = new FlowEdge<long long>(directEdge);
                    directEdge->setReversedEdge(reversedEdge);
                    _graph.e[directEdge->getStartVertex()].push_back(directEdge);
                    _graph.e[reversedEdge->getStartVertex()].push_back(reversedEdge);
                    realEdges[directEdge->getStartVertex()].push_back(graph.e[i][j]);
                    realEdges[reversedEdge->getStartVertex()].push_back(NULL);
                }
            }
        }
        runDinic(_graph, source, sink);
        for (int i = 0; i < (int)_graph.e.size(); ++i) {
            for (int j = 0; j < (int)_graph.e[i].size(); ++j) {
                if (_graph.e[i][j]->getID() != -1) { // direct edge
                    realEdges[i][j]->incFlow(_graph.e[i][j]->getFlow() * minCapacity);
                }
            }
        }
        graph.flow += _graph.flow * minCapacity;
    }
    runDinic(graph, source, sink);
}

#endif
