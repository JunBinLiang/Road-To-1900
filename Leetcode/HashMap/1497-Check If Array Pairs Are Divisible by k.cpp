class Solution {
public:
    bool canArrange(vector<int>& a, int k) {
        map<int, int> f;
        for(int x : a) {
            f[(x % k + k) % k]++;
        }
        
        for(auto it = f.begin(); it != f.end(); it++) {
            int v = it -> first, cnt = it -> second;
            if((v + v) % k == 0 && cnt % 2 == 1) {
                return false;
            }
            if(cnt != f[(k - v) % k]) {
                return false;
            }
        }
        return true;
    }
};
