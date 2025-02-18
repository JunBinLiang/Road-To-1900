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

const int N = 1e5 + 100;
int a[N], b[N];

const int FENWICK_SIZE = 200000 + 1000;
struct Fenwick {
    int tree[FENWICK_SIZE];
    int sz;
    void init(int n) {
        sz = n;
        for(int i = 0; i <= n + 1; i++) tree[i] = 0;
    }

    void update(int i, int val) {
        i++;
        while(i < sz){
            tree[i] += val;
            i += (i & -i);
        }
    }

    int pre(int i) {
        int sum = 0;
        while(i > 0){
            sum += tree[i];
            i -= ( i & -i);
        }
        return sum;
    }
    int query(int i, int j) {
        return pre(j + 1) - pre(i);
    }
} tr[2];

long long odd = 0;
long long cal(int k, int n) {
    int SHIFT = n + 10;
    long long ans = 0;
    tr[0].init(n * 2 + 100);
    tr[1].init(n * 2 + 100);
    int s = 0;
    unordered_map<int, int> mp[2];
    for(int i = 0; i < n; i++) {
        if(a[i] > k) {
            s++;
        } else {
            s--;
        }
        if(i % 2 == 1 && s > 0) {
            ans++;
        }
        ans += tr[i % 2].query(0, s + SHIFT - 1);
        tr[i % 2].update(s + SHIFT, 1);

        if(i % 2 == 1 && s == 0) ans++;
        ans += mp[i % 2][s];
        mp[i % 2][s]++;
    }

    tr[0].init(n * 2 + 100);
    tr[1].init(n * 2 + 100);
    mp[0].clear();
    mp[1].clear();
    s = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < k) {
            s++;
        } else {
            s--;
        }
        if(i % 2 == 1 && s > 0) {
            ans++;
        }
        
        ans += tr[i % 2].query(0, s + SHIFT - 1);
        tr[i % 2].update(s + SHIFT, 1);
        
        if(i % 2 == 1 && s == 0) ans++;
        ans += mp[i % 2][s];
        mp[i % 2][s]++;
    }
    
    mp[0].clear();
    mp[1].clear();
    s = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == k) continue;
        int j = i;
        vector<int> c;
        while(j < n && a[j] != k) {
            if(a[j] > k) c.push_back(1);
            else c.push_back(-1);
            j++;
        }

        mp[0].clear();
        mp[1].clear();
        s = 0;
        for(int t = 0; t < c.size(); t++) {
            s += c[t];
            if(t % 2 == 1 && s == 0) ans--;
            ans -= (mp[t % 2][s]);
            mp[t % 2][s]++;
        }
        i = j - 1;
    }
    
    ans += (odd);
    return ans;
    
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    odd = 0;
    for(int i = 1; i <= n; i += 2) {
        odd += (n - i + 1);
    }
    
    long long ans = (n + 1ll) * n / 2;
    ans *= 10;
    for(int k = 1; k <= 10; k++) {
        ans -= cal(k, n);
    }
    cout << ans + odd << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

