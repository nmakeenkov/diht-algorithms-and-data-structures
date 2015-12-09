#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

template<typename CapacityType>
std::istream &operator>>(std::istream &in, FlowEdge<CapacityType> &flowEdge) {
	int from, to, capacity;
	in >> from >> to >> capacity;
	from--;
	to--;
	flowEdge.startVertex = from;
	flowEdge.finishVertex = to;
	flowEdge.capacity = capacity;
	return in;
}


template<typename CapacityType>
CapacityType FlowEdge<CapacityType>::getCapacity() const {
	return capacity;
}

template<typename CapacityType>
CapacityType FlowEdge<CapacityType>::getFlow() const {
	return flow;
}

template<typename CapacityType>
FlowEdge<CapacityType> *FlowEdge<CapacityType>::getReversedEdge() const {
	return reversedEdge;
}

template<typename CapacityType>
void FlowEdge<CapacityType>::setReversedEdge(FlowEdge<CapacityType> *_reversedEdge) {
	reversedEdge = _reversedEdge;
}

template<typename CapacityType>
void FlowEdge<CapacityType>::incFlow(CapacityType d) {
	flow += d;
	reversedEdge->flow -= d;
}

#endif
