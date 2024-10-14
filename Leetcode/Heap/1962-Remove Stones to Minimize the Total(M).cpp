class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> pq;
        for(int x : piles) pq.push(x);
        
        while(k--) {
            int t = pq.top();
            pq.pop();
            t -= (t / 2);
            pq.push(t);
        }
        
        int ans = 0;
        while(pq.size() > 0) ans += pq.top(), pq.pop();
        return ans;
    }
};
