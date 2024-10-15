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

/*
费马小定理
*/

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


long long inverse(long long a, long long b) {
    long long x, y;
    exgcd(a, b, x, y);
    x %= b;
    if(x < 0) x += b; 
    return x;
}

void solve() {
    long long a, b, p, x;
    cin >> a >> b >> p >> x;
    long long val = 1;
    vector<long long> A;
    A.push_back(val);
    for(int i = 1; i < p - 1; i++) {
        val *= a;
        val %= p;
        A.push_back(val);
    }

    long long pinv = inverse(p - 1, p);
    
    //cout << pinv << endl;

    long long ans = 0;
    set<long long> s;
    for(int i = 0; i < A.size(); i++) {
        long long inva = inverse(A[i], p);
        long long rval = (b * inva) % p; //possible value for n
        // n value has a form of : t(p - 1) + i
        
        //check any n such that
        //(t(p - 1) + i) % p == rval
        rval -= i;
        if(rval < 0) rval += p;
        long long t = (rval * pinv) % p;

        if(x - i < 0) continue;
        long long c =  ((x - i) / ( (p - 1))); 
        c -= t;
        if(c >= 0) {
            ans += (c / p + 1);
        }
        if(i == 0 && t == 0) ans--;
    }
    cout << ans << endl;
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
