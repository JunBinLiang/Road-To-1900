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

//12:45 - 1:42
bool ok(vector<int>& a, int index) {
    int t = 2;
    for(int i = index + 1; i < a.size(); i++) {
        if(a[i] < t) return false;
        t++;
    }
    return true;
}

bool can(vector<int>& a, int index) { //check if i can reach both at mid point
    int n = a.size();
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        int dis = abs(index - i);
        b[i] = a[i] - dis;
    }   

    vector<int> l(n), r(n);
    for(int i = 0; i < n; i++) {
        l[i] = b[i];
        if(i) l[i] = min(l[i], l[i - 1]);
    }
    for(int i = n - 1; i >= 0; i--) {
        r[i] = b[i];
        if(i + 1 < n) r[i] = min(r[i], r[i + 1]);
    }
    
    int cnt = 1;
    int t = 2;
    int left = index - 1, right = index + 1;
    while(left >= 0 && right < n) {
        if(r[right] == cnt) {
            right++;
            t++;
        } else {
            if(a[left] < t) return false;
            t++;
            cnt++;
            left--;
        }
    }
    while(left >= 0) {
        if(a[left] < t) return false;
        t++;
        left--;
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;

    int p1 = -1;
    int l = 0, r = n - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(a, mid)) {
            p1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if(p1 == -1) {
        cout << 0 << endl;
        return;
    }
    
    l = p1; r = n - 1;
    int p2 = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(can(a, mid)) {
            p2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    //cout << p1 << " " << p2 << endl;

    if(p2 != -1) {
        cout << p2 - p1 + 1 << endl;
    } else {
        cout << 0 << endl;
    }

}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
