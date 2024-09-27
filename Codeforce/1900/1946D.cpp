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

//10:05 - 10:48
int n, x;

int get(vector<int>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

int cal(vector<vector<int>>& cnt, vector<int>& constraints) {
    int p = 0;
    int cut = 0;
    for(int j = 0; j < n; j++) {
        bool okcut = true;
        for(int constraint : constraints) {
            if(get(cnt[constraint], p, j) % 2 == 1) okcut = false;
        }
        //cout << j << " " << okcut << endl;
        if(okcut) {
            cut++;
            p = j + 1;
        }
    }
    return cut;
}

void solve() {
    cin >> n >> x;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> cnt(31, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 31; j++) {
            if(a[i] & (1ll << j)) {
                cnt[j][i] = 1;
            }
            if(i) cnt[j][i] += cnt[j][i - 1];
        }
    }

    int s = 0;
    for(int i = 0; i < 31; i++) {
        if(cnt[i].back() % 2 == 1) {
            s += (1 << i);
        }
    }

    if(s > x) {
        cout << -1 << endl;
        return;
    }

    vector<int> constraints;
    int ans = -1;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(x & (1 << i)) b = 1;
        if(b == 0) {
            if(cnt[i].back() % 2 == 1) break; //broken
            constraints.push_back(i);
            if(i == 0) ans = max(ans, cal(cnt, constraints));
        } else {
            if(cnt[i].back() % 2 == 1) {
                if(i == 0) {
                    ans = max(ans, cal(cnt, constraints));
                }
                continue; //same prefix
            }

            if(i) constraints.push_back(i);
            ans = max(ans, cal(cnt, constraints));
            if(i) constraints.pop_back();
        }
    }

    cout << ans << endl;
    
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
