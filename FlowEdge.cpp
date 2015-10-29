#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

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
