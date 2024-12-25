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

class Dinic {
    struct Edge {
        int from, to, cap, flow;
    };
    vector<Edge> edges;
    vector<vector<int>> G;
    vector<int> d, cur;
    int n, m, s, t;

    bool bfs() {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        q.push(s);
        d[s] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (d[e.to] == -1 && e.cap > e.flow) {
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    int dfs(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
public:
    Dinic(int n) : n(n), m(0) {
        G.resize(n);
        d.resize(n);
    }

    void addEdge(int from, int to, int cap) {
        edges.push_back({from, to, cap, 0});
        edges.push_back({to, from, 0, 0});
        G[from].push_back(m++);
        G[to].push_back(m++);
    }

    int maxFlow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            flow += dfs(s, LLONG_MAX);
        }
        return flow;
    }
};

class Hungarian {
    vector<vector<int>> G;
    vector<int> match;
    vector<bool> vis;
    int n, m;

    bool dfs(int u) {
        for (auto v : G[u]) {
            if (!vis[v]) {
                vis[v] = true;
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
public:
    Hungarian(int n, int m) : n(n), m(m) {
        G.resize(n);
        match.resize(m, -1);
        vis.resize(m);
    }

    void addEdge(int u, int v) {
        G[u].push_back(v);
    }

    int maxMatching() {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            fill(vis.begin(), vis.end(), false);
            if (dfs(i)) ans++;
        }
        return ans;
    }

    vector<int> getMatch() {
        return match;
    }
};
