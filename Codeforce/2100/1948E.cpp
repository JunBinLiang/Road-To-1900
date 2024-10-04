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
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//4:31 - 5:22

void check(vector<int>& a, int k) {
    int n = a.size();
    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int d = abs(i - j) + abs(a[i] - a[j]);
            if(d > k) {
                cout << "gg  " << i << " " << j << endl;
            }
        }
    }
}

void add(vector<int>& cur, vector<int>& ans, int len) {
    //cout << cur << "  " << ans << endl;
    int n = cur.size();
    int half = (len + 1) / 2;
    if(cur.size() < half) {
        for(int i = 0; i < cur.size(); i++) {
            ans[cur[i]] = cur[i];
        }
        return;
    }

    int t = cur[half - 1];
    for(int i = 0; i < half; i++) {
        ans[cur[i]] = t--;
    }
    int last = cur.back();
    for(int i = half; i < n; i++) {
        ans[cur[i]] = last--;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    int len = k;
    int tot = n / len;
    if(n % len != 0) tot++;

    vector<int> cur;
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        cur.push_back(i);
        if(cur.size() == len) {
            //cout << "gg " << cur << endl;
            add(cur, ans, len);
            cur.clear();
        }
    }

    if(cur.size() > 0) {
        add(cur, ans, len);
    }
    
    
    //map<int, vector<pair<int, int>>> f;
    
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
    cout << tot << endl;
    int c = 1;
    for(int i = 1; i <= n; i++) {
        cout << c << " ";
        if((i) % len == 0) {
            c++;
        }
    } 
    cout << endl;
    
    
    /*vector<int> v1 = {0, 4, 3, 2, 1, 8, 7, 6, 5};
    check(v1, 8);
    vector<int> v2 = {0, 4, 3, 2, 1, 7, 6, 5};
    check(v2, 7);*/
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
