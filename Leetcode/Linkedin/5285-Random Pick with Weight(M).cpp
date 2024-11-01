class Solution {
public:
    vector<int> p; 
    Solution(vector<int>& w) {
        p = vector<int>(w.size());
        for(int i = 0; i < w.size(); i++) {
            p[i] = w[i];
            if(i) p[i] += p[i - 1];
        }
    }
    
    int pickIndex() {
        int rnd = rand() % p.back() + 1;
        int l = 0, r = p.size() - 1;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int L = 1, R = p[mid];
            if(mid > 0) L = p[mid - 1] + 1;
            if(rnd < L) {
                r = mid - 1;
            } else {
                if(rnd > R) {
                    l = mid + 1;
                } else {
                    ans = mid;
                    break;
                }
            }
        }
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
