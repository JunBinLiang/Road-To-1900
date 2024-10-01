#include <bits/stdc++.h>
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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//3:45 : 4:15
bool good(vector<int>& a, int l, int r) {
    for(int i = l; i <= r; i++) {
        if(a[i] == 2) return true;
    }
    return false;
}

int get(vector<int>& a) {
    int n = a.size();
    int ans = 0;
    vector<pair<int, int>> stk;
    for(int i = 0; i < n; i++) {
        int j = i;
        if(a[i] == 0) {
            while(j < n && a[i] == a[j]) {
                j++;
            }
            int l = i, r = j - 1;
            int cnt = r - l + 1;
            ans += cnt;
            if(stk.size() > 0) {
                //cout << "gg " << ans <<"  " << stk.back().first << " " << stk.back().second << endl;
                if(good(a, stk.back().first, stk.back().second)) {
                    ans--;
                    cnt--;
                }
            }
            stk.push_back({cnt, -1});
        } else {
            while(j < n && a[j] != 0) {
                j++;
            }
            int l = i, r = j - 1;
            ans++;
            if(stk.size() == 0 || stk.back().first == 0) {
                a[r] = 2; //so I can take right
            } else {
                ans--;
            }
            stk.push_back({l, r});
        }
        i = j - 1;
        //cout << i << "  " << ans << endl;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans1 = get(a);
    reverse(a.begin(), a.end());
    int ans2 = get(a);

    cout << min(ans1, ans2) << endl;
    //cout << ans1 << endl;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
