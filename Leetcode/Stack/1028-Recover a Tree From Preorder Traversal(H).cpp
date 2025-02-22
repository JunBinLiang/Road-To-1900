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
    TreeNode* recoverFromPreorder(string s) {
        int n = s.size();
        vector<pair<TreeNode*, int>> stk;
        TreeNode* root = new TreeNode();
        
        int i = 0;
        while(i < n && isd(s[i])) {
            root -> val = root -> val * 10 + s[i] - '0';
            i++;
        }
        stk.push_back({root, 0});
        
        for(; i < n; i++) {
            int val = 0;
            int j = i;
            
            int d = 0;
            while(j < n && !isd(s[j])) {
                d++;
                j++;
            }
            
            while(j < n && isd(s[j])) {
                val = val * 10 + s[j] - '0';
                j++;
            }
            
            TreeNode* node = new TreeNode(val);
            while(stk.size() > 0 && d != stk.back().second + 1) {
                stk.pop_back();
            }
            if(stk.back().first -> left == NULL) stk.back().first -> left = node;
            else stk.back().first -> right = node;
            stk.push_back({node, d});
            i = j - 1;
        }
        return root;
    }
    
    bool isd(char c) {
        return c >= '0' && c <= '9';
    }
};
