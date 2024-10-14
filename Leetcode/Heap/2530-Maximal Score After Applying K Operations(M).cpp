class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> pq;
        for(int x : nums) pq.push(x);
        long long ans = 0;
        while(pq.size() > 0 && k > 0) {
            int t = pq.top(); pq.pop();
            ans += t;
            if(t % 3 == 0 && t / 3) pq.push(t / 3);
            else if(t % 3 != 0 && t / 3 + 1) pq.push(t / 3 + 1);
            k--;
        }
        return ans;
    }
};
