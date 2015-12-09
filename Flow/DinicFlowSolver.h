#ifndef _DINICFLOWSOLVER_H_
#define _DINICFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"
#include"BFSGraph.h"
#include"FlowSolver.h"

class DinicFlowSolver : public FlowSolver {
private:
	class EdgeIsNotFull;
	long long dfs(Net<long long> &graph, int vertex, int sink, long long flowToPush,
					 std::vector<int> const &levelOfVertex,
					 std::vector<int> &indexOfEdge);
    void runDinic(Net<long long> &graph, int source, int sink);
public:
	DinicFlowSolver(Net<long long> &_graph) : FlowSolver(_graph) {}
    virtual void solve(int source, int sink);
};

#include"DinicFlowSolver.cpp"

#endif
