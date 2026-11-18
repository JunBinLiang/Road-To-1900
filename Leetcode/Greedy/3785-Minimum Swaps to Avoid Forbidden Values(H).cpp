class Solution {
public:
    int minSwaps(vector<int>& a, vector<int>& b) {
        int n = a.size();
        map<int, int> mp1, mp2, mp3;
        for(int i = 0; i < n; i++) {
            mp1[a[i]]++;
            mp2[b[i]]++;
            if(a[i] == b[i]) {
                mp3[a[i]]++;
            }
        }

        for(auto it = mp1.begin(); it != mp1.end(); it++) {
            int k = it -> first, v = it -> second;
            if(n - mp2[k] < v) {
                return -1;
            }
        }
        priority_queue<pair<int, int>> pq;
        for(auto it = mp3.begin(); it != mp3.end(); it++) {
            int k = it -> first, v = it -> second;
            pq.push({v, k});
        }

        int ans = 0;
        while(pq.size() > 1) {
            pair<int, int> p1 = pq.top(); pq.pop();
            pair<int, int> p2 = pq.top(); pq.pop();
            p1.first--;
            p2.first--;
            if(p1.first > 0) pq.push(p1);
            if(p2.first > 0) pq.push(p2);
            ans++;
        }
        if(pq.size() > 0) {
            ans += pq.top().first;
        }
        return ans;
    }
};
