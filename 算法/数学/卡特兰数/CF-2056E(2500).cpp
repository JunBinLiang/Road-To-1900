#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    

using namespace std;
using ll = long long;

const int MOD = 998244353;
const int N = 2e5 + 10;

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first == p2.first) {
        return p1.second > p2.second;
    }
    return p1.first < p2.first;
}


long long f[N];
long long inv(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        long long q = a / m;
        long long t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

void init() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = f[i - 1] * (4 * i - 2);
        f[i] %= MOD;
        f[i] *= inv(i + 1, MOD);
        f[i] %= MOD;
    }
}

long long get(int i) {
    if(i == 0) return 1;
    return f[i];
}


long long dfs(vector<pair<int, int>>& a, int L, int R) {
    if(L >= R) {
        return 1;
    }
    
    vector<int> ind = {L};
    int right = a[L].second;
    while(true) {
        int l = L, r = R;
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[mid].first > right) {
                p = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        if(p == -1) {
            break;
        } else {
            right = a[p].second;
            ind.push_back(p);
        }
    }
    
    long long ans = 1;
    if(ind.size() == 1) {
        ans *= dfs(a, L + 1, R);
    } else {
        int cnt = ind.size();
        ans *= get(cnt - 1);
        ans %= MOD;
        for(int i = 0; i < ind.size(); i++) {
            if(i == ind.size() - 1) {
                ans *= dfs(a, ind[i] + 1, R);
                ans %= MOD;
            } else {
                ans *= dfs(a, ind[i] + 1, ind[i + 1] - 1);
                ans %= MOD;
            }
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i].first >> a[i].second;
    }

    for(int i = 1; i <= n; i++) {
        a.push_back({i, i});
    }
    a.push_back({1, n});
    
    set<pair<int, int>> s(a.begin(), a.end());
    a = vector<pair<int, int>>(s.begin(), s.end());

    sort(a.begin(), a.end(), comp);
    
    long long ans = dfs(a, 0, a.size() - 1);
    cout << ans << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

