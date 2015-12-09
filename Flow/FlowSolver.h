#ifndef _FLOWSOLVER_H
#define _FLOWSOLVER_H

#include"Net.h"

class FlowSolver {
protected:
    Net<long long> &graph;
public:
    FlowSolver(Net<long long> &_graph) : graph(_graph) {}
    virtual void solve(int source, int sink) = 0;
};

#endif