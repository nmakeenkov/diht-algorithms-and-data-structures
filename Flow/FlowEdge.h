#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include<vector>
#include<iostream>
#include"Edge.h"

template<typename CapacityType>
class FlowEdge;

template<typename CapacityType>
std::istream &operator>>(std::istream &in, FlowEdge<CapacityType> &flowEdge);

template<typename CapacityType>
class FlowEdge : public Edge {
protected:
	CapacityType capacity, flow;
	FlowEdge *reversedEdge;
public:
	FlowEdge() : Edge(), capacity(CapacityType()), flow(CapacityType()),
				 reversedEdge(NULL) {}
	FlowEdge(int _id, int _startVertex = 0, int _finishVertex = 0,
			 CapacityType _capacity = CapacityType(), CapacityType _flow = CapacityType()) :
			Edge(_id, _startVertex, _finishVertex), capacity(_capacity), flow(_flow),
			reversedEdge(NULL) {}
	FlowEdge(FlowEdge *_reversedEdge) :
			Edge(-1, _reversedEdge->getFinishVertex(), _reversedEdge->getStartVertex()),
			capacity(CapacityType()), flow(CapacityType()), reversedEdge(_reversedEdge) {}
	
	FlowEdge<CapacityType> *getReversedEdge() const;
	CapacityType getCapacity() const;
	CapacityType getFlow() const;

	void setReversedEdge(FlowEdge<CapacityType> *_reversedEdge);
	void incFlow(CapacityType d);

	friend std::istream &operator>> <>(std::istream &in,
									   FlowEdge<CapacityType> &flowEdge);
};

#include"FlowEdge.cpp"

#endif
