#ifndef _DINICFLOWSOLVER_H_
#define _DINICFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"
#include"BFSGraph.h"

template<typename CapacityType>
class DinicFlowSolver : public Net<CapacityType> {
private:
	class EdgeIsNotFull;
	CapacityType dfs(int vertex, int sink, CapacityType flowToPush,
					 std::vector<int> const &levelOfVertex,
					 std::vector<int> &indexOfEdge);
public:
	DinicFlowSolver() : Net<CapacityType>() {}

	void runDinic(int source, int sink);

	friend class BFSGraph<DinicFlowSolver, EdgeIsNotFull>;
};

#include"DinicFlowSolver.cpp"

#endif
