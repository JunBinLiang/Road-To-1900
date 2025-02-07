class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& q) {
        vector<int> ans;
        map<int, int> mp1, mp2;
        for(int i = 0; i < q.size(); i++) {
            int j = q[i][0], c = q[i][1];
            if(mp1.find(j) == mp1.end()) {
                mp1[j] = c;
                mp2[c]++;
            } else {
                int oldc = mp1[j];
                mp1[j] = c;
                mp2[oldc]--;
                if(mp2[oldc] == 0) mp2.erase(oldc);
                mp2[c]++;
            }
            ans.push_back(mp2.size());
        }
        return ans;
    }
};
