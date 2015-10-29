#include"PreflowPushFlowSolver.h"
#include"DinicFlowSolver.h"
#include<iostream>

int main() {
	std::ios_base::sync_with_stdio(false);
	if (time(NULL) % 2) {
		PreflowPushFlowSolver<long long> a;
		std::cin >> a;
		a.runPreflowPush(0, a.getV() - 1);
		std::cout << a;
	} else {
		DinicFlowSolver<long long> a;
		std::cin >> a;
		a.runDinic(0, a.getV() - 1);
		std::cout << a;
	}
	return 0;
}
