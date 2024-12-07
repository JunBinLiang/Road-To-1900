#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct AcAutomation {
    int tr[1000000 + 100][26];
    int ne[1000000 + 100], cnt[1000000 + 100];
    int mp[1000000 + 100];
    vector<int> ord;
    int id = 1;
    void init() {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        memset(cnt, 0, sizeof cnt);
        id = 1;
    }

    void clear() {
        for(int i = 0; i <= id; i++) {
            ne[i] = 0;
            cnt[i] = 0;
            for(int j = 0; j < 26; j++) tr[i][j] = 0;
        }
        id = 1;
    }

    void add(string& s, int index) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if(tr[u][c] == 0) tr[u][c] = id++;
            u = tr[u][c];
            cnt[u]++;
        }
        mp[index] = u;
    }
  
    void build() {
        queue<int> q;
        for(int i = 0; i < 26; i++) {
            if(tr[0][i] != 0) {
                q.push(tr[0][i]);
            }
        }
        while(q.size() > 0) {
            int u = q.front(); q.pop();
            ord.push_back(u);
            for(int i = 0; i < 26; i++) {
                int c = tr[u][i];
                if(!c) {
                    tr[u][i] = tr[ne[u]][i];
                } else {
                    ne[c] = tr[ne[u]][i];
                    q.push(c);
                }
            }
        }
    }
} ac;
int f[1000000 + 10];
void solve() {
    ac.init();

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ac.add(s, i);
    }

    ac.build();
    memset(f, 0, sizeof f);
    for(int i = ac.ord.size() - 1; i >= 0; i--) {
        int u = ac.ord[i];
        f[u] += ac.cnt[u];
        f[ac.ne[u]] += f[u];
    }

    for(int i = 0; i < n; i++) {
        cout << f[ac.mp[i]] << endl;
    }
    
}


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
