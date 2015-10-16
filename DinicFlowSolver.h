#ifndef _DINICFLOWSOLVER_H_
#define _DINICFLOWSOLVER_H_

#include<vector>
#include<queue>
#include"Net.h"
#include"BFSGraph.h"

template<typename CapacityType>
class DinicFlowSolver : public Net<CapacityType> {
private:
	class EdEx;
public:
	DinicFlowSolver() : Net<CapacityType>() {}
	
	CapacityType dfs(int v, int t, CapacityType flow, 
			std::vector<int> const &lev,
			std::vector<int> &ind);
	void runDinic(int s, int t);

	/*
	friend void BFSGraph<DinicFlowSolver, EdEx>::bfs(DinicFlowSolver const &g, 
			int start, std::vector<int> &dist);
	*/
	friend class BFSGraph<DinicFlowSolver, EdEx>;
};

#include"DinicFlowSolver.cpp"

#endif
