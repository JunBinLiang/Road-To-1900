const int N = 1e5 + 10;
long long dp[N][2]; // (index, even or odd)

class Solution {
public:
    long long maxAlternatingSum(vector<int>& a) {
        int n = a.size();
        if(n == 1) {
            return a[0];
        }
        long long ans = -1e16;
        long long lo = 0, le = 0;

        for(int i = 0; i <= n; i++) {
            dp[i][0] = dp[i][1] = -1e16;
        }
        
        //cut prefix odd, cur prefix even
        long long pe = -1e16, po = -1e16;
        long long lmn1 = 0, lmn2 = 1e16;
    
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) le += a[i];
            else lo += a[i];
            long long os, es;
            if((i + 1) % 2 == 0) {
                //cut even
                es = le - lo - lmn1;
                //cut odd
                os = lo - le - lmn2;
                ans = max(ans, max(es, os));
            } else {
                //cut even
                os = le - lo - lmn1;
                //cut odd
                es = lo - le - lmn2;
                ans = max(ans, max(es, os));
            }

            if((i + 1) % 2 == 0)
                lmn1 = min(lmn1, le - lo);
            else
                lmn2 = min(lmn2, lo - le);

            if(i) {
                long long s1 = dp[i - 1][0] + a[i];
                long long s2 = dp[i - 1][1] - a[i];
                dp[i][0] = max(dp[i][0], s2);
                dp[i][1] = max(dp[i][1], s1);
            } else {
                dp[i][0] = 0;
            }

            //empty
            dp[i][0] = max(dp[i][0], pe);
            dp[i][1] = max(dp[i][1], po);
            
            if(i)
                ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
            pe = es;
            po = os;
        }
        return ans;
    }
};
