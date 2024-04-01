const int maxn = 100005;
const int maxm = 200005;
int stack[maxm];
struct edge {
	int u, v, id;
	edge *nx;
	edge *rev;
	int tp;
}p[maxm * 2], *h[maxn];
int cnt = 0;
void addedge(int u, int v, int id, int t) {
	edge *new1 = &p[cnt++];
	new1->u = u, new1->v = v, new1->nx = h[u], new1->id = id, h[u] = new1, new1->tp = 0;
	if(t == 1) { // undirected case
		edge *new2 = &p[cnt++];
		new2->u = v, new2->v = u, new2->nx = h[v], new2->id = -id, h[v] = new2, new2->tp = 0; // -id: travel in the reverse direction
		new1->rev = new2, new2->rev = new1;
	}
}
int top = 0;
void dfs(int a, int t) { // need the graph to be connected
	for(; h[a];) {
		if(h[a]->tp) {
			h[a] = h[a]->nx;
			continue;
		}
		if(t == 1)
			h[a]->rev->tp = 1;
		int lid = h[a]->id, lv = h[a]->v;
		h[a] = h[a]->nx;
		dfs(lv, t);
		stack[top++] = lid;
	}
}
void otp() { // Output the path. Important: need to reverse the stack
	for (int i = top - 1; i >= 0; i--) cout << stack[i] << ' ';
}
