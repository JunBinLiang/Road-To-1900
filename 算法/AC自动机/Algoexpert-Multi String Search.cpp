#include <vector>
using namespace std;

struct AcAutomation {
    int tr[1010][256];
    int ne[1010], mp[1010];
    bool vis[1010];
    int id = 1;
    void init() {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        memset(mp, -1, sizeof mp);
        memset(vis, 0, sizeof vis);
        id = 1;
    }

    void add(string& s, int index) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i];
            if(tr[u][c] == 0) tr[u][c] = id++;
            u = tr[u][c];
        }
        mp[u] = index;
    }
  
    void build() {
        queue<int> q;
        for(int i = 0; i < 256; i++) {
            if(tr[0][i] != 0) {
                q.push(tr[0][i]);
            }
        }
        while(q.size() > 0) {
            int u = q.front(); q.pop();
            for(int i = 0; i < 256; i++) {
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

vector<bool> multiStringSearch(string s, vector<string> a) {
  // Write your code here.
  ac.init();
  for(int i = 0; i < a.size(); i++) {
    ac.add(a[i], i);
  }
  ac.build();
  vector<bool> ans(a.size());
  for(int i = 0, u = 0; i < s.size(); i++) {
    u = ac.tr[u][s[i]];
    int j = u;
    while(j && !ac.vis[j]) {
      if(ac.mp[j] != -1) {
        ans[ac.mp[j]] = true;
      }
      ac.vis[j] = true;
      j = ac.ne[j];
    }
  }
  return ans;
}
