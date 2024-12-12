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
    int tr[100000 + 100][26];
    int ne[100000 + 100], p[100000 + 100];
    int len[100000 + 100];
    int id = 1;
    vector<int> indexs[100000 + 100];
    void init() {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        memset(p, -1, sizeof p);
        memset(len, 0, sizeof len);
        for(int i = 0; i < 100000 + 100; i++) {
            indexs[i].clear();
        }
        id = 1;
    }

    void add(string& s, int index) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'A';
            if(tr[u][c] == 0) tr[u][c] = id++;
            u = tr[u][c];
            len[u] = i + 1;
            indexs[u].push_back(index);
        }
        p[u] = index;
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
            for(int i = 0; i < 26; i++) {
                int c = tr[u][i];
                if(!c) {
                    tr[u][i] = tr[ne[u]][i];
                } else {
                    ne[c] = tr[ne[u]][i];
                    //cout << "build " << c << " " << ne[c] << endl;
                    q.push(c);
                }
            }
        }
    }
} ac1, ac2;

int L[110][1110], R[110][1110];
void solve() {
    memset(L, -1, sizeof L);
    memset(R, -1, sizeof R);

    ac1.init();
    ac2.init();

    string s;
    cin >> s;
    int m;
    cin >> m;
    
    vector<int> a;
    for(int i = 0; i < m; i++) {
        string t;
        cin >> t;
        ac1.add(t, i);
        reverse(t.begin(), t.end());
        ac2.add(t, i);
        a.push_back(t.size());
    }
    
    ac1.build();
    ac2.build();
    
    for(int i = 0, u = 0; i < s.size(); i++) {
        int c = s[i] - 'A';
        u = ac1.tr[u][c];
        int p = u;
        while (p) {
            int len = ac1.len[p];
            for(int index : ac1.indexs[p]) {
                L[index][len] = i; 
            }
            ac1.indexs[p].clear();
            p = ac1.ne[p];
        }
    }

    reverse(s.begin(), s.end());
    for(int i = 0, u = 0; i < s.size(); i++) {
        int c = s[i] - 'A';
        u = ac2.tr[u][c];
        int p = u;
        while (p) {
            int len = ac2.len[p];
            for(int index : ac2.indexs[p]) {
                R[index][len] = s.size() - i - 1; 
            }
            ac2.indexs[p].clear();
            p = ac2.ne[p];
        }
    }
    
    /*for(int i = 0; i < m; i++) {
        cout << i << endl;
        for(int l = 1; l <= a[i]; l++) cout << L[i][l] << " ";
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < m; i++) {
        cout << i << endl;
        for(int l = 1; l <= a[i]; l++) cout << R[i][l] << " ";
        cout << endl;
    }*/

    int ans = 0;
    for(int i = 0; i < m; i++) {
        if(a[i] == 1) continue;
        for(int l = 1; l <= a[i]; l++) {
            if(L[i][l] != -1) {
                if(l == a[i] || L[i][l] < R[i][a[i] - l]) {
                    ans++;
                    break;
                }
            }
        }
    }
    cout << ans << endl;
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
