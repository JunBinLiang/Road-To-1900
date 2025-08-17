bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first == p2.first) {
        return p2.second < p1.second;
    }
    return p1.first < p2.first;
}

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& a) {
        vector<pair<int, int>> b;
        for(int i = 0; i < a.size(); i++) {
            int l = a[i][0], r = a[i][1], h = a[i][2];
            b.push_back({l, h});
            b.push_back({r, -h});
        }

        vector<vector<int>> ans;
        sort(b.begin(), b.end(), comp);
        map<int, int> mp;
        int pre = -1;
        for(int i = 0; i < b.size(); i++) {
            int x = b[i].first, h = b[i].second;
            if(h < 0) { //exist
                h = -h;
                mp[h]--;
                if(mp[h] == 0) {
                    mp.erase(h);
                }
            } else { //enter
                mp[h]++;
            }

            int y = 0;
            if(mp.size() == 0) {

            } else {
                auto it = mp.end(); 
                it--;
                y = it -> first;
            }
            if(pre != y) {
                ans.push_back({x, y});
            }
            pre = y;
        }
        return ans;
    }
};
