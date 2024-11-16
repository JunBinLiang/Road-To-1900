//9:13
class Solution {
public:
    vector<int> resultsArray(vector<int>& a, int k) {
        int n = a.size();
        vector<int> ans;
        
        for(int i = 0; i < a.size(); i++) {
            a[i] -= i;
        }
        
        unordered_map<int, int> mp;
        for(int i = 0; i < n; i++) {
            mp[a[i]]++;
            if(i + 1 >= k) {
                if(mp.size() == 1) ans.push_back(a[i] + i);
                else ans.push_back(-1);
                mp[a[i - k + 1]]--;
                if(mp[a[i - k + 1]] == 0) {
                    mp.erase(a[i - k + 1]);
                }
            }
        }
        return ans;
    }
};
