class Solution {
public:
    long long minOperations(vector<int>& a, int m, int k) {
        int n = a.size();
        map<int, int> mp1, mp2;
        int sz1 = 0, sz2 = 0;
        long long s1 = 0, s2 = 0;
        vector<long long> changes(n);
        for(int i = 0; i < n; i++) {
            if(mp1.size() == 0) {
                add(mp1, a[i], sz1, s1);
            } else {
                auto it = mp1.end();
                it--;
                if(a[i] > it -> first) add(mp2, a[i], sz2, s2);
                else add(mp1, a[i], sz1, s1);
            }
            adjust(mp1, mp2, sz1, sz2, s1, s2);
            if(i + 1 >= m) {
                auto it = mp1.end();
                it--;
                int med = it -> first;
                changes[i] = ((med + 0ll) * sz1 - s1) + (s2 - ((med + 0ll) * sz2)); 
                bool ok = false;
                int l = i - m + 1;
                if(mp1.find(a[l]) != mp1.end()) {
                    ok = true;
                    del(mp1, a[l], sz1, s1);
                }
                if(!ok) {
                    del(mp2, a[l], sz2, s2);
                }
                adjust(mp1, mp2, sz1, sz2, s1, s2);
            }
        }

        //for(int x : changes) cout << x << " ";
        //cout << endl << endl;

        const long long INF = 1e16;
        vector<vector<long long>> dp(n, vector<long long>(k + 1, INF));
        for(int i = m - 1; i < n; i++) {
            dp[i][0] = 0;
            dp[i][1] = changes[i];
            for(int j = 1; j <= k; j++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                if(i - m >= 0) {
                    dp[i][j] = min(dp[i][j], changes[i] + dp[i - m][j - 1]);
                }
            }
        }

        long long ans = 1e16;
        for(int i = 0; i < n; i++) {
            ans = min(ans, dp[i][k]);
        }
        return ans;

    }

    void adjust(map<int, int>& mp1, map<int, int>& mp2, int& sz1, int& sz2, long long& s1, long long& s2) {
        while(sz1 > sz2 + 1) {
            auto it = mp1.end();
            it--;
            int k = it -> first;
            del(mp1, k, sz1, s1);
            add(mp2, k, sz2, s2);
        }

        while(sz2 + 1 > sz1) {
            auto it = mp2.begin();
            int k = it -> first;
            add(mp1, k, sz1, s1);
            del(mp2, k, sz2, s2);
        }
    }

    void add(map<int, int>& mp, int key, int& sz, long long& s) {
        mp[key]++;
        sz++;
        s += key;
    }

    void del(map<int, int>& mp, int key, int& sz, long long& s) {
        mp[key]--;
        if(mp[key] == 0) mp.erase(key);
        sz--;
        s -= key;
    }
};
