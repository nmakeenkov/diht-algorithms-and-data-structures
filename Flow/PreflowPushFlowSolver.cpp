#ifndef _PREFLOWPUSHFLOWSOLVER_CPP_
#define _PREFLOWPUSHFLOWSOLVER_CPP_

#include"PreflowPushFlowSolver.h"
#include<queue>

void PreflowPushFlowSolver::relable(int v) {
	int newHeight = graph.getV() * 2;
	for (int i = 0; i < (int)graph.e[v].size(); ++i) {
		FlowEdge<long long> *edge = graph.e[v][i];
		if (edge->getCapacity() > edge->getFlow()) {
			newHeight = std::min(height[edge->getFinishVertex()] + 1, newHeight);
		}
	}
	heightCount[height[v]]--;
	int gapC = graph.getV();
	if (heightCount[height[v]] == 0)
		gapC = height[v];
	height[v] = newHeight;
	heightCount[height[v]]++;
	if (gapC < (int)graph.getV()) {
		for (int i = 0; i < (int)height.size(); ++i) {
			if (height[i] > gapC && height[i] < (int)graph.getV()) {
				heightCount[height[i]]--;
				height[i] = graph.getV();
				heightCount[height[i]]++;
			}
		}
	}
}

void PreflowPushFlowSolver::push(FlowEdge<long long> *edge) {
	long long flow = std::min(excess[edge->getStartVertex()], edge->getCapacity() - edge->getFlow());
	edge->incFlow(flow);
	excess[edge->getStartVertex()] -= flow;
	int u = edge->getFinishVertex();
	excess[u] += flow;
	if (excess[u] > 0LL && excess[u] <= flow) { // was 0 and now >= 0
		vertexQueue.push(u);
	}
}

void PreflowPushFlowSolver::discharge(int v) {
	while (excess[v] > 0) {
		if (indexOfCurrentEdge[v] == (int)graph.e[v].size()) {
			relable(v);
			indexOfCurrentEdge[v] = 0;
		} else {
			FlowEdge<long long> *edge = graph.e[v][indexOfCurrentEdge[v]];
			if (edge->getCapacity() - edge->getFlow() > 0LL
				&& height[edge->getFinishVertex()] == height[v] - 1) {
				push(edge);
			} else {
				indexOfCurrentEdge[v]++;
			}
		}
	}
}

void PreflowPushFlowSolver::solve(int source, int sink) {
	height = std::vector<int>(graph.getV(), 0);
	heightCount = std::vector<int>(graph.getV() * 2, 0);
	heightCount[graph.getV()] = 1;
	heightCount[0] = graph.getV() - 1;
	height[source] = graph.getV();
	excess = std::vector<long long>(graph.getV(), 0LL);
	for (int i = 0; i < (int)graph.e[source].size(); ++i) {
		FlowEdge<long long> *edge = graph.e[source][i];
		edge->incFlow(edge->getCapacity());
		excess[edge->getFinishVertex()] += edge->getCapacity();
		excess[source] -= edge->getCapacity();
	}
	for (int i = 0; i < (int)graph.e[sink].size(); ++i) {
		excess[sink] -= graph.e[sink][i]->getReversedEdge()->getCapacity();
	}
	for (int i = 0; i < (int)graph.getV(); ++i) {
		if (excess[i] > 0) {
			vertexQueue.push(i);
		}
	}
	indexOfCurrentEdge = std::vector<int>(graph.getV(), 0);
	while (!vertexQueue.empty()) {
		int v = vertexQueue.front();
		vertexQueue.pop();
		discharge(v);
	}
    graph.flow = -excess[source];
}

#endif
