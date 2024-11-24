//2:15 - 2:18
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& a) {
        int n = a.size();
        long long s = 0;
        int cnt = 0;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(a[i][j] < 0) {
                    cnt++;
                }
                s += abs(a[i][j]);
                pq.push(abs(a[i][j]));
            }
        }
        
        if(cnt % 2 == 0) {
            return s;
        } else {
            return s - pq.top() * 2;
        }
    }
};
