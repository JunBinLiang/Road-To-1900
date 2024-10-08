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
#include <deque>

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
ostream &operator<<(ostream &out, const set<T> &a) {
  out << "[";
  bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;}
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


//4:11 - 4:31
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> ans;
    for(int i = 0; i < 40; i++) {
        sort(a.begin(), a.end());
        if(a[0] == a.back() && a[0] == 0) break;
        
        int x = -1;
        int mindif = 2000000000;
        for(int j = 0; j < n - 1; j++) {
            if(a[j] + 1 < a[j + 1]) {
                int t = (a[j + 1] - a[j]) / 2 + a[j];
                int dif = max(abs(a[0] - t), abs(a.back() - t));
                if(dif < mindif) {
                    mindif = dif;
                    x = t;
                }
            }
        }
        
        if(a[0] == a.back()) {
            x = a[0];
        }

        if(x == -1) break;
        
        ans.push_back(x);
        for(int& v : a) v = abs(v - x);
        
        //cout << x << "  " << a << endl;
    }

    bool ok = true;
    for(int& x : a) {
        if(x != 0) {
            ok = false;
        }
    }
    if(!ok) {
        cout << -1 << endl;
        return;
    }


    cout << ans.size() << endl;
    for(int x : ans) cout << x << " ";
    cout << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
