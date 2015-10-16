#ifndef _NET_H_
#define _NET_H_

#include<vector>
#include<queue>
#include<istream>
#include<ostream>
#include"FlowEdge.h"
#include"Graph.h"

template<typename CapacityType>
class Net;

template<typename CapacityType>
std::istream &operator>>(std::istream &in, Net<CapacityType> &g);

template<typename CapacityType>
std::ostream &operator<<(std::ostream &out, Net<CapacityType> &g);

template<typename CapacityType>
class Net : public Graph {
protected:
	CapacityType flow;
	std::vector<std::vector<FlowEdge<CapacityType> *> > e;
public:
	Net() : Graph() {}
	
	size_t getV() const;
	void relable(int v, std::vector<int> &h, std::vector<int> &hCnt);
	void push(int v, FlowEdge<CapacityType> *u, 
			std::vector<CapacityType> &exc, std::queue<int> &q);
	void runPreflowPush(int s, int t);

	friend std::istream &operator>> <>(std::istream &in, 
			Net<CapacityType> &g);
	friend std::ostream &operator<< <>(std::ostream &out, 
			Net<CapacityType> &g);
};

#include"Net.cpp"

#endif
