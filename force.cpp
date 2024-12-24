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

// inline int read() {
//     int re = 0, val = 1, c = getchar();
//     while (c < '0' || c > '9') val = c == '-' ? -1 : 1, c = getchar();
//     while (c >= '0' && c <= '9') re = (re << 3) + (re << 1) + (c ^ 48), c = getchar();
//     return re * val;
// }

// inline void write(int w) {
//     if (w == 0) putchar('0');
//     if (w < 0) putchar('-'), w *= -1;
//     int c[20], pos = 0;
//     while (w) c[++pos] = (w % 10 ^ 48), w /= 10;
//     for (int i = pos; i; i--) putchar(c[i]);
//     putchar('\n');
// }

class custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

//================================MY CODE STARTS HERE================================//

// senpai! kore dekiru kana?
// omoshiroi desu ne!

// 励志红名的大一蒟蒻ToT

void senpaiSolve() {
    // BRO REMEMBER TO CHECK THE MOD VALUE
    // BRO I SET INT TO LONG LONG SO YOU CAN'T HACK ME BY USING HUGE NUMBER :D
    
}

signed main() {
    IOS;  // YOU USE IOS THEN YOU CAN'T USE READ() AND WRITE()

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("fout.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    clock_t c1 = clock();
    while (t--) {
        senpaiSolve();
    }

    // clock_t c1 = clock();
    // senpaiSolve();

end:
    cerr << "Time used: " << clock() - c1 << "ms" << endl;
    return 0;
}
