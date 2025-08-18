class Solution {
public:
    bool judgePoint24(vector<int>& a) {
        vector<int> c = {0, 1, 2, 3};
        do {
            vector<int> vec;
            for(int i = 0; i < 4; i++) {
                vec.push_back(a[c[i]]);
            }
            vector<double> b = dfs(vec, 0, vec.size() - 1);
            for(double x : b) {
                if(abs(x - 24) <= 0.00005) {
                    return true;
                }
            }
        } while (next_permutation(c.begin(), c.end()));
        return false;
    }

    vector<double> dfs(vector<int>& a, int l, int r) {
        if(l == r) {
            return {a[l] + 0.0};
        }

        vector<double> ans;
        for(int i = l; i < r; i++) {
            vector<double> L = dfs(a, l, i);
            vector<double> R = dfs(a, i + 1, r);
            for(double x : L) {
                for(double y : R) {
                    ans.push_back(x + y);
                    ans.push_back(x * y);
                    ans.push_back(x - y);
                    ans.push_back(x / y);
                }
            }
        }
        return ans;
    }
};
