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

//7:20 - 8:44
const int SIZE = 200000 + 100;
struct Fenwick {
  int tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

void no() {
    printf("NO\n");
}
void yes() {
    printf("YES\n");
}

const int N = 2e5 + 100;
int a[N], b[N];
vector<int> q[N];
set<int> pos[N];
int n;
void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);

    for(int i = 1; i <= n; i++) {
        if(a[i] > b[i]) {
            no();
            return;
        }
    }

    for(int i = 1; i <= n; i++) {
        pos[i].clear();
        q[i].clear();
    }
    for(int i = 1; i <= n; i++) pos[a[i]].insert(i);

    for(int i = 1; i <= n; i++) {
        q[b[i]].push_back(i);
    }
    
    vector<pair<int, int>> d;
    for(int i = 1; i <= n; i++) {
        d.push_back({a[i], i});
    }

    set<int> ban;
    ban.insert(0); ban.insert(n + 1);
    tr.init(n + 2);
    for(int i = 1; i <= n; i++) tr.update(i, 1);

    sort(d.begin(), d.end());
    int j = 0;
    for(int t = 1; t <= n; t++) {
        if(q[t].size() == 0) continue;
        while(j < d.size() && d[j].first <= t) {
            tr.update(d[j].second, -1);
            j++;
        }

        if(pos[t].size() == 0) {
            no();
            return;
        }

        for(int index : q[t]) {
            auto it = ban.upper_bound(index);
            int R = *it; //ban r
            it--;
            int L = *it; //ban l
            
            //cout << index << " " << t << "   |" << L << " " << R << endl;
            
            bool ok = false;
            auto itr = pos[t].upper_bound(index - 1);
            int l = -1, r = -1;
            if(itr != pos[t].end()) {
                r = *itr;
                if(r < R && tr.query(index, r) == 0) {
                    ok = true;
                }
            }
            if(itr != pos[t].begin()) {
                itr--;
                l = *itr;
                if(l >= L && tr.query(l, index) == 0) {
                    ok = true;
                }
            }
            //cout << index << " " << t << "   |" << l << " " << r << pos[t] << endl << endl; 
            
            if(!ok) {
                no();
                return;
            }
            
        }

        for(int index : q[t]) {
            ban.insert(index);
        }
    }

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
