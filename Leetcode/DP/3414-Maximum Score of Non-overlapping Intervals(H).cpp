struct T {
    int l, r, w, i;
    bool operator<(const T& other) {
        return l < other.l;
    }
};

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& a) {
        int n = a.size();
        vector<T> A;
        for(int i = 0; i < n; i++) {
            A.push_back({a[i][0], a[i][1], a[i][2], i});
        }
        
        sort(A.begin(), A.end());
        vector<vector<long long>> dp(n, vector<long long>(5, -1));
        vector<vector<long long>> pdp(n, vector<long long>(5, -1));
        vector<vector<long long>> nxt(n, vector<long long>(5, -1));
        vector<vector<long long>> best(n, vector<long long>(5, -1));
        
        for(int i = n - 1; i >= 0; i--) {
            dp[i][1] = A[i].w;
            pdp[i][1] = A[i].w;
            best[i][1] = i;
            nxt[i][1] = -1;
            
            int l = i + 1, r = n - 1;
            int p = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(A[mid].l > A[i].r) {
                    p = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            
            if(p != -1) {
                for(int j = 2; j <= 4; j++) {
                    if(pdp[p][j - 1] != -1) {
                        dp[i][j] = pdp[p][j - 1] + A[i].w;
                        pdp[i][j] = dp[i][j];
                        nxt[i][j] = best[p][j - 1];
                        best[i][j] = i;
                    }
                }    
            }
            
            if(i + 1 < n) {
                for(int j = 1; j <= 4; j++) {
                    if(pdp[i + 1][j] == -1) continue;
                    if(pdp[i + 1][j] >= pdp[i][j]) {
                        if(pdp[i + 1][j] > pdp[i][j]) {
                            pdp[i][j] = pdp[i + 1][j];
                            best[i][j] = best[i + 1][j];
                        } else {
                            if(A[best[i + 1][j]].i < A[best[i][j]].i) {
                                best[i][j] = best[i + 1][j];
                            }
                        }
                    }
                }
            }
        }
        
        long long mx = -1;
        for(int i = 1; i <= 4; i++) {
            mx = max(mx, pdp[0][i]);
        }
        
        vector<int> ans = {n, n, n, n};
        for(int i = 1; i <= 4; i++) {
            vector<int> b;
            if(pdp[0][i] == mx) {
                int index = best[0][i];
                int j = i;
                while(b.size() != i) {
                    b.push_back(A[index].i);
                    index = nxt[index][j];
                    j--;
                }
            }
            sort(b.begin(), b.end());
            if(comp(ans, b)) {
                ans = b;
            }
        }
        return ans;
    }
    
    bool comp(vector<int>& a, vector<int>& b) {
        for(int i = 0; i < min(a.size(), b.size()); i++) {
            if(b[i] < a[i]) {
                return true;
            }
            else if(b[i] > a[i]) {
                return false;
            }
        }
        return false;
    }
};
