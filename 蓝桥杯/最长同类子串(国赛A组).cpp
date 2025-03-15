//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P10992
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 1e5 + 10;
const int MOD = 1e9 + 7, BASE1 = 26, BASE2 = 101;
unsigned long long p1[N], h1[26], p2[N], h2[N];

deque<int> d[26];

void init() {
    p1[0] = 1;
    for(int i = 1; i < N; i++) {
        p1[i] = p1[i - 1] * BASE1;
    }

    p2[0] = 1;
    for(int i = 1; i < N; i++) {
        p2[i] = p2[i - 1] * BASE2;
    }
}

bool ok(string& s, string& t, int k) {
    int n = s.size(), m = t.size();
    for(int i = 0; i < 26; i++) {
        d[i].clear();
        h1[i] = 0;
        h2[i] = 0;
    }

    //hash s
    set<pair<unsigned long long, unsigned long long>> vis;
    for(int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        
        if(d[c].size()) {
            int dif = i - d[c].back();
            h1[c] = h1[c] * BASE1 + dif;
            h2[c] = h2[c] * BASE2 + dif;
        }
        d[c].push_back(i);

        if(i + 1 >= k) {
            /*cout << "gg " << (i - k + 1) << "  " << i << endl;
            for(int j = 0; j < 26; j++) cout << h1[j] << " ";
            cout  << endl;
            for(int j = 0; j < 26; j++) cout << h2[j] << " ";
            cout  << endl;*/
            
            
            vector<pair<int, int>> a;
            for(int j = 0; j < 26; j++) {
                if(d[j].size()) {
                    a.push_back({d[j].back(), j});
                }
            }
            sort(a.begin(), a.end());
            long long ha1 = 0, ha2 = 0;
            for(int j = a.size() - 1; j >= 0; j--) {
                int c = a[j].second;
                int sz = d[c].size();
                ha1 = ha1 * p1[sz] + h1[c];

                ha2 = ha2 * p2[sz] + h2[c];
                //cout << c << "  " << sz << "  " << h1[c] << endl;
            }
            vis.insert({ha1, ha2});
            
            //cout << endl;
            
            int j = i - k + 1;
            c = s[i - k + 1] - 'a';
            d[c].pop_front();
            if(d[c].size()) {
                int dif = d[c].front() - j;
                h1[c] -= (p1[d[c].size() - 1] * dif);
                h2[c] -= (p2[d[c].size() - 1] * dif);
            }
        }
    }


    //hash t
    for(int i = 0; i < 26; i++) {
        d[i].clear();
        h1[i] = 0;
        h2[i] = 0;
    }

    for(int i = 0; i < m; i++) {
        int c = t[i] - 'a';
        
        if(d[c].size()) {
            int dif = i - d[c].back();
            h1[c] = h1[c] * BASE1 + dif;
            h2[c] = h2[c] * BASE2 + dif;
        }
        d[c].push_back(i);

        if(i + 1 >= k) {
            vector<pair<int, int>> a;
            for(int j = 0; j < 26; j++) {
                if(d[j].size()) {
                    a.push_back({d[j].back(), j});
                }
            }
            sort(a.begin(), a.end());
            long long ha1 = 0, ha2 = 0;
            for(int j = a.size() - 1; j >= 0; j--) {
                int c = a[j].second;
                int sz = d[c].size();
                ha1 = ha1 * p1[sz] + h1[c];

                ha2 = ha2 * p2[sz] + h2[c];
            }
            if(vis.find({ha1, ha2}) != vis.end()) {
                return true;
            }
            
            int j = i - k + 1;
            c = t[i - k + 1] - 'a';
            d[c].pop_front();
            if(d[c].size()) {
                int dif = d[c].front() - j;
                h1[c] -= (p1[d[c].size() - 1] * dif);
                h2[c] -= (p2[d[c].size() - 1] * dif);
            }
        }
    }
    return false;
}

void solve() {
    init();
    string s, t;
    cin >> s >> t;
    int l = 1, r = min(s.size(), t.size());
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(s, t, mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}














#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 1e5 + 10;
const int MOD = 1e9 + 7, BASE = 101;
unsigned long long p[N];
int lst1[N], nxt1[N], lst2[N], nxt2[N];
int lst[26];
deque<int> d[26];

void init(string& s, string& t) {
    memset(lst1, -1, sizeof lst1);
    memset(lst2, -1, sizeof lst2);
    memset(nxt1, -1, sizeof nxt1);
    memset(nxt2, -1, sizeof nxt2);
    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = p[i - 1] * BASE;
    }

    vector<int> pos(26, -1);
    for(int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        lst1[i] = pos[c];
        nxt1[pos[c]] = i; 
        pos[c] = i; 
    }

    pos = vector(26, -1);
    for(int i = 0; i < t.size(); i++) {
        int c = t[i] - 'a';
        lst2[i] = pos[c];
        nxt2[pos[c]] = i; 
        pos[c] = i; 
    }
    
    /*for(int i = 0; i < t.size(); i++) {
        cout << lst2[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < t.size(); i++) {
        cout << nxt2[i] << " ";
    }
    cout << endl << endl;*/
}

bool ok(string& s, string& t, int k) {
    int n = s.size(), m = t.size();

    unordered_set<unsigned long long> us;
    unsigned long long h = 0;
    for(int i = 0; i < n; i++) {
        int dif = 0;
        if(lst1[i] != -1 && i - lst1[i] < k) {
            dif = i - lst1[i];
        }
        h = h * BASE + dif;
        
        if(i + 1 >= k) {
            us.insert(h);
            int j = i - k + 1;
            int dif = 0;
            if(nxt1[j] != -1 && nxt1[j] <= i) {
                dif = i - nxt1[j];
                h = h - ((nxt1[j] - j) * p[i - nxt1[j]]);
            }
        }
    }

    h = 0;
    for(int i = 0; i < m; i++) {
        int dif = 0;
        if(lst2[i] != -1 && i - lst2[i] < k) {
            dif = i - lst2[i];
        }
        h = h * BASE + dif;
        
        if(i + 1 >= k) {
            if(us.find(h) != us.end()) {
                return true;
            }
            int j = i - k + 1;
            int dif = 0;
            if(nxt2[j] != -1 && nxt2[j] <= i) {
                dif = i - nxt2[j];
                h = h - ((nxt2[j] - j) * p[i - nxt2[j]]);
            }

        }
    }
    return false;
}

void solve() {
    string s, t;
    cin >> s >> t; 
    init(s, t);
    int l = 1, r = min(s.size(), t.size());
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(s, t, mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
