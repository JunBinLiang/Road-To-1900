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
    vector<int> postorderTraversal(TreeNode* root) {
        if(root == NULL) return {};
        vector<int> ans;
        vector<TreeNode*> stk;
        stk.push_back(root);
        
        while(stk.size()) {
            TreeNode* u = stk.back(); stk.pop_back();
            ans.push_back(u -> val);
            if(u -> left) stk.push_back(u -> left);
            if(u -> right) stk.push_back(u -> right);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
