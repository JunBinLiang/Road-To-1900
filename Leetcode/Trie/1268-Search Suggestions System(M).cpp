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

bool yes = false;
void init() {
    if(yes) return;
    yes = true;
    tr.init();
}

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        init();
        for(string& s : products) tr.add(s);
        vector<vector<string>> ans(searchWord.size());
        int u = 0;
        for(int i = 0; i < searchWord.size() && u != -1; i++) {
            int c = searchWord[i] - 'a';
            u = tr.tr[u][c];
            if(u != -1) ans[i] = vector<string>(tr.a[u].begin(), tr.a[u].end());
        }
        tr.clear();
        return ans;
    }
};
