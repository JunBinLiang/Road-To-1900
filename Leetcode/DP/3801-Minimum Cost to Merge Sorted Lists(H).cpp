class Solution {
public:
    long long minMergeCost(vector<vector<int>>& a) {
        int n = a.size();
        vector<int> med((1 << n) + 1), len((1 << n) + 1);
        for(int st = 0; st < (1 << n); st++) {
            med[st] = getMed(a, st);
            len[st] = getLen(a, st);
        }

        //do dp
        const long long INF = 1e16;
        vector<long long> dp(1 << n, INF);
        dp[0] = 0;
        for(int st = 1; st < (1 << n); st++) {
            if(bitcount(st) == 1) {
                dp[st] = 0;
                continue;
            }
            for(int subst = 1; subst <= st; subst++) {
                if((st & subst) == subst && (st | subst) == st) { //it is submask
                    int other = st ^ subst;
                    dp[st] = min(dp[st], dp[subst] + dp[other] + abs(med[subst] - med[other]) + len[subst] + len[other]);
                }
            }
        }
        return dp.back();
    }

    int bitcount(int n) {
        int cnt = 0;
        for(int i = 0; i < 13; i++) {
            if(n & (1 << i)) cnt++;
        }
        return cnt;
    }

    int getLen(vector<vector<int>>& a, int st) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(st & (1 << i)) {
                ans += a[i].size();
            }
        }
        return ans;
    }

    int getMed(vector<vector<int>>& a, int st) {
        int len = 0;
        for(int i = 0; i < a.size(); i++) {
            if(st & (1 << i)) {
                len += a[i].size();
            }
        }
        //find the kth
        int k = (len + 1) / 2;
        int l = -1e9, r = 1e9 + 10, ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int cnt = 0;
            for(int i = 0; i < a.size(); i++) {
                if(st & (1 << i)) {
                    cnt += find(a[i], mid);
                }
            }
            if(cnt >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return ans;
    }

    int find(vector<int>& a, int k) { //how many element <= k
        int l = 0, r = a.size() - 1;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[mid] <= k) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return ans + 1;
    }
};
