class Solution {
public:
    int maximumSum(vector<int>& a) {
        int n = a.size();
        map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[get(a[i])].push_back(a[i]);
        }
        
        int ans = -1;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            vector<int> vec = it -> second;
            sort(vec.begin(), vec.end());
            if(vec.size() > 1) {
                ans = max(ans, vec.back() + vec[vec.size() - 2]);
            }
        }
        return ans;
    }
    int get(int x) {
        int s = 0;
        while(x) {
            s += (x % 10);
            x /= 10;
        }
        return s;
    }
};
