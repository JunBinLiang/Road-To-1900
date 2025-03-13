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


int cal(string& s) {
    int l = 0;
    int r = s.size() - 1;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        vector<int> cnt(26);
        for(int i = 0; i <= mid; i++) {
            cnt[s[i] - 'a']++;
        }
        bool ok = true;
        int L = 0, R = s.size() - 1;
        while(L < R && R > mid) {
            if(L <= mid) {
                if(!cnt[s[R] - 'a']) ok = false;
                cnt[s[R] - 'a']--;
            } else {
                if(s[L] != s[R]) {
                    ok = false;
                }
            }
            L++;
            R--;
        }        

        if(ok) {
            ans = mid + 1;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void solve() {
    string s;
    cin >> s;
    int l = 0, r = s.size() - 1;
    while(l <= r && s[l] == s[r]) {
        l++;
        r--;
    }

    if(l > r) {
        cout << 0 << endl;
        return;
    }

    s = s.substr(l, r - l + 1);
    l = 0;
    r = s.size() - 1;
    int ans = -1;
    
    string rev = s;
    reverse(rev.begin(), rev.end());
    ans = min(cal(s), cal(rev));
    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
