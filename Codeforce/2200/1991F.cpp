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

//7:50 - 8:59
bool check(vector<int>& a, int mx1, int mx2) {
    if(a.size() != 4) return false;
    long long s = (a[0] + 0ll) + a[1] + a[2] + a[3];
    
    int index = -1;
    for(int i = 0; i < 4; i++) {
        if(a[i] > mx2) {
            index = i;
        }
    }

    if(index != -1) {
        for(int i = 0; i < 4; i++) {
            if(i == index) continue;
            for(int j = i + 1; j < 4; j++) {
                if(j == index) continue;
                long long s2 = a[i] + a[j], s1 = s - s2;
                if(s1 > mx1 && s2 > mx2) return true;
            }
        }
        return false;
    } else {
        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 4; j++) {
                long long s1 = a[i] + a[j], s2 = s - s1;
                if(s1 > mx1 && s2 > mx2) return true;
                if(s1 > mx2 && s2 > mx1) return true;
            }
        }
        return false;
    }
}

bool ok(vector<int>& a) {
    int n = a.size();
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    vector<int> b;
    for(int i = 0; i < n - 2; i++) {
        if(a[i] < a[i + 1] + a[i + 2]) {
            b.push_back(i);
        }
    }
    if(b.size() < 2) {
        return false;
    }
    
    if(b.back() - b[0] >= 3) return true;
    
    for(int i = 0; i < b.size(); i++) {
        for(int j = i + 1; j < b.size(); j++) {
            vector<int> c;
            for(int k = 0; k < n && c.size() < 4; k++) {
                if(k == b[i] || k == b[j]) continue;
                if(k < b[i]) continue;
                c.push_back(a[k]);
            }
            if(check(c, a[b[i]], a[b[j]])) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        int sz = r - l + 1;
        vector<int> b;
        if(sz <= 200) {
            for(int j = l; j <= r; j++) b.push_back(a[j]);
        } else {
            for(int j = l; j <= l + 200; j++) {
                b.push_back(a[j]);
            }
        }
        if(ok(b)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
