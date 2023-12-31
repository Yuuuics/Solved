#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int N = 3e5 + 5;

int n, rt, u, v, s[N], g[N], z[N];
i64 ans, c1[N], c2[N];
vector<int> e[N];

int lowbit(int x) {
	return x & -x;
}

void add(i64 *c, int x, int k) {
	++x;
	while (x <= n + 1) {
		c[x] += k;
		x += lowbit(x);
	}
}

i64 query(i64 *c, int x) {
	++x;
	i64 res = 0;
	while (x) {
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}

void dfs1(int x, int f) {
	s[x] = 1, g[x] = 0;
	bool flag = 1;
	for (size_t i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f) continue;
		dfs1(y, x);
		s[x] += s[y];
		g[x] = max(g[x], s[y]);
		if (s[y] > n / 2) flag = 0;
	}
	if (n - s[x] > n / 2) flag = 0;
	if (flag) rt = x;
}

void dfs2(int x, int f) {
	add(c1, s[f], -1);
	add(c1, n - s[x], 1);
	if (x ^ rt) {
		ans += x * query(c1, n - 2 * g[x]);
		ans -= x * query(c1, n - 2 * s[x] - 1);
		ans += x * query(c2, n - 2 * g[x]);
		ans -= x * query(c2, n - 2 * s[x] - 1);
		if (!z[x] && z[f]) z[x] = 1;
		ans += rt * (s[x] <= n - 2 * s[z[x] ? v : u]);
	}
	add(c2, s[x], 1);
	for (size_t i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (y == f) continue;
		dfs2(y, x);
	}
	add(c1, s[f], 1);
	add(c1, n - s[x], -1);
	if (x ^ rt) {
		ans -= x * query(c2, n - 2 * g[x]);
		ans += x * query(c2, n - 2 * s[x] - 1);
	}
}

void solve() {
    // freopen("centroid.in", "r", stdin);
    // freopen("centroid.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) e[i].clear();
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	ans = 0;
	dfs1(1, 0);
	dfs1(rt, 0);
	u = v = 0;
	for (size_t i = 0; i < e[rt].size(); i++) {
		int x = e[rt][i];
		if (s[x] > s[v]) v = x;
		if (s[v] > s[u]) swap(u, v);
	}
	for (int i = 1; i <= n + 1; i++) c1[i] = c2[i] = 0;
	for (int i = 0; i <= n; i++) {
		add(c1, s[i], 1);
		z[i] = 0;
	}
	z[u] = 1;
	dfs2(rt, 0);
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
	return 0;
}
