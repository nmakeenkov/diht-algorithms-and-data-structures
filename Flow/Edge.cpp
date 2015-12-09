#ifndef _EDGE_CPP_
#define _EDGE_CPP_

#include"Edge.h"

int Edge::getID() const {
	return id;
}

int Edge::getStartVertex() const {
	return startVertex;
}

int Edge::getFinishVertex() const {
	return finishVertex;
}

#endif
