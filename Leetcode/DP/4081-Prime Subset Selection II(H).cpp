const int N = 1020;
bool initDone = false;
bool is[N];
vector<int> p; // size 184

bool dp[N][200][30];

void init() {
    if(initDone) return;
    initDone = true;
    memset(is, 0, sizeof is);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        p.push_back(i);
        for(int j = i; j < N; j += i) {
            is[j] = true;
        }
    }    
}

//first 25 prime number sum >= 1000
class Solution {
public:
    vector<int> maxPrimeSubset(int n, int s) {
        if(s == 1) {
            return {};
        }
        init();
        
        int sz = 0;
        int cur = 0;
        for(int x : p) {
            cur += x;
            sz++;
            if(cur > s) break;
        }

        vector<int> newp;
        for(int x : p) {
            if(x <= n) newp.push_back(x);
        }

        //reset
        for(int i = 0; i <= s + 2; i++) {
            for(int j = 0; j <= newp.size() + 2; j++) {
                for(int k = 0; k <= sz + 2; k++) {
                    dp[i][j][k] = false;
                }
            } 
        }


        dp[0][newp.size()][0] = true;
        for(int i = newp.size() - 1; i >= 0; i--) { //200
            int x = newp[i];
            for(int j = x; j <= s; j++) { //1000
                for(int cnt = 1; cnt <= sz + 1; cnt++) { //25
                    if(dp[j - x][i + 1][cnt - 1]) {
                        dp[j][i][cnt] = true;
                    }
                }
            }

            for(int j = 0; j <= s; j++) {
                for(int cnt = 0; cnt <= sz + 1; cnt++) {
                    dp[j][i][cnt] |= dp[j][i + 1][cnt];
                }
            }
        }

        int mxs = -1, mncnt = -1;

        for(int sum = s; sum >= 2 && mxs == -1; sum--) {
            for(int cnt = 0; cnt <= sz + 1; cnt++) {
                if(dp[sum][0][cnt]) {
                    mxs = sum;
                    mncnt = cnt;
                    break;
                }
            }
        }

        vector<int> ans;
        int cursum = 0;
        for(int i = 0; i < newp.size(); i++) {
            int x = newp[i];
            //if take
            if(mncnt > 0) {
                if(dp[mxs - (cursum + x)][i + 1][mncnt - 1]) {
                    cursum += x;
                    mncnt -= 1;
                    ans.push_back(x);
                }
            }
        }
        return ans;
    }
};
