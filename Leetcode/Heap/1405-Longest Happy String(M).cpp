class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if(a)
            pq.push({a, 'a'});
        if(b)
            pq.push({b, 'b'});
        if(c)
            pq.push({c, 'c'});
        
        vector<pair<int, char>> A;
        while(pq.size()) {
            pair<int, char> p1 = pq.top(); pq.pop();
            if(A.size() == 0 || A.back().second != p1.second) {
                A.push_back({1, p1.second});
                p1.first--;
            } else if(A.back().second == p1.second) {
                if(A.back().first == 2) {
                    if(pq.size() == 0) break;
                    else {
                        pair<int, char> p2 = pq.top(); pq.pop();
                        A.push_back({1, p2.second});
                        p2.first--;
                        if(p2.first) pq.push(p2);
                    }
                } else {
                    A.back().first++;
                    p1.first--;
                }
            }
            if(p1.first) pq.push(p1);
        }
        
        string ans = "";
        for(auto p : A) {
            for(int i = 0; i < p.first; i++) {
                ans += p.second;
            }
        }
        return ans;
    }
};
