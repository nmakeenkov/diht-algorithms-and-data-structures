#ifndef _NET_CPP_
#define _NET_CPP_

#include"Net.h"
#include<queue>

template<typename CapacityType>
size_t Net<CapacityType>::getV() const {
	return e.size();
}

template<typename CapacityType>
std::istream &operator>>(std::istream &in, Net<CapacityType> &g) {
	int n, m;
	in >> n >> m;
	g.e.resize(n);
	for (int i = 0; i < m; ++i) {
		FlowEdge<CapacityType> *dir = new FlowEdge<CapacityType>(i);
		in >> (*dir);
		FlowEdge<CapacityType> *rev = new FlowEdge<CapacityType>(dir);
		dir->setReversedEdge(rev);
		g.e[dir->getStartVertex()].push_back(dir);
		g.e[rev->getStartVertex()].push_back(rev);
	}
	return in;
}

template<typename CapacityType>
std::ostream &operator<<(std::ostream &out, Net<CapacityType> &g) {
	out << g.flow << "\n";
	int maxNum = 0;
	for (int i = 0; i < (int)g.e.size(); ++i) {
		maxNum += g.e[i].size();
	}
	maxNum /= 2; // reversed are fakes
	std::vector<CapacityType> ans(maxNum);
	for (int i = 0; i < (int)g.e.size(); ++i) {
		for (int j = 0; j < (int)g.e[i].size(); ++j) {
			if (g.e[i][j]->getID() != -1)  { // not a fake
				ans[g.e[i][j]->getID()] = g.e[i][j]->getFlow();
			}
		}
	}
	for (int i = 0; i < (int)ans.size(); ++i) {
		out << ans[i] << "\n";
	}
	return out;
}

#endif
