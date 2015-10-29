#ifndef _DINICFLOWSOLVER_CPP_
#define _DINICFLOWSOLVER_CPP_

#include"DinicFlowSolver.h"
#include"BFSGraph.h"
#include<queue>

template<typename CapacityType>
class DinicFlowSolver<CapacityType>::EdgeIsNotFull {
public:
	bool operator()(FlowEdge<CapacityType> * const &edge) {
		return (edge->getCapacity() - edge->getFlow());
	}
};

template<typename CapacityType>
CapacityType DinicFlowSolver<CapacityType>::dfs(int vertex, int sink, CapacityType flowToPush,
                                                std::vector<int> const &levelOfVertex,
                                                std::vector<int> &indexOfEdge) {
	if (vertex == sink) {
		return flowToPush;
	}
	CapacityType ans = CapacityType();
	for (;indexOfEdge[vertex] < (int)Net<CapacityType>::e[vertex].size();
          ++indexOfEdge[vertex]) {
		FlowEdge<CapacityType> *edge = Net<CapacityType>::e[vertex][indexOfEdge[vertex]];
		int to = edge->getFinishVertex();
		if (levelOfVertex[to] != levelOfVertex[vertex] + 1) {
			continue;
		}
		CapacityType flowAdded = dfs(to, sink, std::min(flowToPush, edge->getCapacity()
																	- edge->getFlow()),
									 levelOfVertex, indexOfEdge);
		edge->incFlow(flowAdded);
		ans += flowAdded;
		flowToPush -= flowAdded;
		if (flowToPush == CapacityType()) { // everything pushed - do not increment the index
			return ans;
		}
	}
	return ans;
}

template<typename CapacityType>
void DinicFlowSolver<CapacityType>::runDinic(int source, int sink) {
	Net<CapacityType>::flow = CapacityType();
	while (true) {
		std::vector<int> distaneToVertex;
		BFSGraph<DinicFlowSolver, EdgeIsNotFull>::bfs(*this, source, distaneToVertex);
		if (distaneToVertex[sink] == -1) {
			break;
		}
		CapacityType MaxFlowPossible = CapacityType();
		for (int i = 0; i < (int)Net<CapacityType>::e[source].size(); ++i) {
			FlowEdge<CapacityType> *edge = (FlowEdge<CapacityType> *)
                    Net<CapacityType>::e[source][i];
			MaxFlowPossible += edge->getCapacity() - edge->getFlow();
		}
		std::vector<int> indexOfEdge(Net<CapacityType>::e.size(), 0);
		CapacityType pushed = dfs(source, sink, MaxFlowPossible, distaneToVertex, indexOfEdge);
        Net<CapacityType>::flow += pushed;
	}
}

#endif
