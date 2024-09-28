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

//6:35 - 7:14
const int N = 1e5 + 10;
vector<int> g[N];
vector<int> vec; 
void dfs(int pa, int u) {
    if(pa != -1 && g[u].size() == 1) {
        //leaf
        vec.push_back(u);
    }
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
    }
}


/*int cal(string& s, char first) {
    int score = 0, cnt = 0;
    for(int u : vec) {
        if(u == 1) continue;
        if(s[u - 1] == '?') {
            cnt++;
            continue;
        }
        if(s[u - 1] != first) score++;
    }
    //cout << first << "  " << score << " " << cnt << endl;
    return score + cnt / 2;
}*/

void solve() {
    int n; string s;
    cin >> n;
    FOR(i, 0, n + 1) g[i].clear();
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> s;

    //Number of 0 1 segments equal : has weight
    //Number of 0 1 segments not equal : no weight

    vec.clear();
    dfs(-1, 1);
    
    //cout << vec << endl;

    if(s[0] == '?') {
        int s1 = 0, s2 = 1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '?') s1++;
        }
        int one = 0, zero = 0;
        for(int u : vec) {
            if(s[u - 1] == '?') s2++;
            if(s[u - 1] == '1') one++;
            else if(s[u - 1] == '0') zero++;
        }
        
        //cout << "  " << s1 << " " << s2 << endl;
        if(one == zero) {
            int internal = s1 - s2;
            if(internal % 2 == 1) {
                cout << s2 / 2 + one << endl;
            } else {
                cout << (s2 - 1) / 2 + one << endl;
            }
        } else {
            cout << max(one, zero) + (s2 - 1) / 2 << endl;
        }
    } else {
        int score = 0;
        int cnt = 0;
        for(int u : vec) {
            if(s[u - 1] == '?') {
                cnt++;
                continue;
            }
            if(s[u - 1] != s[0]) score++;
        }
        score += ((cnt + 1) / 2);
        cout << score << endl;
    }
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
