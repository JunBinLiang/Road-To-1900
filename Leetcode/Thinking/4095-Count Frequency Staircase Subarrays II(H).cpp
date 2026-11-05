class Solution {
public:
    int countStaircase(vector<int>& a) {
        int n = a.size();
        map<int, vector<int>> mp;
        vector<int> pos(n);
        for(int i = 0; i < n; i++) {
            mp[a[i]].push_back(i);
            pos[i] = mp[a[i]].size() - 1;
        }

        vector<int> nxt(n, -1); // next distinct number
        vector<int> stk;
        for(int i = 0; i < n; i++) {
            while(stk.size() > 0 && a[i] != a[stk.back()]) {
                int index = stk.back();
                stk.pop_back();
                nxt[index] = i;
            }
            stk.push_back(i);
        }

        int ans = 0;
        for(int i = 0; i < n; i++) {
            // start from index i to extend
            ans++;
            int cur = i;
            
            int cut = n;
            int index = pos[i];
            if(index + 1 < mp[a[i]].size()) {
                cut = mp[a[i]][index + 1];
            }

            int cnt = 2;
            int tot = 1;
            int end = i;
            while(true) {
                tot += cnt;
                int nextUniqueIndex = nxt[cur];
                cur = nextUniqueIndex;
                if(nextUniqueIndex == -1) break;
                int x = a[nextUniqueIndex];
                vector<int>& vec = mp[x];
                int index = pos[nextUniqueIndex];
                if(index + cnt - 1 < vec.size()) {
                    int last = vec[index + cnt - 1];
                    if(last > cut) break;
                    if(index + cnt < vec.size()) {
                        cut = min(cut, vec[index + cnt]);
                    }
                    end = max(end, last);
                    if(i + tot - 1 == end) {
                        ans++;
                    }
                } else {
                    break;
                }
                cnt++;
            }
        }

        return ans;
    }
};
