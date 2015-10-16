#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include<vector>
#include<iostream>
#include"Edge.h"

template<typename W>
class FlowEdge : public Edge {
private:
	W cap, flow;
	FlowEdge *rev;
public:
	FlowEdge() : Edge(), cap(W()), flow(W()), rev(NULL) {}
	FlowEdge(int _num, int _vert, W _cap, W _flow = 0) :
			Edge(_num, _vert), cap(_cap), flow(_flow), rev(NULL) {}
	FlowEdge(int _vert, FlowEdge *_rev) : 
			Edge(-1, _vert), cap(W()), flow(W()), rev(_rev) {}
	
	FlowEdge<W> *getRev() const;
	W getCap() const;
	W getFlow() const;
	void setRev(FlowEdge<W> *_rev);
	void incFlow(W d);
};

#include"FlowEdge.cpp"

#endif
