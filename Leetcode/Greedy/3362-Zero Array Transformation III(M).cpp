//3:48
class Solution {
public:
    int maxRemoval(vector<int>& a, vector<vector<int>>& q) {
        int n = a.size();
        int ans = 0;
        vector<int> line(n + 1);
        sort(q.begin(), q.end());
        
        int s = 0;
        int j = 0;
        priority_queue<int> pq;
        for(int i = 0; i < a.size(); i++) {
            s += line[i];

            while(j < q.size() && q[j][0] <= i) {
                pq.push(q[j][1]);
                j++;
            }
            
            while(pq.size() > 0 && s < a[i]) {
                int right = pq.top(); pq.pop();
                if(right >= i) {
                    s++;
                    line[right + 1]--;
                } else {
                    ans++;
                }
            }
            
            if(s < a[i]) {
                return -1;
            }
        }
        return ans + pq.size();
    }
};
