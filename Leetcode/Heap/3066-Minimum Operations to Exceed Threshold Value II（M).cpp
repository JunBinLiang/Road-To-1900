class Solution {
public:
    int minOperations(vector<int>& a, int k) {
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for(int x : a) pq.push(x);
        int ans = 0;
        while(pq.size() > 1 && pq.top() < k) {
            long long x = pq.top(); pq.pop();
            long long y = pq.top(); pq.pop();
            pq.push(x * 2 + y);
            ans++;
        }
        return ans;
    }
};
