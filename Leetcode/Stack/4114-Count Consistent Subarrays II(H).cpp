class Solution {
public:
    long long countConsistent(vector<int>& a) {
        int n = a.size();
        vector<int> L(n, -1), R(n, n);
        vector<int> stk;
        for(int i = 0; i < n; i++) {
            while(stk.size() > 0 && a[i] < a[stk.back()]) {
                int j = stk.back();
                stk.pop_back();
                R[j] = i;
            }
            stk.push_back(i);
        }

        stk.clear();
        for(int i = n - 1; i >= 0; i--) {
            while(stk.size() > 0 && a[i] <= a[stk.back()]) {
                int j = stk.back();
                stk.pop_back();
                L[j] = i;
            }
            stk.push_back(i);
        }

        vector<vector<int>> p(21);
        for(int i = 0; i < n; i++) {
            int x = a[i];
            for(int j = 0; j < 21; j++) {
                if(x & (1 << j)) {
                    
                } else {
                    p[j].push_back(i);  //absent
                }
            }
        }

        long long ans = 0;
        for(int i = 0; i < n; i++) {
            int l = L[i] + 1, r = R[i] - 1;
            int x = a[i];
            int lcut = l, rcut = r;
            for(int j = 0; j < 21; j++) {
                if(x & (1 << j)) {
                    pair<int, int> pos = find(p[j], i);
                    if(pos.first != -1 && pos.first + 1 >= lcut && pos.first + 1 <= i) {
                        lcut = max(lcut, pos.first + 1);
                    }
                    if(pos.second != -1 && pos.second - 1 <= rcut && pos.second - 1 >= i) {
                        rcut = min(rcut, pos.second - 1);
                    }
                }
            }
            ans += ((i - lcut + 1ll) * (rcut - i + 1));
        }
        return ans;
    }

    pair<int, int> find(vector<int>& p, int bound) {
        int l = 0, r = p.size() - 1;
        int ans1 = -1, ans2 = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(p[mid] + 1 <= bound) {
                ans1 = p[mid];
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        l = 0; r = p.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(p[mid] - 1 >= bound) {
                ans2 = p[mid];
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return {ans1, ans2};
    }
};
