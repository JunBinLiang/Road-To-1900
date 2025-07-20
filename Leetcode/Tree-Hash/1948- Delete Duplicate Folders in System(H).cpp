const int N = 2e5 + 100;
map<string, int> tr[N];
map<unsigned long long, int> seen;
vector<vector<string>> ans;
unsigned long long ha[N];
string strs[N];
int id = 0;

const int BASE = 991;
unsigned long long po[N];
bool INIT = false;

void init() {
    if(INIT) return;
    INIT = true;
    po[0] = 1;
    for(int i = 1; i < N; i++) {
        po[i] = po[i - 1] * BASE;
    }
}

void reset() {
    for(int i = 0; i <= id; i++) tr[i].clear();
    id = 0;
}

void add(vector<string>& p) {
    int u = 0;
    for(int i = 0; i < p.size(); i++) {
        string& s = p[i];
        if(tr[u].find(s) == tr[u].end()) {
            tr[u][s] = ++id;
        }
        u = tr[u][s];
        strs[u] = s;
    }
}

unsigned long long f(string s) {
    unsigned long long h = 0;
    for(char& c : s) {
        h = h * BASE + (c - 'a' + 1);
    }
    return h;
}

pair<unsigned long long, int> dfs1(int u) {
    unsigned long long h = 0;
    int sz = 1;
    for(auto it = tr[u].begin(); it != tr[u].end(); it++) {
        string s = it -> first; 
        int v = it -> second;
        pair<unsigned long long, int> p = dfs1(v);
        h = h * po[p.second] + p.first;
        h = h * po[to_string(p.second).size()] + f(to_string(p.second));
        sz += p.second;
    }
    seen[h]++;
    ha[u] = h;
    h = h * po[strs[u].size()] + f(strs[u]);
    return {h, sz};
}

void dfs2(vector<string>& path, int u) {
    if(seen[ha[u]] > 1 && ha[u] != 0) {
        return;
    }
    
    if(strs[u].size() > 0) {
        path.push_back(strs[u]);
    }

    if(path.size() > 0) {
        ans.push_back(vector<string>(path.begin(), path.end()));
    }

    for(auto it = tr[u].begin(); it != tr[u].end(); it++) {
        string s = it -> first; 
        int v = it -> second;
        dfs2(path, v);
    }

    if(strs[u].size() > 0) {
        path.pop_back();
    }
}



class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& a) {
        reset();
        init();
        for(int i = 0; i < a.size(); i++) {
            add(a[i]);
        }
        seen.clear();
        ans.clear();
        
        dfs1(0);

        vector<string> path;
        dfs2(path, 0); 
        sort(ans.begin(), ans.end());
        return ans;
    }
};
