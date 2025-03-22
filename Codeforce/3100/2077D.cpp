#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
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


void comp(vector<int>& a, vector<int>& b) {
    if(a.size() == 0) {
        a = vector<int>(b.begin(), b.end());
    } else {
        for(int i = 0; i < min(a.size(), b.size()); i++) {
            if(b[i] > a[i]) {
                a = vector<int>(b.begin(), b.end()); 
                return;
            } else if(a[i] > b[i]) {
                return;
            }
        }
        if(b.size() > a.size()) {
            a = vector<int>(b.begin(), b.end());
        }
    }
}

int T = 0, c = 0;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> ans;
    vector<int> b(a.begin(), a.end());
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    
    //for(int x : b) cout << x << " ";
    //cout << endl;

    for(int i = 0; i < min(n, 40); i++) {
        int val = b[i];
        long long s = 0;
        for(int j = 0; j < n; j++) {
            if(a[j] <= val) {
                s += a[j];
            }
        }
        
        if(val * 2 >= s) continue;
        vector<int> stk;
        long long ls = 0;
        for(int j = 0; j < n; j++) {
            if(a[j] > val) continue;
            
            while(stk.size() > 0 && a[j] > stk.back() && (ls - stk.back() + s) > val * 2) {
                int last = stk.back(); stk.pop_back();
                ls -= last;
            }
            s -= a[j];
            ls += a[j];
            stk.push_back(a[j]);
        }
        comp(ans, stk);
    }

    if(ans.size() == 0) {
        cout << -1 << endl;
        return;
    }    
    cout << ans.size() << endl;
    for(int x : ans) cout << x << " ";
    cout << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  T = t;
  while(t--) {
    solve();
  }
  return 0;
}
