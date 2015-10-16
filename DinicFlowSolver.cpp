#ifndef _DINICFLOWSOLVER_CPP_
#define _DINICFLOWSOLVER_CPP_

#include"DinicFlowSolver.h"
#include"BFSGraph.h"
#include<queue>

template<typename CapacityType>
class DinicFlowSolver<CapacityType>::EdEx {
public:
	bool operator()(FlowEdge<CapacityType> * const &e) {
		return (e->getCap() - e->getFlow());
	}
};

template<typename CapacityType>
CapacityType DinicFlowSolver<CapacityType>::dfs(int v, int t, 
		CapacityType flow, std::vector<int> const &lev, 
		std::vector<int> &ind) {
	if (v == t) {
		return flow;
	}
	CapacityType ans = CapacityType();
	for (;ind[v] < (int)Net<CapacityType>::e[v].size(); ++ind[v]) {
		FlowEdge<CapacityType> *ed = (FlowEdge<CapacityType> *)
				Net<CapacityType>::e[v][ind[v]];
		int to = ed->getVert();
		if (lev[to] != lev[v] + 1) {
			continue;
		}
		CapacityType cur = dfs(to, t, std::min(flow, ed->getCap() 
				- ed->getFlow()), lev, ind);
		ed->incFlow(cur);
		ans += cur;
		flow -= cur;
		if (flow == CapacityType()) { // do not ind++
			return ans;
		}
	}
	return ans;
}

template<typename CapacityType>
void DinicFlowSolver<CapacityType>::runDinic(int s, int t) {
	Net<CapacityType>::flow = CapacityType();
	while (true) {
		std::vector<int> dist;
		BFSGraph<DinicFlowSolver, EdEx>::bfs(*this, s, dist);
		if (dist[t] == -1) {
			break;
		}
		CapacityType w;
		for (int i = 0; i < (int)Net<CapacityType>::e[s].size(); ++i) {
			FlowEdge<CapacityType> *ed = (FlowEdge<CapacityType> *)
					Net<CapacityType>::e[s][i];
			w += ed->getCap() - ed->getFlow();
		}
		std::vector<int> ind(Net<CapacityType>::e.size(), 0);
		CapacityType pushed;
		do {
			pushed = dfs(s, t, w, dist, ind);
			Net<CapacityType>::flow += pushed;
		} while (pushed > CapacityType());
	}
}

#endif
