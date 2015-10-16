#ifndef _EDGE_H_
#define _EDGE_H_

class Edge {
private:
	int num, vert;
public:
	Edge() : num(-1), vert(-1) {}
	Edge(int _num, int _vert) : num(_num), vert(_vert) {}

	int getNum() const;
	int getVert() const;
};

#include"Edge.cpp"

#endif
