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

//2:03 - 2:32
void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            a[i][j]--;
        }
    }

    set<string> h;
    for(int i = 0; i < n; i++) {
        vector<int>& vec = a[i];
        //cout << vec << endl;
        vector<int> pos(11);
        for(int j = 0; j < vec.size(); j++) {
            pos[vec[j]] = j;
        }
        int bit = 0;
        string s = "";
        for(int j = 0; j < vec.size(); j++) {
            bit |= (1 << pos[j]);
            s += to_string(bit);
            s +="|";
            h.insert(s);
        }
    }
    
    for(int i = 0; i < n; i++) {
        vector<int>& vec = a[i];
        int ans = 0;
        int bit = 0;
        string s = "";
        for(int j = 0; j < vec.size(); j++) {
            bit |= (1 << vec[j]);
            s += to_string(bit);
            s += "|";
            if(h.find(s) != h.end()) {
                ans = j + 1;
            } else {
                break;
            }
        }
        printf("%d ", ans);
    }

    printf("\n");
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
