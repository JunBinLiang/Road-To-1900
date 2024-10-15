#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)


long long exgcd(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
        x = 1; // 设置b=0时的特殊解 
        y = 0;
        return a;
    }
    long long ans = exgcd(b, a % b, x, y);
    long long t = x; // 将x2, y2换算成x1, y1
    x = y;
    y = t - a / b * y;
    //cout << "exgcd " << a << " " << b << "  " << x << " "  << y << "     |" << a * x + b * y << endl;
    return ans;
}

/*
考虑两个数时的解
a1 * x + m1 = a2 * y + m2
a1 * x + a2 * y = m2 - m1


考虑将两个式子合并成
*/

void solve() {
    int n;
    cin >> n;
    long long a1, m1;
    cin >> a1 >> m1;
    bool ok = true;
    for(int i = 1; i < n; i++) {
        long long a2, m2;
        cin >> a2 >> m2;

        if(!ok) {
            continue;
        }

        long long x, y;
        long long g = exgcd(a1, a2, x, y);
        if((m2 - m1) % g != 0) {
            ok = false;
        } else {
            x *= (m2 - m1) / g; //a1 * x + a2 * y = m2 - m1 一个解
            //普通解
            long long add = abs(a2 / __gcd(a1, a2)); 
            x %= add;
            if(x < 0) x += add;
            //合并更新a1, m1, 详细看证明：https://www.acwing.com/solution/content/23099/
            m1 = x * a1 + m1;
            a1 = abs(a1 * a2 / g);
        }
    }

    if(ok) {
        cout << m1 << endl;
    } else {
        cout << -1 << endl;
    }
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
