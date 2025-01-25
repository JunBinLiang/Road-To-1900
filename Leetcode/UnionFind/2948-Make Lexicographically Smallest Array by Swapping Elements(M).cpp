class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& a, int k) {
        int n = a.size();
        vector<pair<int, int>> b;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            b.push_back({a[i], i});
        }
        
        
        sort(b.begin(), b.end());
        for(int i = 0; i < n; i++) {
            int j = i + 1;
            vector<int> indexs;
            vector<int> vals;
            indexs.push_back(b[i].second);
            vals.push_back(b[i].first);
            while(j < n && b[j].first - b[j - 1].first <= k) {
                indexs.push_back(b[j].second);
                vals.push_back(b[j].first);
                j++;
            }
            sort(indexs.begin(), indexs.end());
            for(int x = 0; x < indexs.size(); x++) {
                ans[indexs[x]] = vals[x];
            }
            i = j - 1;
        }
        return ans;
    }
};
