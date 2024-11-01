#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;

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

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    int d1 = p1.first - p1.second;
    int d2 = p2.first - p2.second;
    return d1 < d2;
}

long long get(vector<long long>& p, int l, int r) {
    if(r < l) return 0;
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

//2:08 - 2:58
void solve() {
    int n, m;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end(), comp);
    reverse(a.begin(), a.end());

    vector<long long> p1, p2;
    long long s1 = 0, s2 = 0;
    for(int i = 0; i < a.size(); i++) {
        s1 += a[i].first;
        s2 += a[i].second;
        p1.push_back(s1);
        p2.push_back(s2);
    }
    
    cin >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        long long x0, y0;
        //ax + by = n
        int g = exgcd(a, b, x0, y0);
        if(n % g != 0) {
            cout << -1 << endl;
        } else {
            long long x1 = x0 * (n / g); //一个解
            long long add = abs(b / g); //取整数方便以下计算
            x1 %= add;
            if(x1 < 0) x1 += add;
            
            if(x1 * a > n) {
                cout << -1 << endl;
                continue;
            }
            
            long long ans = 0;
            int l = 0, r = (n - x1 * a) / a / add;
            while(l <= r) {
                int mid1 = l + (r - l) / 3;
                int mid2 = l + (r - l) / 3 * 2;
                int c1 = (x1 + add * mid1) * a; int d1 = n - c1;
                int c2 = (x1 + add * mid2) * a; int d2 = n - c2;
                long long ans1 = get(p1, 0, c1 - 1) + get(p2, n - d1, n - 1);
                long long ans2 = get(p1, 0, c2 - 1) + get(p2, n - d2, n - 1);;
                ans = max(ans, ans1);
                ans = max(ans, ans2);
                if(ans1 > ans2) {
                    r = mid2 - 1;
                } else {
                    l = mid1 + 1;
                }
            }
            cout << ans << endl;
        }
    }
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
