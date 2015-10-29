#ifndef _EDGE_H_
#define _EDGE_H_

class Edge {
private:
	int id, startVertex, finishVertex;
public:
	Edge() : id(-1), startVertex(-1), finishVertex(-1) {}
	Edge(int _id, int _startVertex, int _finishVertex) : id(_id),
														 startVertex(_startVertex),
														 finishVertex(_finishVertex) {}

	int getID() const;
	int getStartVertex() const;
	int getFinishVertex() const;
};

#include"Edge.cpp"

#endif
