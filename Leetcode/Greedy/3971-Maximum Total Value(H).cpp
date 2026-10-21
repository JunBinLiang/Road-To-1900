const int MOD = 1e9 + 7;
class Solution {
public:
    int maxTotalValue(vector<int>& a, vector<int>& b, int t) {
        int n = a.size();
        int mx = *max_element(a.begin(), a.end());
        vector<int> ori(a.begin(), a.end());

        int l = 0, r = mx;
        int cut = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            long long tot = 0;
            for(int i = 0; i < n; i++) {
                if(a[i] < mid) { //not taken
                    continue;
                }
                tot += ((a[i] - mid) / b[i]) + 1;
            }
            if(tot >= t) {
                cut = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if(cut == -1) {
            long long ans = 0;
            for(int i = 0; i < n; i++) {
                int time = a[i] / b[i];
                int end = a[i], start = a[i] - b[i] * time;
                ans += ((start + end + 0ll) * (time + 1) / 2);
                ans %= MOD;
            }
            return ans;
        }

        long long ans = 0;
        int cnt = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for(int i = 0; i < a.size(); i++) {
            int time = (a[i] - cut) / b[i]; 
            time = max(time, 0);
            int end = a[i], start = a[i] - time * b[i];
            ans += (end + start + 0ll) * (time + 1) / 2;
            ans %= MOD;
            cnt += (time + 1);
            a[i] -= (time * b[i]);
            pq.push({a[i], i});
        }

        //optimization
        while(cnt > t) {
            pair<int, int> p = pq.top();
            pq.pop();
            ans -= p.first;
            if(ans < 0) ans += MOD;
            ans %= MOD;
            if(p.first + b[p.second] <= ori[p.second]) {
                p.first += b[p.second];
                pq.push(p);
            }
            cnt--;
        }

        
        if(cnt < t) {
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
            for(int i = 0; i < n && cnt <  t; i++) {
                cnt++;
                ans += a[i];
            }
        }
        return ans;
    }
};
