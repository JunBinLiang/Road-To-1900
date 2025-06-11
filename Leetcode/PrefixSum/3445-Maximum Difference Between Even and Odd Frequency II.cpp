class Solution {
public:
    int maxDifference(string s, int k) {
        vector<pair<char, char>> comb;
        for(char c1 = '0'; c1 <= '4'; c1++) {
            for(char c2 = '0'; c2 <= '4'; c2++) {
                if(c1 != c2) comb.push_back({c1, c2});
            }
        }

        int ans = -1000000000;
        int n = s.size();
        for(auto& p : comb) {
            int cnt1 = 0, cnt2 = 0;
            vector<pair<int, int>> a;
            map<pair<int, int>, int> mp;
            for(int i = 0, j = 0; i < n; i++) {
                if(s[i] == p.first) {
                    cnt1++;
                } else if(s[i] == p.second) {
                    cnt2++;
                }
                int s1 = (cnt1 - cnt2);
                int b1 = cnt1 % 2, b2 = cnt2 % 2;
                a.push_back({cnt1, cnt2});

                while(i - j >= k) {
                    int bb1 = a[j].first % 2, bb2 = a[j].second % 2;
                    if(a[j].second == cnt2) break;
                    if(mp.find({bb1, bb2}) == mp.end()) {
                        mp[{bb1, bb2}] = a[j].first - a[j].second;
                    } else {
                        mp[{bb1, bb2}] = min(mp[{bb1, bb2}], a[j].first - a[j].second);
                    }
                    j++;
                }

                if(i + 1 >= k) {
                    if(b1 == 1 && b2 == 0 && cnt1 > 0 && cnt2 > 0) {
                        ans = max(ans, cnt1 - cnt2);
                    }
                }

                if(mp.find({b1 ^ 1, b2}) != mp.end()) {
                    ans = max(ans, (cnt1 - cnt2) - mp[{b1 ^ 1, b2}]);
                }
            }
        }
        return ans;
    }
};
