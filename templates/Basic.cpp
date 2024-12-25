/*

    ____                  ___ __                   __   __   __
   / __ \____ _____  ____/ (_) /_  ____  ____     / /  / /  / /
  / /_/ / __ `/ __ \/ __  / / __ \/ __ \/ __ \   / /  / /  / /
 / ____/ /_/ / / / / /_/ / / / / / /_/ / /_/ /  /_/  /_/  /_/
/_/    \__,_/_/ /_/\__,_/_/_/ /_/\____/\____/  (_)  (_)  (_)

                         /\_/\
                      ~ ( >.< ) ~
                        (") (")

*/

//================================MACRO DEFINITION HERE================================//

#include <bits/stdc++.h>
using namespace std;

#define int          long long
#define ULL          unsigned long long
#define LD           long double
#define PII          pair<int, int>
#define EPS          1e-7
#define lowbit(x)    (x & -x)
#define mp           make_pair
#define pb           push_back
#define lb           lower_bound
#define fi           first
#define se           second
#define all(v)       (v).begin(), (v).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define MOD          998244353
#define HASHMOD      1000000000000000003
#define IOS          ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define endl         '\n'

//================================SOME TEMPLATES HERE================================//

class Kruskal {
public:
    int n, m;
    vector<int> fa, siz;
    vector<pair<int, PII>> edges;

    Kruskal(int n, int m) : n(n), m(m) {
        fa.resize(n + 1);
        siz.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            siz[i] = 1;
        }
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (siz[x] < siz[y]) swap(x, y);
        fa[y] = x;
        siz[x] += siz[y];
    }

    void add_edge(int u, int v, int w) {
        edges.pb(mp(w, mp(u, v)));
    }

    int kruskal() {
        sort(all(edges));
        int res = 0;
        for (auto &edge : edges) {
            int w = edge.fi;
            int u = edge.se.fi;
            int v = edge.se.se;
            if (find(u) != find(v)) {
                merge(u, v);
                res += w;
            }
        }
        return res;
    }
};

class Prim {
public:
    int n, m;
    vector<vector<PII>> g;
    vector<int> dis;
    vector<bool> vis;

    Prim(int n, int m) : n(n), m(m) {
        g.resize(n + 1);
        dis.resize(n + 1);
        vis.resize(n + 1);
    }

    void add_edge(int u, int v, int w) {
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }

    int prim() {
        fill(all(dis), LLONG_MAX);
        dis[1] = 0;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            int minn = LLONG_MAX, u = -1;
            for (int j = 1; j <= n; j++) {
                if (!vis[j] && dis[j] < minn) {
                    minn = dis[j];
                    u = j;
                }
            }
            if (u == -1) break;
            vis[u] = true;
            res += dis[u];
            for (auto &edge : g[u]) {
                int v = edge.fi;
                int w = edge.se;
                if (!vis[v] && w < dis[v]) {
                    dis[v] = w;
                }
            }
        }
        return res;
    }
};

class SPFA {
public:
    int n, m;
    vector<vector<PII>> g;
    vector<int> dis;
    vector<bool> inq;

    SPFA(int n, int m) : n(n), m(m) {
        g.resize(n + 1);
        dis.resize(n + 1);
        inq.resize(n + 1);
    }

    void add_edge(int u, int v, int w) {
        g[u].pb(mp(v, w));
    }

    bool spfa(int s) {
        fill(all(dis), LLONG_MAX);
        fill(all(inq), false);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        inq[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (auto &edge : g[u]) {
                int v = edge.fi;
                int w = edge.se;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        return true;
    }
};

class AStar {
public:
    int n, m;
    vector<vector<PII>> g;
    vector<int> dis;
    vector<bool> vis;

    AStar(int n, int m) : n(n), m(m) {
        g.resize(n + 1);
        dis.resize(n + 1);
        vis.resize(n + 1);
    }

    void add_edge(int u, int v, int w) {
        g[u].pb(mp(v, w));
    }

    int astar(int s, int t) {
        fill(all(dis), LLONG_MAX);
        fill(all(vis), false);
        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.push(mp(0, s));
        dis[s] = 0;
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (auto &edge : g[u]) {
                int v = edge.fi;
                int w = edge.se;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.push(mp(dis[v] + abs(v - t), v));
                }
            }
        }
        return dis[t];
    }
};