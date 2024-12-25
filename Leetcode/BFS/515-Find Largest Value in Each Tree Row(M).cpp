/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if(!root) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<int> ans;
        while(q.size()) {
            int sz = q.size();
            int mx = q.front() -> val;
            for(int i = 0; i < sz; i++) {
                TreeNode* u = q.front();
                mx = max(mx, u -> val);
                q.pop();
                if(u -> left) q.push(u -> left);
                if(u -> right) q.push(u -> right);
            }
            ans.push_back(mx);
        }
        return ans;
    }
};
