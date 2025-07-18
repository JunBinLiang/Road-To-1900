class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int k, vector<vector<int>>& q) {
        vector<pair<int, int>> a;
        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }
        sort(a.begin(), a.end());

        vector<vector<int>> f(n, vector<int>(19, -1));
        for(int i = 0; i < n; i++) {  
            int l = i + 1, r = n - 1;
            f[i][0] = i;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[mid].first <= a[i].first + k) {
                    f[i][0] = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            mp[a[i].first] = i;
        }

        for(int j = 1; j < 19; j++) {
            for(int i = 0; i < n; i++) {
                f[i][j] = f[f[i][j - 1]][j - 1];
            }
        }
        
        vector<int> ans;
        for(int i = 0; i < q.size(); i++) {
            int u = q[i][0], v = q[i][1];
            if(nums[u] > nums[v]) swap(u, v);
            if(u == v) {
                ans.push_back(0);
                continue;
            }
            if(nums[u] == nums[v]) {
                ans.push_back(1);
                continue;
            }
            int l = 1, r = n;
            int s = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                int L = mp[nums[u]], R = mp[nums[v]];
                for(int i = 0; i < 18; i++) {
                    if(mid & (1 << i)) {
                        L = f[L][i];
                    }
                }
                if(L >= R) {
                    s = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans.push_back(s);
        }
        return ans;
    }
};
