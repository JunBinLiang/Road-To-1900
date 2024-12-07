struct AcAutomation {
    int tr[10010 * 55][26];
    int ne[10010 * 55], cnt[10010 * 55];
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

    void add(string& s) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if(tr[u][c] == 0) tr[u][c] = id++;
            u = tr[u][c];
        }
        cnt[u]++;
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
                    q.push(c);
                }
            }
        }
    }
} ac;
