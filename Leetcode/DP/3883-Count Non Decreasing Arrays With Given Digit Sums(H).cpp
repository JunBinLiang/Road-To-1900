const int N = 51;
vector<int> e[N];
bool done = false;
void init() {
    if(done) {
        return;
    }
    done = true;
    for(int i = 0; i <= 5000; i++) {
        int x = i;
        int s = 0;
        while(x > 0) {
            int d = x % 10;
            x /= 10;
            s += d;
        }
        e[s].push_back(i);
    }
}

int dp[1010][5010];
int pdp[1010][5010];

class Solution {
public:
    int countArrays(vector<int>& a) {
        init();
        const int MOD = 1e9 + 7;
        
        int n = a.size();
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= 5000; j++) {
                pdp[i][j] = dp[i][j] = 0;
            }
        }

        for(int i = 0; i < n; i++) {
            for(int x : e[a[i]]) {
                if(i == 0) {
                    dp[i][x] = 1;
                } else {
                    dp[i][x] += pdp[i - 1][x];
                    dp[i][x] %= MOD;
                }
            }
            for(int j = 0; j <= 5000; j++) {
                pdp[i][j] = dp[i][j];
                if(j > 0) pdp[i][j] += pdp[i][j - 1];
                pdp[i][j] %= MOD;
            }
        }

        int ans = 0;
        for(int x : e[a[n - 1]]) {
            ans += dp[n - 1][x];
            ans %= MOD;
        }
        return ans;
    }
};
