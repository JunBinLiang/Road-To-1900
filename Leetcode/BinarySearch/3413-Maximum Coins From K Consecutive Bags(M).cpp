long long get(vector<long long>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];    
}

class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        map<int, int> mp;
        for(auto& vec : coins) {
            int l = vec[0], r = vec[1], w = vec[2];
            mp[l] += w;
            mp[r + 1] -= w;
        }
        
        long long s = 0;
        vector<pair<int, long long>> a;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            s += it -> second;
            a.push_back({it -> first, s});
        }
        
        vector<pair<int, long long>> b;
        for(int i = 0; i < a.size() - 1; i++) {
            int sz = a[i + 1].first - a[i].first;
            b.push_back({sz, a[i].second});
        }
        
        long long ans = 0;
        ans = max(ans, cal(b, k));
        reverse(b.begin(), b.end());
        ans = max(ans, cal(b, k));

        return ans;
    }
    
    long long cal(vector<pair<int, long long>>& b, int k) {
        vector<long long> p1(b.size()), p2(b.size());
        for(int i = 0; i < b.size(); i++) {
            p1[i] = b[i].first;
            p2[i] = (b[i].first * b[i].second);
            if(i) {
                p1[i] += p1[i - 1];
                p2[i] += p2[i - 1];
            }
        }
        
        long long ans = 0;
        
        for(int i = 0; i < b.size(); i++) {
            int l = i, r = b.size() - 1;
            int p = i - 1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(get(p1, i, mid) <= k) {
                    p = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            long long tot = 0;
            int K = k;
            if(p >= i) {
                tot += get(p2, i, p);
                K -= get(p1, i, p);
            }
            if(p + 1 < b.size()) {
                tot += (b[p + 1].second * min(K, b[p + 1].first));
            }
            ans = max(ans, tot);
        }
        return ans;
    }
};
