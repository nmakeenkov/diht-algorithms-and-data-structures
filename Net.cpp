#ifndef _NET_CPP_
#define _NET_CPP_

#include"Net.h"
#include<queue>

template<typename W>
size_t Net<W>::getV() const {
	return e.size();
}

template<typename W>
void Net<W>::bfs(int start, std::vector<int> &dist) const {
	dist.resize(e.size());
	for (int i = 0; i < (int)dist.size(); ++i) {
		dist[i] = -1;
	}
	std::queue<int> q;
	q.push(start);
	dist[start] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < (int)e[v].size(); ++i) {
			int to = e[v][i]->getVert();
			if (dist[to] == -1 && e[v][i]->getCap()
					- e[v][i]->getFlow() > W()) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
}

template<typename W>
W Net<W>::dfs(int v, int t, W flow, 
		std::vector<int> const &lev, std::vector<int> &ind) {
	if (v == t) {
		return flow;
	}
	W ans = W();
	for (;ind[v] < (int)e[v].size(); ++ind[v]) {
		int to = e[v][ind[v]]->getVert();
		if (lev[to] != lev[v] + 1) {
			continue;
		}
		W cur = dfs(to, t, std::min(flow, 
				e[v][ind[v]]->getCap() - e[v][ind[v]]->getFlow()),
				lev, ind);
		e[v][ind[v]]->incFlow(cur);
		ans += cur;
		flow -= cur;
		if (flow == W()) { // do not ind++
			return ans;
		}
	}
	return ans;
}

template<typename W>
void Net<W>::runDinic(int s, int t) {
	flow = W();
	while (true) {
		std::vector<int> dist;
		bfs(s, dist);
		if (dist[t] == -1) {
			break;
		}
		long long w;
		for (int i = 0; i < (int)e[s].size(); ++i) {
			w += e[s][i]->getCap() - e[s][i]->getFlow();
		}
		std::vector<int> ind(e.size(), 0);
		long long pushed = 1488;
		while (pushed > 0) {
			pushed = dfs(s, t, w, dist, ind);
			flow += pushed;
		}
	}
}

template<typename W>
void Net<W>::relable(int v, std::vector<int> &h, std::vector<int> &hCnt) {
	int newh = getV() * 2;
	for (int i = 0; i < (int)e[v].size(); ++i) {
		if (e[v][i]->getCap() > e[v][i]->getFlow()) {
			newh = std::min(h[e[v][i]->getVert()] + 1, newh);
		}
	}
	hCnt[h[v]]--;
	int gapC = getV();
	if (hCnt[h[v]] == 0)
		gapC = h[v];	
	h[v] = newh;
	hCnt[h[v]]++;
	if (gapC < getV()) {
		for (int i = 0; i < (int)h.size(); ++i) {
			if (h[i] > gapC && h[i] < getV()) {
				hCnt[h[i]]--;
				h[i] = getV();
				hCnt[h[i]]++;
			}
		}
	}
}

template<typename W>
void Net<W>::push(int v, FlowEdge<W> *e, std::vector<W> &exc,
		std::queue<int> &q) {
	W f = std::min(exc[v], e->getCap() - e->getFlow());
	e->incFlow(f);
	exc[v] -= f;
	int u = e->getVert();
	exc[u] += f;
	if (exc[u] > W() && exc[u] <= f) { // was <= 0 and now >= 0
		q.push(u);
	}
}

template<typename W>
void Net<W>::runPreflowPush(int s, int t) {
	std::vector<int> h(getV(), 0);
	std::vector<int> hCnt(getV() * 2, 0);
	hCnt[getV()] = 1;
	hCnt[0] = getV() - 1;
	h[s] = getV();
	std::vector<W> exc(getV(), W());
	for (int i = 0; i < (int)e[s].size(); ++i) {
		e[s][i]->incFlow(e[s][i]->getCap());
		exc[e[s][i]->getVert()] += e[s][i]->getCap();
		exc[s] -= e[s][i]->getCap();
	}
	for (int i = 0; i < (int)e[t].size(); ++i) {
		exc[t] -= e[t][i]->getRev()->getCap();
	}
	std::queue<int> q;
	for (int i = 0; i < (int)getV(); ++i) {
		if (exc[i] > 0) {
			q.push(i);
		}
	}
	std::vector<int> ind(getV(), 0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		while (exc[v] > 0) {
			if (ind[v] == (int)e[v].size()) {
				relable(v, h, hCnt);
				ind[v] = 0;
			} else {
				if (e[v][ind[v]]->getCap() - e[v][ind[v]]->getFlow() > W() && 
						h[e[v][ind[v]]->getVert()] == h[v] - 1) {
					push(v, e[v][ind[v]], exc, q);		
				} else {
					ind[v]++;
				}
			}
		}
	}
	flow = -exc[s];
}

template<typename W>
std::istream &operator>>(std::istream &in, Net<W> &g) {
	int n, m;
	in >> n >> m;
	g.e.resize(n);
	for (int i = 0; i < m; ++i) {
		int f, t, c;
		in >> f >> t >> c;
		f--;
		t--;
		FlowEdge<W> *dir = new FlowEdge<W>(i, t, c);
		FlowEdge<W> *rev = new FlowEdge<W>(f, dir);
		dir->setRev(rev);
		g.e[f].push_back(dir);
		g.e[t].push_back(rev);
	}
	return in;
}

template<typename W>
std::ostream &operator<<(std::ostream &out, Net<W> &g) {
	out << g.flow << "\n";
	int maxNum = 0;
	for (int i = 0; i < (int)g.e.size(); ++i) {
		maxNum += g.e[i].size();
	}
	maxNum /= 2; // reversed are fakes
	std::vector<W> ans(maxNum);
	for (int i = 0; i < (int)g.e.size(); ++i) {
		for (int j = 0; j < (int)g.e[i].size(); ++j) {
			if (g.e[i][j]->getNum() != -1)  { // not a fake
				ans[g.e[i][j]->getNum()] = g.e[i][j]->getFlow();
			}
		}
	}
	for (int i = 0; i < (int)ans.size(); ++i) {
		out << ans[i] << "\n";
	}
	return out;
}

#endif
