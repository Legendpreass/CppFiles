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

class UnionSet {
private:
    vector<int> fa, sz;
    int n;

public:
    UnionSet(int n) : n(n) {
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
    }
};

class Treap {
private:
    struct Node {
        int val, key, size;
        Node *lc, *rc;
        Node(int val) : val(val), key(rand()), size(1), lc(nullptr), rc(nullptr) {}
    };
    Node *root;
    int size(Node *o) { return o ? o->size : 0; }
    void update(Node *o) { o->size = size(o->lc) + size(o->rc) + 1; }
    Node *merge(Node *a, Node *b) {
        if (!a || !b) return a ? a : b;
        if (a->key < b->key) {
            a->rc = merge(a->rc, b);
            update(a);
            return a;
        } else {
            b->lc = merge(a, b->lc);
            update(b);
            return b;
        }
    }
    void split(Node *o, int k, Node *&a, Node *&b) {
        if (!o) {
            a = b = nullptr;
            return;
        }
        if (size(o->lc) < k) {
            a = o;
            split(o->rc, k - size(o->lc) - 1, a->rc, b);
            update(a);
        } else {
            b = o;
            split(o->lc, k, a, b->lc);
            update(b);
        }
    }
    void insert(int k, int val) {
        Node *a, *b;
        split(root, k, a, b);
        root = merge(merge(a, new Node(val)), b);
    }
    void erase(int k) {
        Node *a, *b, *c;
        split(root, k, a, b);
        split(b, 1, b, c);
        root = merge(a, c);
    }
    int query(int k) {
        Node *a, *b, *c;
        split(root, k, a, b);
        split(b, 1, b, c);
        int res = b->val;
        root = merge(merge(a, b), c);
        return res;
    }
public:
    Treap() : root(nullptr) {}
    void insert(int k, int val) { insert(k, val); }
    void erase(int k) { erase(k); }
    int query(int k) { return query(k); }
};

class FenwickTree {
private:
    vector<int> tree;
    int n;

public:
    FenwickTree(int n) : n(n) { tree.resize(n + 1); }
    void add(int x, int v) {
        for (int i = x; i <= n; i += lowbit(i)) tree[i] += v;
    }
    int query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += tree[i];
        return res;
    }
};

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int value) {
        propagate(node, start, end);

        if (start > end || start > r || end < l) {
            return;
        }

        if (start >= l && end <= r) {
            tree[node] += value;
            if (start != end) {
                lazy[2 * node + 1] += value;
                lazy[2 * node + 2] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, value);
        updateRange(2 * node + 2, mid + 1, end, l, r, value);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    // 查询区间最大值
    int queryRange(int node, int start, int end, int l, int r) {
        propagate(node, start, end);

        if (start > end || start > r || end < l) {
            return INT_MIN;
        }

        if (start >= l && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left_query = queryRange(2 * node + 1, start, mid, l, r);
        int right_query = queryRange(2 * node + 2, mid + 1, end, l, r);
        return max(left_query, right_query);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void update(int l, int r, int value) { updateRange(0, 0, n - 1, l, r, value); }

    int query(int l, int r) { return queryRange(0, 0, n - 1, l, r); }
};

class DynamicSegmenTree {
private:
    struct Node {
        int l, r, sum;
        Node *lc, *rc;
        Node(int l, int r) : l(l), r(r), sum(0), lc(nullptr), rc(nullptr) {}
    };
    Node *root;
    void pushup(Node *o) { o->sum = o->lc->sum + o->rc->sum; }
    void update(Node *o, int x, int v) {
        if (o->l == o->r) {
            o->sum += v;
            return;
        }
        int mid = (o->l + o->r) >> 1;
        if (x <= mid) {
            if (!o->lc) o->lc = new Node(o->l, mid);
            update(o->lc, x, v);
        } else {
            if (!o->rc) o->rc = new Node(mid + 1, o->r);
            update(o->rc, x, v);
        }
        pushup(o);
    }
    int query(Node *o, int l, int r) {
        if (o->l >= l && o->r <= r) return o->sum;
        int mid = (o->l + o->r) >> 1, res = 0;
        if (mid >= l && o->lc) res += query(o->lc, l, r);
        if (mid < r && o->rc) res += query(o->rc, l, r);
        return res;
    }

public:
    DynamicSegmenTree() { root = new Node(1, 1e9); }
    void update(int x, int v) { update(root, x, v); }
    int query(int l, int r) { return query(root, l, r); }
};

class HJTSegmenTree {
private:
    struct Node {
        int l, r, sum;
        Node *lc, *rc;
        Node(int l, int r) : l(l), r(r), sum(0), lc(nullptr), rc(nullptr) {}
    };
    vector<Node *> root;
    void pushup(Node *o) { o->sum = o->lc->sum + o->rc->sum; }
    void update(Node *o, Node *&p, int x, int v) {
        if (o->l == o->r) {
            p->sum = o->sum + v;
            return;
        }
        int mid = (o->l + o->r) >> 1;
        if (x <= mid) {
            if (!p->lc) p->lc = new Node(o->l, mid);
            if (!o->lc) o->lc = new Node(o->l, mid);
            update(o->lc, p->lc, x, v);
            p->rc = o->rc;
        } else {
            if (!p->rc) p->rc = new Node(mid + 1, o->r);
            if (!o->rc) o->rc = new Node(mid + 1, o->r);
            update(o->rc, p->rc, x, v);
            p->lc = o->lc;
        }
        pushup(p);
    }
    int query(Node *o, Node *p, int l, int r) {
        if (o->l >= l && o->r <= r) return p->sum - o->sum;
        int mid = (o->l + o->r) >> 1, res = 0;
        if (mid >= l && o->lc) res += query(o->lc, p->lc, l, r);
        if (mid < r && o->rc) res += query(o->rc, p->rc, l, r);
        return res;
    }
    void clear(Node *o) {
        if (!o) return;
        clear(o->lc);
        clear(o->rc);
        delete o;
    }
public:
    HJTSegmenTree() { root.push_back(new Node(1, 1e9)); }
    ~HJTSegmenTree() {
        for (Node* r : root) {
            clear(r);
        }
    }
    void update(int x, int v) {
        root.push_back(new Node(1, 1e9));
        update(root[root.size() - 2], root[root.size() - 1], x, v);
    }
    int query(int l, int r) { return query(root[root.size() - 2], root[root.size() - 1], l, r); }
};

class STTable {
private:
    vector<vector<int>> st;
    vector<int> log;
    int n, m;

public:
    STTable() = default;

    STTable(const vector<int> &v) {
        n = v.size();
        m = log2(n) + 1;
        st.resize(n, vector<int>(m));
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++) log[i] = log[i / 2] + 1;
        for (int i = 0; i < n; i++) st[i][0] = v[i];
        for (int j = 1; j < m; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int j = log[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};