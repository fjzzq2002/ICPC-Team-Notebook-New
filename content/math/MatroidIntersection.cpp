/**
 * Author: yql?
 * Description: Matroid intersection.
 */

template<typename M1, typename M2>
vector<int> matroid_intersection(int n, vector<int> w, M1 m1, M2 m2) {
	// maximize
	vector<bool> used(n);
	if (!m1(used) || !m2(used)) {
		return vector<int>();
	}
	auto find_path = [&]() {
		vector<vector<int>> adj(n + 2);
		for (int i = 0; i < n; ++i) {
			if (!used[i]) {
				for (int j = 0; j < n; ++j) {
					if (used[j]) {
						used[i] = true;
						used[j] = false;
						if (m1(used)) {
							adj[i].push_back(j);
						}
						if (m2(used)) {
							adj[j].push_back(i);
						}
						used[i] = false;
						used[j] = true;
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (!used[i]) {
				used[i] = true;
				if (m1(used)) {
					adj[i].push_back(n + 1);
				}
				if (m2(used)) {
					adj[n].push_back(i);
				}
				used[i] = false;
			}
		}
		vector<int> dist(n + 2, inf);
		vector<bool> visit(n + 2);
		vector<int> pre(n + 2, -1);
		queue<int> q;
		dist[n] = 0;
		q.push(n);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			visit[x] = false;
			for (auto y : adj[x]) {
				int cost = 0;
				if (y < n) {
					cost = used[y] ? w[y] : -w[y];
				}
				if (dist[y] > dist[x] + cost) {
					dist[y] = dist[x] + cost;
					pre[y] = x;
					if (!visit[y]) {
						visit[y] = true;
						q.push(y);
					}
				}
			}
		}
		if (dist[n + 1] == inf) {
			return false;
		}
		for (int i = pre[n + 1]; i != n; i = pre[i]) {
			used[i] = !used[i];
		}
		return true;
	};
	vector<int> ans;
	ans.push_back(0);
	while (find_path()) {
		int res = 0;
		for (int i = 0; i < n; ++i) {
			if (used[i]) {
				res += w[i];
			}
		}
		ans.push_back(res);
	}
	return ans;
}
