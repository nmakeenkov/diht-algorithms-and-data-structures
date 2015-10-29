#ifndef _PREFLOWPUSHFLOWSOLVER_H_
#define _PREFLOWPUSHFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"

template<typename CapacityType>
class PreflowPushFlowSolver : public Net<CapacityType> {
private:
	std::vector<int> height, heightCount;
	std::vector<CapacityType> excess;
	std::queue<int> vertexQueue;
	std::vector<int> indexOfCurrentEdge;

	void relable(int v);
	void push(FlowEdge<CapacityType> *edge);
	void discharge(int v);
public:
	PreflowPushFlowSolver() : Net<CapacityType>() {}
	
	void runPreflowPush(int source, int sink);
};

#include"PreflowPushFlowSolver.cpp"

#endif
