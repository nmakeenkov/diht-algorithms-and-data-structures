#ifndef _PREFLOWPUSHFLOWSOLVER_H_
#define _PREFLOWPUSHFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"

template<typename CapacityType>
class PreflowPushFlowSolver : public Net<CapacityType> {
private:
	std::vector<int> h, hCnt;
	std::vector<CapacityType> exc;
	std::queue<int> q;

	void relable(int v);
	void push(int v, FlowEdge<CapacityType> *u);
public:
	PreflowPushFlowSolver() : Net<CapacityType>() {}
	
	void runPreflowPush(int s, int t);
};

#include"PreflowPushFlowSolver.cpp"

#endif
