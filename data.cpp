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
#define X            first
#define Y            second
#define all(v)       (v).begin(), (v).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define MOD          998244353
#define HASHMOD      1000000000000000003
#define IOS          ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define endl         '\n'
#include <algorithm>
#include <random>
#define int long long

int random(int n) {  // 返回0-n-1之间的随机整数
    return rand() % n;
}
void generateRandomArray(int n, int m) {  // 随机生成长度为n的绝对值在m之内的整数序列
    for (int i = 1; i <= n; i++) {
        cout << random(2 * m + 1) - m << '\n';
    }
}

void generateIntervals(int m, int n) {  // 随机生成 m个[1,n]的子区间
    for (int i = 1; i <= m; i++) {
        int l = random(n) + 1;
        int r = random(n) + 1;
        if (l > r) swap(l, r);
        cout << l << " " << r << '\n';
    }
}

void generateTwoDimensionalArray(int n, int m, int k, int p) {  // 随机生成n行m列的二维数组
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << random(k) + p << " ";
        }
        cout << endl;
    }
}

void generateTree(int n) {                 // 随机生成一棵n个点的树，用n个点n-1条边的无向图的形式输出
    for (signed int i = 2; i <= n; i++) {  // 从2 ~ n之间的每个点i向 1 ~ i-1之间的点随机连一条边
        int fa = random(i - 1) + 1;
        int val = random(1e9) + 1;
        cout << fa << " " << i << " " << val << '\n';
    }
}

void generateGraph(int n, int m) {  // 随机生成一张n个点m条边的无向图，图中不存在重边、自环
    set<pair<int, int>> edges;      // 防止重边
    for (int i = 1; i <= n; i++) {  // 先生成一棵树，保证连通
        int fa = random(i - 1) + 1;
        edges.insert({fa, i + 1});
        edges.insert({i + 1, fa});
    }
    while (edges.size() < m) {  // 再生成剩余的 m-n+1 条边
        int x = random(n) + 1;
        int y = random(n) + 1;
        if (x != y) {
            edges.insert({x, y});
            edges.insert({y, x});
        }
    }
    // Shuffling and outputting
    vector<pair<int, int>> Edges(edges.begin(), edges.end());
    random_device rd;
    mt19937 g(rd());
    shuffle(Edges.begin(), Edges.end(), g);
    for (auto& edge : Edges) {
        cout << edge.first << " " << edge.second << '\n';
    }
}

signed main() {
    IOS;
    srand(time(0));
    int t = random(30) + 1;
    cout << t << endl;
    while (t--) {
        
    }
    return 0;
}
