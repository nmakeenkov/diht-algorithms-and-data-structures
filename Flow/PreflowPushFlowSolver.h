#ifndef _PREFLOWPUSHFLOWSOLVER_H_
#define _PREFLOWPUSHFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"
#include"FlowSolver.h"

class PreflowPushFlowSolver : public FlowSolver {
private:
	std::vector<int> height, heightCount;
	std::vector<long long> excess;
	std::queue<int> vertexQueue;
	std::vector<int> indexOfCurrentEdge;

	void relable(int v);
	void push(FlowEdge<long long> *edge);
	void discharge(int v);
public:
	PreflowPushFlowSolver(Net<long long> &_graph) : FlowSolver(_graph) {}

    virtual void solve(int source, int sink);
};

#include"PreflowPushFlowSolver.cpp"

#endif
