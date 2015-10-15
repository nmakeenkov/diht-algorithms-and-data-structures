#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

template<typename W>
int FlowEdge<W>::getNum() const {
	return num;
}

template<typename W>
int FlowEdge<W>::getVert() const {
	return vert;
}

template<typename W>
W FlowEdge<W>::getCap() const {
	return cap;
}

template<typename W>
W FlowEdge<W>::getFlow() const {
	return flow;
}

template<typename W>
FlowEdge<W> *FlowEdge<W>::getRev() const {
	return rev;
}

template<typename W>
void FlowEdge<W>::setRev(FlowEdge<W> *_rev) {
	rev = _rev;
}

template<typename W>
void FlowEdge<W>::incFlow(W d) {
	flow += d;
	rev->flow -= d;
}

#endif
