struct Trie {
    int tr[(100000 + 10)][26];
    vector<string> a[(100000 + 10) * 26]; 
    int id = 1;
    void init() {
        memset(tr, -1, sizeof tr);
    }
    
    void add(string& s) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if(tr[u][c] == -1) tr[u][c] = id++;
            u = tr[u][c];
            a[u].push_back(s);
            sort(a[u].begin(), a[u].end());
            while(a[u].size() > 3) a[u].pop_back();
        }
    }
    
    void clear() {
        for(int i = 0; i <= id; i++) {
            a[i].clear();
            for(int j = 0; j < 26; j++) {
                tr[i][j] = -1;
            }
        }
        id = 1;
    }
} tr;
