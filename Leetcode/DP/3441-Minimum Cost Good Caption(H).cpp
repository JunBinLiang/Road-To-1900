const int N = 50000 + 10, INF = 1e9;
int dp[N][26];
int p[26][N], R[26][N], Rindex[26][N], to[N][26];

int get(int i, int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[i][r];
    return p[i][r] - p[i][l - 1];
}

class Solution {
public:
    string minCostGoodCaption(string s) {
        if(s.size() < 3) {
            return "";
        }
        
        int n = s.size();
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j < 26; j++) {
                dp[i][j] = INF;
            }
        }
        
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j <= n; j++) {
                p[i][j] = 0;
                R[i][j] = INF;
            }
        }
        
        for(char c2 = 'a'; c2 <= 'z'; c2++) {
            for(int i = 0; i < n; i++) {
                p[c2 - 'a'][i] = f(s[i], c2);
                if(i) {
                    p[c2 - 'a'][i] += p[c2 - 'a'][i - 1];
                }
            }
        }
        
        for(int i = n - 3; i >= 0; i--) {
            if(i + 3 <= n - 3) {
                int index = i + 3;
                int mn = INF;
                int c = -1;
                for(int j = 0; j < 26; j++) {
                    if(dp[index][j] < mn) {
                        mn = dp[index][j];
                        c = j;
                    }
                }
                
                for(int j = 0; j < 26; j++) {
                    R[j][index] = mn + get(j, 0, index - 1);
                    Rindex[j][index] = index;
                    if(R[j][index + 1] <= R[j][index]) {
                        if(R[j][index + 1] < R[j][index]) {
                            R[j][index] = min(R[j][index], R[j][index + 1]);
                            Rindex[j][index] = Rindex[j][index + 1];
                        } else {
                            if(c >= j) {
                                Rindex[j][index] = Rindex[j][index + 1];
                            }   
                        }
                    }
                }
            }            
            
            for(int j = 0; j < 26; j++) {
                dp[i][j] = get(j, i, n - 1);
                to[i][j] = n;
                if(R[j][i + 3] - get(j, 0, i - 1) <= dp[i][j]) {
                    if(R[j][i + 3] - get(j, 0, i - 1) < dp[i][j])
                    dp[i][j] = R[j][i + 3] - get(j, 0, i - 1);
                    to[i][j] = Rindex[j][i + 3];
                }
            }
            
        }
        
        int w = INF;
        for(int i = 0; i < 26; i++) {
            w = min(w, dp[0][i]);
        }
        
        /*for(int i = 0; i < n; i++) {
            for(int j = 0; j < 26; j++) {
                cout << dp[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 26; j++) {
                cout << to[i][j] << "  ";
            }
            cout << endl;
        }
        
        cout << w << endl;*/
       
        //construct answer
        string ans = "";
        while(ans.size() != n) {
            for(int c = 0; c < 26; c++) {
                if(dp[ans.size()][c] == w) {
                    int j = to[ans.size()][c];
                    int cur = ans.size();
                    while(cur < j) {
                        char c1 = c + 'a';
                        ans += c1;
                        w -= f(s[cur], c1);
                        cur++;
                    }
                    break;
                }
            }
        }
        return ans;
    }
    
    int f(char c1, char c2) {
        int d1 = c1 - 'a';
        int d2 = c2 - 'a';
        return abs(d1 - d2);
    }
};
