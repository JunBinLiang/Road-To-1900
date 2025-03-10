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
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)

using ll = long long;

namespace Fenwick {
    const int FENWICK_SIZE = 600000 + 1000;
    struct Fenwick {
        long long tree[FENWICK_SIZE];
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
 
        long long pre(int i) {
            long long sum = 0;
            while(i > 0){
                sum += tree[i];
                i -= ( i & -i);
            }
            return sum;
        }
        long long query(int i, int j) {
            return pre(j + 1) - pre(i);
        }
    } tr;
}
 
using namespace Fenwick; 

void solve() {
    int n;
    string s;
    cin >> n >> s;
    long long ans = 0;
    /*for(int i = 0; i < n; i++) {
        int cnt0 = 0, cnt1 = 0;
        for(int j = i; j < n; j++) {
            if(s[j] == '0') cnt0++;
            else cnt1++;

            if(cnt0 >= cnt1 * 3 + 2) {
                ans++;
            } else {
                if(cnt0 == cnt1 * 3 - 1) ans++;
            }
        }
    }
    cout << ans << endl;*/
    int ps = 0;
    map<int, int> mp;
    vector<int> a = {0};
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') ps++;
        else ps -= 3;
        if(ps == -1) ans++;
        if(mp.find(ps + 1) != mp.end()) {
            ans += mp[ps + 1];
        } 
        a.push_back(ps);
        a.push_back(ps - 2);
        mp[ps]++;
    }

    int id = 1;
    sort(a.begin(), a.end());
    mp.clear();
    for(int i = 0; i < a.size(); i++) {
        if(mp.find(a[i]) == mp.end()) {
            mp[a[i]] = id++;
        }
    }
    tr.init(id + 10);

    ps = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') ps++;
        else ps -= 3;

        if(ps >= 2) {
            ans++;
        }
        ans += tr.query(0, mp[ps - 2]);
        tr.update(mp[ps], 1);
    }

    cout << ans << endl;

}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
