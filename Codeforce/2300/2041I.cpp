#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>

using namespace std;
const int N = 2e6 + 100;
unordered_map<int, string> mp;
set<int> sets[N + 100];
int mat[256];
int fa[N];
int top[N], len[N];

struct Node {
    map<int, int> ch;
} tr[N];

int id = 1;
void add(string& s, int si) {
    int u = 0;
    for(int i = 0; i < s.size(); i++) {
        int c = mat[s[i]];
        if(tr[u].ch.find(c) == tr[u].ch.end()) {
            tr[u].ch[c] = id++;
        }
        fa[tr[u].ch[c]] = u;
        u = tr[u].ch[c];
    }

    sets[u].insert(si);
    if(top[u] == -1) {
        top[u] = si;
        len[u] = s.size();
    } else {
        if(s.size() == len[u]) {
            top[u] = min(top[u], si);
        }
    }
    
    while(u != 0) {
        int p = fa[u], mxLen = 0;
        for(auto it = tr[p].ch.begin(); it != tr[p].ch.end(); it++) {
            mxLen = max(mxLen, len[it -> second]);
        }
        len[p] = mxLen;
        for(auto it = tr[p].ch.begin(); it != tr[p].ch.end(); it++) {
            if(len[it -> second] == mxLen) {
                top[p] = top[it -> second];
                break;
            }
        }
        u = fa[u];
    }
}

void del(string& s, int si) {
    int u = 0;
    for(int i = 0; i < s.size(); i++) {
        int c = mat[s[i]];
        u = tr[u].ch[c];
    }

    sets[u].erase(si);
    bool ok = false;
    for(auto it = tr[u].ch.begin(); it != tr[u].ch.end(); it++) {
        if(top[it -> second] != -1) {
            ok = true;
        }
    }
    if(!ok) {
        if(sets[u].size()) {
            auto it = sets[u].begin();
            top[u] = *it;
            len[u] = mp[*it].size();
        } else {
            top[u] = -1;
            len[u] = 0;
        }
    }

    while(u != 0) {
        int p = fa[u], mxLen = 0;
        for(auto it = tr[p].ch.begin(); it != tr[p].ch.end(); it++) {
            mxLen = max(mxLen, len[it -> second]);
        }
        
        if(mxLen == 0) {
            if(sets[p].size() > 0) {
                auto it = sets[p].begin();
                top[p] = *it;
                len[p] = mp[*it].size();
            } else {
                top[p] = -1;
                len[p] = 0;
            }
        } else {
            len[p] = mxLen;
            for(auto it = tr[p].ch.begin(); it != tr[p].ch.end(); it++) {
                if(len[it -> second] == mxLen) {
                    top[p] = top[it -> second];
                    break;
                }
            }
        }
        u = fa[u];
    }
}


void init() {
    memset(fa, -1, sizeof fa);
    memset(top, -1, sizeof top);
    memset(len, 0, sizeof len);
    int pos = 0;
    for(int i = 0; i < 256; i++) {
        if(i >= 33 && i <= 126) {
            mat[i] = pos++;
        }
    }
}


void solve() {
    init();

    int n;
    cin >> n;
    string t = "";
    int u = 0, ti = 0;
    for(int i = 0; i < n; i++) {
        string op;
        cin >> op;
        if(op == "add") {
            int si; string s;
            cin >> si >> s;
            mp[si] = s;
            add(s, si);
        } else if(op == "delete") {
            int si;
            cin >> si;
            string s = mp[si];
            mp.erase(si);
            del(s, si);
        } else if(op == "append") {
            string s; cin >> s;
            t += s;
        } else if(op == "backspace") {
            int k;
            cin >> k;
            k = min(k, (int)(t.size()));
            while(k--) {
                if(ti == t.size()) {
                    u = fa[u];
                    ti--;
                }
                t.pop_back();
            }
        }
        
        //adjust
        while(u != 0 && top[u] == -1) {
            u = fa[u];
            ti--;
        }
        while(ti != t.size()) {
            int c = mat[t[ti]];
            if(tr[u].ch.find(c) != tr[u].ch.end() && top[tr[u].ch[c]] != -1) {
                u = tr[u].ch[c];
                ti++;
            } else {
                break;
            }
        }
        //cout << "gg " << i << "  " << ti << "  |" << t << endl;
        if(ti != t.size()) {
            cout << -1 << endl;
        } else {
            cout << top[u] << endl;
        }
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
