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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> a(n); 
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    int ans = 0, j = 1, day = a[0].first;
    deque<pair<int, int>> q;
    q.push_back(a[0]);
    while(q.size() || j < n) {
        if(q.size() > 0) {
            auto p = q.front();
            int r = p.first + k;
            int pre = day;
            while(j < a.size() && a[j].first <= r) {
                long long s = (a[j].first - pre + 0ll) * m;
                long long eat = 0;
                while(q.size() > 0) {
                    if(s >= q.back().second) {
                        s -= q.back().second;
                        eat += q.back().second;
                        q.pop_back();
                    } else {
                        q.back().second -= s;
                        eat += s;
                        break;
                    }
                }
                ans += eat / m;
                q.push_back(a[j]);
                pre = a[j].first;
                j++;
            }
            if(pre != r) {
                long long s = (r - pre + 0ll) * m;
                long long eat = 0;
                while(q.size() > 0) {
                    if(s >= q.back().second) {
                        s -= q.back().second;
                        eat += q.back().second;
                        q.pop_back();
                    } else {
                        q.back().second -= s;
                        eat += s;
                        break;
                    }
                }
                ans += eat / m;
            }
            day = r;
            while(q.size() > 0 && q.front().first + k - 1 < day) q.pop_front();
        } else {
            day = a[j].first;
            q.push_back(a[j]);
            j++;
        }
    }

    cout << ans << endl;
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
