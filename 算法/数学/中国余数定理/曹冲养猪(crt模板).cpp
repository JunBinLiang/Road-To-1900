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
    int ans = exgcd(b, a % b, x, y);
    int t = x; // 将x2, y2换算成x1, y1
    x = y;
    y = t - a / b * y;
    //cout << "exgcd " << a << " " << b << "  " << x << " "  << y << "     |" << a * x + b * y << endl;
    return ans;
}

long long inv(long long a, long long m) { //求逆元
    long long x, y;
    exgcd(a, m, x, y);
    x %= m;
    if(x < 0) x += m; 
    return x;
}

long long crt(vector<long long>& a, vector<long long>& b) {
  long long M = 1, ans = 0;
  for (int i = 0; i < a.size(); i++) M = M * b[i];
  for (int i = 0; i < a.size(); i++) {
    long long m = M / b[i];
    ans = (ans + a[i] * m * inv(m, b[i]) % M) % M;
  }
  return (ans % M + M) % M;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i] >> a[i];
    }
    cout << crt(a, b) << endl;
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
