bool comp(vector<int>& p1, vector<int>& p2) {
    return p1[0] < p2[0];
}

class Solution {
public:
    long long maxEarnings(vector<vector<int>>& a) {
        int n = a.size();
        sort(a.begin(), a.end(), comp);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        long long ans = 0;
        set<long long> dp;
        vector<long long> record(n);

        for(int i = 0; i < n; i++) {
            int s1 = a[i][0], e1 = a[i][1], w1 = a[i][2];
            while(pq.size() && pq.top().first <= s1) {
                pair<int, int> p = pq.top();
                pq.pop();
                int index = p.second;
                int s2 = a[index][0], e2 = a[index][1], w2 = a[index][2];
                dp.insert(record[index] - e2);
            }

            if(dp.size() == 0) { //single
                ans = max(ans, w1 + 0ll);
                record[i] = w1;
            } else {
                auto it = dp.end();
                it--;
                long long pval = *it;
                long long cval = w1 + s1 + pval;
                ans = max(ans, cval);
                record[i] = cval;
            }
            pq.push({e1, i});
        }
        return ans;
    }
};
