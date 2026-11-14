class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& a, vector<vector<int>>& queries) {
        int n = a.size();
        vector<int> to(n);
        vector<int> start; //starting point
        for(int i = 0; i < n; i++) {
            start.push_back(i);
            int j = i + 1;
            while(j < n && a[j] >= a[j - 1]) {
                j++;
            }
            int k = j - 1;
            int cnt = 1;
            while(k >= i) {
                to[k] = cnt++;
                k--;
            }
            i = j - 1;
        }

        vector<long long> p(n);
        for(int i = 0; i < n; i++) {
            p[i] = to[i];
            if(i) p[i] += p[i - 1];
        }

        vector<long long> ans;
        for(auto& q : queries) {
            int l = q[0], r = q[1];
            long long s = p[r];
            if(l) s -= p[l - 1];

            int index = find(start, r);
            long long mul = to[r] - 1;
            if(index < l) {
                s -= ((r - l + 1) * mul);
            } else {
                int sz = r - index + 1;
                s -= (sz * mul);
            }
            ans.push_back(s);
        }
        return ans;
    }

    int find(vector<int>& a, int bound) {
        int l = 0, r = a.size() - 1, ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[mid] <= bound) {
                ans = a[mid];
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
