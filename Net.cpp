#ifndef _NET_CPP_
#define _NET_CPP_

#include"Net.h"
#include<queue>

template<typename CapacityType>
size_t Net<CapacityType>::getV() const {
	return e.size();
}

template<typename W>
std::istream &operator>>(std::istream &in, Net<W> &g) {
	int n, m;
	in >> n >> m;
	g.e.resize(n);
	for (int i = 0; i < m; ++i) {
		int f, t, c;
		in >> f >> t >> c;
		f--;
		t--;
		FlowEdge<W> *dir = new FlowEdge<W>(i, t, c);
		FlowEdge<W> *rev = new FlowEdge<W>(f, dir);
		dir->setRev(rev);
		g.e[f].push_back(dir);
		g.e[t].push_back(rev);
	}
	return in;
}

template<typename W>
std::ostream &operator<<(std::ostream &out, Net<W> &g) {
	out << g.flow << "\n";
	int maxNum = 0;
	for (int i = 0; i < (int)g.e.size(); ++i) {
		maxNum += g.e[i].size();
	}
	maxNum /= 2; // reversed are fakes
	std::vector<W> ans(maxNum);
	for (int i = 0; i < (int)g.e.size(); ++i) {
		for (int j = 0; j < (int)g.e[i].size(); ++j) {
			if (g.e[i][j]->getNum() != -1)  { // not a fake
				ans[g.e[i][j]->getNum()] = g.e[i][j]->getFlow();
			}
		}
	}
	for (int i = 0; i < (int)ans.size(); ++i) {
		out << ans[i] << "\n";
	}
	return out;
}

#endif
