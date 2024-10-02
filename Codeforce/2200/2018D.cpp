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

const int N = 2e5 + 10;
int p[N], sz[N];
int l[N], st[N];
int tot = 0, okcnt = 0;
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void merge(int u, int v) {
    int r1 = find(u), r2 = find(v);
    if(r1 == r2) return;
    if(l[r1] > l[r2]) {
        swap(r1, r2);
    }

    //r1 -> r2
    if(st[r1]) {
        if(sz[r1] % 2 == 0) {
            if(st[r1] != 0) okcnt--;
        } else {
            if(st[r1] == 3) {
                okcnt--;
            } else {
                if(st[r1] == 1 && l[r1] % 2 == 0) {
                    okcnt--;
                }
                if(st[r1] == 2 && l[r1] % 2 == 1) {
                    okcnt--;
                }
            }
        }
    }
    
    if(st[r2]) {
        if(sz[r2] % 2 == 0) {
            if(st[r2] != 0) okcnt--;
        } else {
            if(st[r2] == 3) {
                okcnt--;
            } else {
                if(st[r2] == 1 && l[r2] % 2 == 0) {
                    okcnt--;
                }
                if(st[r2] == 2 && l[r2] % 2 == 1) {
                    okcnt--;
                }
            }
        }
    }
    
    p[r1] = r2;
    l[r2] = l[r1];
    tot -= ((sz[r1] + 1) / 2);
    tot -= ((sz[r2] + 1) / 2);
    
    sz[r2] += sz[r1];
    st[r2] |= st[r1];
    tot += ((sz[r2] + 1) / 2);
    if(sz[r2] % 2 == 0) {
        if(st[r2] != 0) okcnt++;
    } else {
        if(st[r2] == 3) {
            okcnt++;
        } else {
            if(st[r2] == 1 && l[r2] % 2 == 0) {
                okcnt++;
            }
            if(st[r2] == 2 && l[r2] % 2 == 1) {
                okcnt++;
            }
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }

    //init
    tot = 0;
    okcnt = 0;
    for(int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
        l[i] = i;
        st[i] = 0;
    }

    //should take maximum element
    vector<bool> vis(n);
    int ans = 0;
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    for(int i = 0; i < n; i++) {
        if(a[i].first == a[0].first) { //max
            st[a[i].second] |= (1 << (a[i].second % 2));
            okcnt++;
        }
    }
    

    for(int i = 0; i < n; i++) {
        int j = i;
        vector<int> indexs;
        while(j < n && a[j].first == a[i].first) {
            vis[a[j].second] = true;
            indexs.push_back(a[j].second);
            tot++;
            j++;
        }
        int s = a[0].first + a[i].first;
        //calculate size

        for(int index : indexs) {
            if(index - 1 >= 0 && vis[index - 1]) {
                merge(index - 1, index);
            }
            if(index + 1 < n && vis[index + 1]) {
                merge(index, index + 1);
            }
        }
        
        s += tot;
        if(okcnt == 0) {
            s--;
        }
        i = j - 1;
        ans = max(ans, s);
    }

    cout << ans << endl;
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
