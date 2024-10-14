//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P1082
//https://ksmeow.moe/euclid/
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
    long long ans = exgcd(b, a % b, x, y);
    long long t = x; // 将x2, y2换算成x1, y1
    x = y;
    y = t - a / b * y;
    return ans;
}

//tutorial : https://ksmeow.moe/euclid/
void solve() {
    long long a, b, x, y;
    scanf("%lld%lld", &a, &b);
    exgcd(a, b, x, y);
    x %= b;
    if(x < 0) x += b; 
    cout << x << endl;
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
