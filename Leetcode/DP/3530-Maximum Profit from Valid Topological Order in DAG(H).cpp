#include <bit>
const int N = 25;
int p[N]; //use bit to represent what nodes must be remove so it can start to process
class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        memset(p, 0, sizeof p);
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            p[v] |= (1 << u);
        }

        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for(int st = 0; st < (1 << n); st++) {
            for(int node = 0; node < n; node++) {
                if(st & (1 << node)) { //take that node
                    int count = __builtin_popcount(st);
                    int pbit = st ^ (1 << node);
                    int s = score[node] * count; 
                    //can i take this
                    if((pbit & p[node]) == p[node] && dp[pbit] != -1) {
                        dp[st] = max(dp[st], s + dp[pbit]);
                    }
                }
            }
        }
        return dp.back();        
    }
};
