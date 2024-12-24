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

static inline int qmul(int a, int b) {
    int res = 0;
    while (b) {
        if (b & 1) res = (res + a) % MOD;
        a = a * 2 % MOD;
        b >>= 1;
    }
    return res;
}

static inline int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = qmul(res, a);
        a = qmul(a, a);
        b >>= 1;
    }
    return res;
}

static inline int Cmn(int n, int m) {
    if (m > n) return 0;
    if (m > n - m) m = n - m;
    int res = 1;
    for (int i = 1; i <= m; i++) {
        res = res * (n - i + 1) % MOD;
        res = res * qpow(i, MOD - 2) % MOD;
    }
    return res;
}

inline int getInv(int x) {
    return qpow(x, MOD - 2);
}

static void exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

class BigInt {
private:
    static const int BASE = 1000000000; // 10^9
    static const int WIDTH = 9;
    vector<int> s;
    static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

    struct Complex {
        double real, imag;
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}
        Complex operator+(const Complex &b) const { return Complex(real + b.real, imag + b.imag); }
        Complex operator-(const Complex &b) const { return Complex(real - b.real, imag - b.imag); }
        Complex operator*(const Complex &b) const { return Complex(real * b.real - imag * b.imag, real * b.imag + imag * b.real); }
    };

    static void FFT(vector<Complex> &a, int n, int invert) {
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double angle = 2 * PI / len * (invert ? -1 : 1);
            Complex wlen(cos(angle), sin(angle));
            for (int i = 0; i < n; i += len) {
                Complex w(1);
                for (int j = 0; j < len / 2; ++j) {
                    Complex u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w = w * wlen;
                }
            }
        }
        if (invert) {
            for (Complex &x : a) x.real /= n;
        }
    }

    vector<int> multiply(const vector<int> &a, const vector<int> &b) const {
        vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size()) n <<= 1;
        fa.resize(n);
        fb.resize(n);

        FFT(fa, n, 0);
        FFT(fb, n, 0);
        for (int i = 0; i < n; ++i) fa[i] = fa[i] * fb[i];
        FFT(fa, n, 1);

        vector<int> result(n);
        for (int i = 0; i < n; ++i) result[i] = round(fa[i].real);
        return result;
    }
public:
    BigInt(long long num = 0) { *this = num; }
    BigInt(const string &str) { *this = str; }

    BigInt& operator=(long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }

    BigInt& operator=(const string &str) {
        s.clear();
        int len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int end = str.length() - i * WIDTH;
            int start = max(0LL, end - WIDTH);
            s.push_back(stoi(str.substr(start, end - start)));
        }
        return *this;
    }

    BigInt operator+(const BigInt &b) const {
        BigInt c;
        c.s.clear();
        for (int i = 0, g = 0; ; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }

    BigInt operator-(const BigInt &b) const {
        BigInt c;
        c.s.clear();
        for (int i = 0, g = 0; ; i++) {
            if (i >= s.size()) break;
            int x = s[i] - g;
            if (i < b.s.size()) x -= b.s[i];
            if (x < 0) {
                g = 1;
                x += BASE;
            } else {
                g = 0;
            }
            c.s.push_back(x);
        }
        while (c.s.size() > 1 && c.s.back() == 0) c.s.pop_back();
        return c;
    }

    BigInt operator*(const BigInt &b) const {
        vector<int> a1, b1;
        for (int x : s) a1.push_back(x);
        for (int x : b.s) b1.push_back(x);
        vector<int> c = multiply(a1, b1);
        BigInt res;
        res.s.clear();
        long long carry = 0;
        for (int i = 0; i < c.size(); i++) {
            carry += c[i];
            res.s.push_back(carry % BASE);
            carry /= BASE;
        }
        while (res.s.size() > 1 && res.s.back() == 0) res.s.pop_back();
        return res;
    }

    void print() const {
        printf("%d", s.back());
        for (int i = s.size() - 2; i >= 0; i--) printf("%09d", s[i]);
        printf("\n");
    }
};