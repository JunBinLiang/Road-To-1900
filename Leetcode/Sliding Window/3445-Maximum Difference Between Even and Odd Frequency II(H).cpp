class Solution {
public:
    int maxDifference(string s, int k) {
        int ans = -1000000000;
        int n = s.size();
        for(char c1 = '0'; c1 < '5'; c1++) {
            for(char c2 = '0'; c2 < '5'; c2++) {
                if(c1 == c2) continue;
                int s1 = 0, s2 = 0;
                queue<int> q[4];
                vector<pair<int, int>> a(n);
                int e[4];
                for(int i = 0; i < 4; i++) e[i] = -1000000000;
                for(int i = 0; i < s.size(); i++) {
                    if(s[i] == c1) s1++;
                    if(s[i] == c2) s2++;
                    int b1 = s1 % 2, b2 = s2 % 2;
                    if(i + 1 >= k && b1 == 1 && b2 == 0 && s2 > 0) ans = max(ans, s1 - s2);
                    int st = (b1) + b2 * 2;
                    
                    int rst = (b1 ^ 1) + (b2) * 2;
                    while(q[rst].size() > 0 && i - q[rst].front() >= k) {
                        int j = q[rst].front();
                        int x = a[j].first, y = a[j].second;
                        if(s1 == x || s2 == y) break;
                        q[rst].pop();
                        e[rst] = max(e[rst], -x + y);
                    }
                    
                    if(i + 1 >= k) {
                        if(b1 == 1 && b2 == 0 && s2 > 0) ans = max(ans, s1 - s2);
                        ans = max(ans, s1 - s2 + e[rst]);
                    }
                    
                    a[i] = {s1, s2};
                    q[st].push(i);
                }
            }
        }
        return ans;
    }
};
