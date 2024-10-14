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

long long gcd(long long a, long long b) {
    if(b == 0) return a;
    if(b > a) swap(a, b);
    return gcd(b, a % b); // 递归求解
}

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
        x = 1; // 设置b=0时的特殊解 
        y = 0;
        return a;
    }
    int ans = exgcd(b, a % b, x, y);
    int t = x; // 将x2, y2换算成x1, y1
    x = y;
    y = t - a / b * y;
    //cout << "exgcd " << a << " " << b << "  " << x << " "  << y << "     |" << a * x + b * y << endl;
    return ans;
}

/*
题意：
求 (x + tn) % L == (y + tm) % L

题解：
可以看成位置小的那个点是从0点 出发
d = y - x （x追y的距离）

简化 (这里正负值不太重要，可以自己验证一下)
(n - m)t + kL = d


let (n - m) = a and L = b;
=> ax1 + by1 = d 
*/

void solve() {
    long long x, y, n, m, L;
    cin >> x >> y >> n >> m >> L;
    
    long long x0, y0;
    long long d = y - x;
    long long a = n - m, b = L; //-1, 5
    long long g = exgcd(a, b, x0, y0);
    if(d % g != 0) {
        cout << "Impossible" << endl;
    } else {
        //x1 是ax1 + by1 = gcd(a, b) 的解    => -1 * 1 + 5 * 0 = -1
        //现在要求 ax + by = d 的x通解，x是最小整数
        
        long long x1 = x0 * (d / g); //ax + by = d 的一个解
        //通解 x = x1 + b / gcd(a, b)
        long long add = abs(b / __gcd(a, b)); //取整数方便以下计算
        x1 %= add;
        if(x1 < 0) x1 += add;
        cout << x1 << endl;
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
