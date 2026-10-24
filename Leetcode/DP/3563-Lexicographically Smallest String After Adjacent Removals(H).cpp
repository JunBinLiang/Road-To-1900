const int N = 255;
bool vis[N];
string small[N];
int dp[N][N];

class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
       
        for(int i = 0; i <= n; i++) {
            vis[i] = false;
            for(int j = 0; j <= n; j++) {
                dp[i][j] = -1;
            }
        }

        dfs(s, 0, s.size() - 1);
        string ans = find(s, 0);
        return ans;
    }

    string find(string& s, int l) { // 250
        int r = s.size() - 1;
        if(l > r) {
            return "";
        }
        
        if(dp[l][r] == 1) {
            vis[l] = true;
            small[l] = "";
            return "";
        }

        if(vis[l]) {
            return small[l];
        }

        // can not remove the whole string
        string ans = "#";

        vector<pair<char, int>> vec;
        for(int i = l; i <= r; i++) {
            vec.push_back({s[i], i});
        }
        sort(vec.begin(), vec.end());

        for(auto& p : vec) { //250
            char c = p.first;
            int i = p.second;
            if((i - 1 >= l && dp[l][i - 1] == 1) || (i == l)) {
                string t = s[i] + find(s, i + 1);
                if (ans == "#" || t < ans) {
                    ans = t;
                }
            }
        }

        vis[l] = true;
        string t = s[l] + find(s, l + 1);
        if(ans == "#") ans = t;
        else if(ans > t) ans = t;
        return small[l] = ans;
    }

    int dfs(string& s, int l, int r) {
        if(l > r) return 0;
        if(dp[l][r] != -1) {
            return dp[l][r];
        }

        if(l + 1 == r) {
            return dp[l][r] = ok(s[l], s[r]);
        }

        if(l == r) {
            return dp[l][r] = 0;
        }

        dp[l][r] = 0;
        if(ok(s[l], s[r]) == 1) {
            dp[l][r] |= dfs(s, l + 1, r - 1);
        }
        for(int mid = l; mid + 1 <= r; mid++) {
            int x = dfs(s, l, mid);
            int y = dfs(s, mid + 1, r);
            x &= y;
            dp[l][r] |= x;
        }
        return dp[l][r];
    }

    int ok(char c1, char c2) {
        if(c1 > c2) swap(c1, c2);
        if(c1 == 'a' && c2 == 'z') return 1;
        return c2 - c1 == 1 ? 1 : 0;
    }
};
