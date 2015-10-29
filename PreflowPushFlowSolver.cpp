#ifndef _PREFLOWPUSHFLOWSOLVER_CPP_
#define _PREFLOWPUSHFLOWSOLVER_CPP_

#include"PreflowPushFlowSolver.h"
#include<queue>

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::relable(int v) {
	int newHeight = Net<CapacityType>::getV() * 2;
	for (int i = 0; i < (int)Net<CapacityType>::e[v].size(); ++i) {
		FlowEdge<CapacityType> *edge = Net<CapacityType>::e[v][i];
		if (edge->getCapacity() > edge->getFlow()) {
			newHeight = std::min(height[edge->getFinishVertex()] + 1, newHeight);
		}
	}
	heightCount[height[v]]--;
	int gapC = Net<CapacityType>::getV();
	if (heightCount[height[v]] == 0)
		gapC = height[v];
	height[v] = newHeight;
	heightCount[height[v]]++;
	if (gapC < Net<CapacityType>::getV()) {
		for (int i = 0; i < (int)height.size(); ++i) {
			if (height[i] > gapC && height[i] < Net<CapacityType>::getV()) {
				heightCount[height[i]]--;
				height[i] = Net<CapacityType>::getV();
				heightCount[height[i]]++;
			}
		}
	}
}

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::push(FlowEdge<CapacityType> *edge) {
	CapacityType flow = std::min(excess[edge->getStartVertex()], edge->getCapacity() - edge->getFlow());
	edge->incFlow(flow);
	excess[edge->getStartVertex()] -= flow;
	int u = edge->getFinishVertex();
	excess[u] += flow;
	if (excess[u] > CapacityType() && excess[u] <= flow) { // was 0 and now >= 0
		vertexQueue.push(u);
	}
}


template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::discharge(int v) {
	while (excess[v] > 0) {
		if (indexOfCurrentEdge[v] == (int)Net<CapacityType>::e[v].size()) {
			relable(v);
			indexOfCurrentEdge[v] = 0;
		} else {
			FlowEdge<CapacityType> *ed = Net<CapacityType>::e[v][indexOfCurrentEdge[v]];
			if (ed->getCapacity() - ed->getFlow() > CapacityType()
				&& height[ed->getFinishVertex()] == height[v] - 1) {
				push(ed);
			} else {
				indexOfCurrentEdge[v]++;
			}
		}
	}
}

template<typename CapacityType>
void PreflowPushFlowSolver<CapacityType>::runPreflowPush(int source, int sink) {
	height = std::vector<int>(Net<CapacityType>::getV(), 0);
	heightCount = std::vector<int>(Net<CapacityType>::getV() * 2, 0);
	heightCount[Net<CapacityType>::getV()] = 1;
	heightCount[0] = Net<CapacityType>::getV() - 1;
	height[source] = Net<CapacityType>::getV();
	excess = std::vector<CapacityType>(Net<CapacityType>::getV(),
			CapacityType());
	for (int i = 0; i < (int)Net<CapacityType>::e[source].size(); ++i) {
		FlowEdge<CapacityType> *edge = Net<CapacityType>::e[source][i];
		edge->incFlow(edge->getCapacity());
		excess[edge->getFinishVertex()] += edge->getCapacity();
		excess[source] -= edge->getCapacity();
	}
	for (int i = 0; i < (int)Net<CapacityType>::e[sink].size(); ++i) {
		excess[sink] -= Net<CapacityType>::e[sink][i]->getReversedEdge()->getCapacity();
	}
	for (int i = 0; i < (int)Net<CapacityType>::getV(); ++i) {
		if (excess[i] > 0) {
			vertexQueue.push(i);
		}
	}
	indexOfCurrentEdge = std::vector<int>(Net<CapacityType>::getV(), 0);
	while (!vertexQueue.empty()) {
		int v = vertexQueue.front();
		vertexQueue.pop();
		discharge(v);
	}
	Net<CapacityType>::flow = -excess[source];
}

#endif
