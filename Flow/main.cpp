#include"PreflowPushFlowSolver.h"
#include"DinicFlowSolver.h"
#include<iostream>

int main() {
	std::ios_base::sync_with_stdio(false);
    Net<long long> gr;
    std::cin >> gr;
	if (time(NULL) % 2) {
		PreflowPushFlowSolver a(gr);
		a.solve(0, (int)gr.getV() - 1);
	} else {
		DinicFlowSolver a(gr);
        a.solve(0, (int)gr.getV() - 1);
	}
    std::cout << gr;
	return 0;
}
