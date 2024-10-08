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


//3:40 - 4:07
const int N = 1e4 + 10;
vector<int> g[N];
int color[N];
bool ok = true;
void dfs(int u) {
    for(int v : g[u]) {
        if(color[v] != -1) {
            if(color[v] == color[u]) {
                ok = false;
            }
            continue;
        }
        color[v] = color[u] ^ 1;
        dfs(v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        color[i] = -1;
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ok = true;
    color[1] = 0;
    dfs(1);

    if(!ok) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }


    
    vector<int> a, b;
    vector<int> vec(3, -1);
    for(int i = 1; i <= n; i++) {
        if(color[i] == 0) a.push_back(i);
        else b.push_back(i);
    }

    if(a.size() < b.size()) swap(a, b);
    

    //play n rounds
    for(int i = 0; i < n; i++) {
        if(!ok) {
            cout << "1 2" << endl;
            int index, c;
            cin >> index >> c;
        } else {
            int c1, c2;
            cin >> c1 >> c2;
            if(c1 > c2) swap(c1, c2);
            if(c1 == 1) { //1 2 or 1 3
                if(a.size() > 0) {
                    cout << a.back() << " " << c1 << endl;
                    a.pop_back();
                } else {
                    cout << b.back() << " " << c2 << endl;
                    b.pop_back();
                }
            } else { //2 3
                if(b.size() > 0) {
                    cout << b.back() << " " << c1 << endl;
                    b.pop_back();
                } else {
                    cout << a.back() << " " << c2 << endl;
                    a.pop_back();
                }
            }
        }
    }

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
