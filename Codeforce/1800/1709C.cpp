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

//1:39 - 1:57
void yes() {
    cout << "YES" << endl;
}

void no() {
    cout << "NO" << endl;
}

bool ok(string& s) {
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') cnt++;
        else {
            if(cnt == 0) return false;
            cnt--;
        }
    }

    return cnt == 0;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            cnt++;
        }
    }

    string t = "";
    int more = n / 2 - cnt;
    int p1 = -1, p2 = -1;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != '?') {
            t += s[i];
        } else {
            if(more > 0) {
                more--;
                t += '(';
                p1 = i;
            } else {
                t += ')';
                if(p2 == -1) p2 = i;
            }
        }
    }
    
    //cout << t << " " << p1 << " " << p2 << endl;
    
    if(p1 != -1 && p2 != -1) {
        swap(t[p1], t[p2]);
        if(ok(t)) {
            no();
            return;
        }
    }

    //t is the always valid
    cnt = 0;
    
    
    yes();
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
