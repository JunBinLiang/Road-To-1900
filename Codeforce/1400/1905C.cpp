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

//5:44 - 6 : 01
bool same(string& s, string& t, int l, int r) {
    for(int i = l; i <= r; i++) {
        if(s[i] != t[i]) return false;
    }
    return true;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;

    string t = s;
    sort(t.begin(), t.end());

    if(s == t) {
        cout << 0 << endl;
        return;
    }

    vector<queue<int>> q(26);
    for(int i = 0; i < s.size(); i++) {
        q[s[i] - 'a'].push(i);
    }

    //find the largest
    int p = 0;
    string seq = "";
    while(p < n) {
        char c = s[p];
        int index = p;
        for(int j = 25; j >= 0; j--) {
            while(q[j].size() > 0 && q[j].front() < p) q[j].pop();
            if(q[j].size() > 0) {
                index = q[j].front();
                c = s[index];
                break;
            }
        }
        
        if(!same(s, t, p, index - 1)) {
            cout << -1 << endl;
            return;
        }
        seq += c;
        p = index + 1;
    }

    int ans = 0;
    for(int i = 0; i < seq.size(); i++) {
        if(seq[i] != seq[0]) ans++;
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
