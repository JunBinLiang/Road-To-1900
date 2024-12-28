int get(vector<int>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& a, int k) {
        int n = a.size();
        vector<int> p(n);
        for(int i = 0; i < n; i++) {
            p[i] = a[i];
            if(i) p[i] += p[i - 1];
        }
        
        vector<pair<int, int>> L(n), R(n);
        for(int i = 0; i < n; i++) {
            L[i] = {-1, -1};
            R[i] = {-1, -1};
        }
        for(int i = k - 1; i < n; i++) {
            int s = get(p, i - k + 1, i);
            L[i] = {s, i - k + 1};
            if(i) merge(L[i], L[i - 1]);
        }
        
        for(int i = n - k; i >= 0; i--) {
            int s = get(p, i, i + k - 1);
            R[i] = {s, i};
            if(i + 1 < n) merge(R[i], R[i + 1]);
        }
        
        vector<int> ans = {-1, -1, -1, -1};
        for(int i = k; i + 2 * k - 1 < n; i++) {
            int mid = get(p, i, i + k - 1);
            pair<int, int> p1 = L[i - 1], p2 = R[i + k];
            if(p1.first == -1 || p2.first == -1) continue;
            update(ans, mid + p1.first + p2.first, p1.second, i, p2.second);
        }
        return {ans[1], ans[2], ans[3]};
    }
    
    void merge(pair<int, int>& p1, pair<int, int>& p2) {
        if(p1.first <= p2.first) {
            if(p1.first < p2.first) {
                p1 = {p2.first, p2.second};
            } else {
                p1.second = min(p1.second, p2.second);
            }
        }
    }
    
    void update(vector<int>& ans, int sum, int i1, int i2, int i3) {
        if(sum >= ans[0]) {
            if(sum > ans[0]) {
                ans = {sum, i1, i2, i3};
            } else {
                vector<int> a = {-1, i1, i2, i3};
                for(int i = 1; i < a.size(); i++) {
                    if(a[i] == ans[i]) {
                        continue;
                    }
                    if(a[i] < ans[i]) {
                        ans = {sum, i1, i2, i3};
                        break;
                    } else {
                        break;
                    }
                }
            }
        }
    }
};
