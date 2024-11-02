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
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == NULL) return {};
        vector<int> ans;
        vector<TreeNode*> stk;
        
        while(root) {
            stk.push_back(root);
            root = root -> left;
        }
        
        while(stk.size()) {
            TreeNode* u = stk.back(); stk.pop_back();
            ans.push_back(u -> val);
            u = u -> right;
            while(u) {
                stk.push_back(u);
                u = u -> left;
            }
        }
        return ans;
    }
};
