struct CartesianTree {
    vector<int> ls, rs;
    int build(vector<int>& a) { //用stack 维护树的右链
        int n = a.size();
        ls = vector<int>(n, -1);
        rs = vector<int>(n, -1);
        vector<int> stk;
        
        for(int i = 0; i < n; i++) {
            int top = -1;
            while(stk.size() > 0 && a[stk.back()] > a[i]) {
                top = stk.back();
                stk.pop_back();
            }
            if(stk.size() > 0){
                rs[stk.back()] = i;
            }
            if(top != -1){
                ls[i] = top;
            }
            stk.push_back(i);
        }
        
        while(stk.size() > 1) stk.pop_back();
        int root = stk.back();
        return root;
    }
} tr;

int ans = 0;
int dfs(vector<int>& a, int u) {
    int sz = 1;
    if(tr.ls[u] != -1) {
        sz += dfs(a, tr.ls[u]);
    }
    if(tr.rs[u] != -1) {
        sz += dfs(a, tr.rs[u]);
    }
    ans = max(ans, a[u] * sz);
    return sz;
}

class Solution {
public:
    int largestRectangleArea(vector<int>& a) {
        int n = a.size();
        int root = tr.build(a);
        ans = 0;
        dfs(a, root);
        return ans;
    }
};
