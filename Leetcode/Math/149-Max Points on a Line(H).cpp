class Solution {
public:
    int maxPoints(vector<vector<int>>& a) {
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            int x1 = a[i][0], y1 = a[i][1]; //fix point
            map<pair<int, int>, int> mp;
            for(int j = 0; j < a.size(); j++) {
                if(i == j) continue;
                int x2 = a[j][0], y2 = a[j][1];
                int up = y1 - y2, down = x1 - x2;
                int g = __gcd(up, down);
                mp[{up / g, down / g}]++;
                ans = max(ans, mp[{up / g, down / g}]);
            }
        }
        return ans + 1;
    }
};
