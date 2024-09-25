const int N = 1010 * 1010;
int tr[N][26];
int cnt[N];
int id = 1;

void add(string& s) {
    int u = 0;
    for(int i = 0; i < s.size(); i++) {
        if(tr[u][s[i] - 'a'] == -1) {
            tr[u][s[i] - 'a'] = id++;
        }
        u = tr[u][s[i] - 'a'];
        cnt[u]++;
    }
}

int query(string& s) {
    int u = 0, ans = 0;
    for(int i = 0; i < s.size() && u != -1; i++) {
        u = tr[u][s[i] - 'a'];
        if(u != -1) {
            ans += cnt[u];
        }
    }
    return ans;  
}

class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        id = 1;
        memset(tr, -1, sizeof tr);
        memset(cnt, 0, sizeof cnt);
        for(string& s : words) {
            add(s);
        }
        
        vector<int> ans;
        for(string& s : words) {
            ans.push_back(query(s));
        }
        
        return ans;
    }
};
