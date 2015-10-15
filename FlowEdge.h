#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include<vector>
#include<iostream>

template<typename W>
class FlowEdge {
private:
	int num, vert;
	W cap, flow;
	FlowEdge *rev;
public:
	FlowEdge() : num(-1), vert(-1), cap(W()), flow(W()), rev(NULL) {}
	FlowEdge(int _num, int _vert, W _cap, W _flow = 0) :
			num(_num), vert(_vert), cap(_cap), flow(_flow), rev(NULL) {}
	FlowEdge(int _vert, FlowEdge *_rev) : 
			num(-1), vert(_vert), cap(W()), flow(W()), rev(_rev) {}
	
	int getNum() const;
	int getVert() const;
	FlowEdge<W> *getRev() const;
	W getCap() const;
	W getFlow() const;
	void setRev(FlowEdge<W> *_rev);
	void incFlow(W d);
};

#include"FlowEdge.cpp"

#endif
