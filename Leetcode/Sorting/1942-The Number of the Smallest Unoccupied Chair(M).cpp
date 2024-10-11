class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        vector<vector<int>> a;
        for(int i = 0; i < times.size(); i++) {
            a.push_back({times[i][0], times[i][1], i});
        }
        
        set<int> s;
        for(int i = 0; i <= times.size(); i++) {
            s.insert(i);
        }
        
        sort(a.begin(), a.end());
        priority_queue<pair<int, int>> pq;
        for(int i = 0; i < a.size(); i++) {
            int t1 = a[i][0], t2 = a[i][1], j = a[i][2];
            while(pq.size() > 0 && -pq.top().first <= t1) {
                pair<int, int> p = pq.top(); pq.pop();
                s.insert(p.second);
            }
            int ava = *(s.begin());
            if(targetFriend == j) {
                return ava;
            }
            s.erase(ava);
            pq.push({-t2, ava});
        }
        return -1;
    }
};
