class Solution {
public:
    long long countMagicalPairs(string s) {
        int n = s.size();
        long long ans = 0;
        vector<vector<int>> p(26);
        for(int i = 0; i < n; i++) {
            int d = s[i] - 'a';
            p[d].push_back(i);
        }

        vector<vector<int>> s1(n), s2(n); 

        vector<int> p1(26, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 26; j++) {
                vector<int>& pos = p[j];
                while(p1[j] < pos.size() && pos[p1[j]] < i) p1[j]++;
                if(p1[j] < pos.size() && pos[p1[j]] >= i) {
                    s1[i].push_back(pos[p1[j]]);
                }
            }
        }

        vector<int> p2(26, n - 1);
        for(int i = 0; i < 26; i++) {
            p2[i] = p[i].size() - 1;
        }

        for(int i = n - 1; i >= 0; i--) {
            for(int j = 0; j < 26; j++) {
                vector<int>& pos = p[j];
                while(p2[j] >= 0 && pos[p2[j]] > i) p2[j]--;
                if(p2[j] >= 0 && pos[p2[j]] <= i) {
                    s2[i].push_back(pos[p2[j]]);
                } 
            }
        }

        for(int i = 1; i < n; i++) {
            int l = i - 1, r = i;
            vector<int>& L = s2[i - 1];
            vector<int>& R = s1[i];
            sort(L.begin(), L.end());
            sort(R.begin(), R.end());
            int p1 = L.size() - 1, p2 = 0;
            while(p1 >= 0 && p2 < R.size()) {
                int idx1 = L[p1], idx2 = R[p2];
                int lcnt = l - idx1, rcnt = idx2 - r;
                ans += (lcnt + 0ll) * rcnt;
                l = idx1;
                r = idx2;
                p1--;
                p2++;
            }

            int idx1 = -1, idx2 = n;
            if(p1 >= 0) idx1 = L[p1];
            if(p2 < R.size()) idx2 = R[p2];
            int lcnt = l - idx1, rcnt = idx2 - r;
            ans += (lcnt + 0ll) * rcnt;
        }
        return ans;
    }
};
