#ifndef _NET_H_
#define _NET_H_

#include<vector>
#include<queue>
#include<istream>
#include<ostream>
#include"FlowEdge.h"

template<typename W>
class Net;

template<typename W>
std::istream &operator>>(std::istream &in, Net<W> &g);

template<typename W>
std::ostream &operator<<(std::ostream &out, Net<W> &g);

template<typename W>
class Net {
private:
	W flow;
	std::vector<std::vector<FlowEdge<W> *> > e;
public:
	Net() {}
	
	size_t getV() const;
	void bfs(int s, std::vector<int> &dist) const;
	W dfs(int v, int t, W flow, std::vector<int> const &lev,
			std::vector<int> &ind);
	void runDinic(int s, int t);
	void relable(int v, std::vector<int> &h, std::vector<int> &hCnt);
	void push(int v, FlowEdge<W> *u, std::vector<W> &exc,
			std::queue<int> &q);
	void runPreflowPush(int s, int t);

	friend std::istream &operator>> <>(std::istream &in, Net<W> &g);
	friend std::ostream &operator<< <>(std::ostream &out, Net<W> &g);
};

#include "Net.cpp"

#endif
