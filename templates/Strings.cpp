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
#define X            first
#define Y            second
#define all(v)       (v).begin(), (v).end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define MOD          998244353
#define HASHMOD      1000000000000000003
#define IOS          ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define endl         '\n'

//================================SOME TEMPLATES HERE================================//

int kmp(const string &text, const string &pattern) {
    string s = pattern + "#" + text;
    int n = s.size(), m = pattern.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int len = pi[i - 1];
        while (len && s[i] != s[len]) len = pi[len - 1];
        if (s[i] == s[len]) pi[i] = len + 1;
        if (pi[i] == m) return i - 2 * m;
    }
    return -1;
}

vector<int> Z_function(const string &s) {
    int n = s.size();
    vector<int> Z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) Z[i] = min(r - i + 1, Z[i - l]);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) Z[i]++;
        if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
    }
    return Z;
}

vector<int> manacher(const string &s) {
    string t = "$#";
    for (auto c : s) t += c, t += '#';
    int n = t.size();
    vector<int> p(n);
    for (int i = 1, mx = 0, id = 0; i < n; i++) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) p[i]++;
        if (i + p[i] > mx) mx = i + p[i], id = i;
    }
    return p;
}

class Hash {
private:
    static const int MAXN = 1e6 + 5;
    static const int BASE = 131;
    int p[MAXN], h[MAXN];

public:
    Hash() {
        p[0] = 1;
        for (int i = 1; i < MAXN; i++) p[i] = p[i - 1] * BASE % HASHMOD;
    }
    void init(const string &s) {
        int n = s.size();
        for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * BASE + s[i - 1]) % HASHMOD;
    }
    int get(int l, int r) { return (h[r] - h[l - 1] * p[r - l + 1] % HASHMOD + HASHMOD) % HASHMOD; }
};

class Trie {
private:
    static const int MAXN = 1e6 + 5;
    int ch[MAXN][26], val[MAXN], cnt;
public:
    Trie() { cnt = 1; }
    void insert(const string &s) {
        int u = 1;
        for (auto c : s) {
            int idx = c - 'a';
            if (!ch[u][idx]) ch[u][idx] = ++cnt;
            u = ch[u][idx];
        }
        val[u]++;
    }
    int query(const string &s) {
        int u = 1;
        for (auto c : s) {
            int idx = c - 'a';
            if (!ch[u][idx]) return 0;
            u = ch[u][idx];
        }
        return val[u];
    }
};

class AC_Automaton {
private:
    static const int MAXN = 1e6 + 5;
    static const int MAXM = 26;
    int ch[MAXN][MAXM], val[MAXN], fail[MAXN], cnt;
    queue<int> q;

public:
    AC_Automaton() { cnt = 1; }
    void insert(const string &s) {
        int u = 1;
        for (auto c : s) {
            int idx = c - 'a';
            if (!ch[u][idx]) ch[u][idx] = ++cnt;
            u = ch[u][idx];
        }
        val[u]++;
    }
    void build() {
        for (int i = 0; i < MAXM; i++)
            if (ch[1][i]) q.push(ch[1][i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < MAXM; i++) {
                if (ch[u][i]) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                } else {
                    ch[u][i] = ch[fail[u]][i];
                }
            }
        }
    }
    int query(const string &s) {
        int u = 1, res = 0;
        for (auto c : s) {
            int idx = c - 'a';
            u = ch[u][idx];
            for (int j = u; j && val[j] != -1; j = fail[j]) {
                res += val[j];
                val[j] = -1;
            }
        }
        return res;
    }
};