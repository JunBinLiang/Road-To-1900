class Solution {
public:
    int maxEqualAdjacentPairs(vector<int>& a) {
        int n = a.size();
        int ans = 0, same = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] == a[i - 1]) {
                same++;
            }
        }

        map<pair<int, int>, int> mp;
        for(int i = 1; i < n; i++) {
            int mn = min(a[i], a[i - 1]);
            int mx = max(a[i], a[i - 1]);
            mp[{mn, mx}]++;
        }

        ans = max(ans, same);

        for(int i = 1; i < n; i++) {
            int x = a[i - 1], y = a[i];
            if(x == y) continue;
            int mn = min(x, y), mx = max(x, y);
            int cnt =  mp[{mn, mx}] + same;
            ans = max(ans, cnt);
        }

        return ans;
    }
};
