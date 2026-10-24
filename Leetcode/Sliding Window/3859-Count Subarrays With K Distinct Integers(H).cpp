class Solution {
public:
    long long countSubarrays(vector<int>& a, int k, int m) {
        int n = a.size();
        long long ans = 0;
        map<int, int> mp1, mp2;
        map<int, queue<int>> qm;
        set<int> s;
        for(int r = 0, l = 0; r < n; r++) {
            mp1[a[r]]++;
            mp2[mp1[a[r]]]++;
            if(mp1[a[r]] != 1) {
                mp2[mp1[a[r]] - 1]--;
                if(mp2[mp1[a[r]] - 1] == 0) mp2.erase(mp1[a[r]] - 1);
            }
            qm[a[r]].push(r);
            s.insert(r);
            while(qm[a[r]].size() > m) {
                int t = qm[a[r]].front();
                qm[a[r]].pop();
                s.erase(t);
            }

            while(mp1.size() > k) {
                int x = a[l];
                mp2[mp1[x]]--;
                if(mp2[mp1[x]] == 0) mp2.erase(mp1[x]);
                
                mp1[x]--;
                if(mp1[x] == 0) mp1.erase(x);
                else mp2[mp1[x]]++;

                int t = qm[x].front();
                if(t == l) {
                    qm[x].pop();
                    if(qm[x].size() == 0) qm.erase(x);
                    s.erase(t);
                }                
                l++;
            }

            if(mp1.size() == k) {
                int smallest = mp2.begin() -> first;
                if(smallest >= m) {
                    int first = *(s.begin());
                    ans += (first - l + 1);
                }
            }
        }
        return ans;
    }
};
