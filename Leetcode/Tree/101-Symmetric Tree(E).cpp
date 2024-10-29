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
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q1, q2;
        q1.push(root);
        q2.push(root);
        
        while(q1.size() && q2.size()) {
            TreeNode* node1 = q1.front(); q1.pop();
            TreeNode* node2 = q2.front(); q2.pop();
            if(node1 -> val != node2 -> val) return false;
            
            if(node1 -> left) {
                if(node2 -> right == NULL) return false;
                q1.push(node1 -> left);
                q2.push(node2 -> right);
            } else {
                if(node2 -> right) return false;
            }
            
            if(node1 -> right) {
                if(node2 -> left == NULL) return false;
                q1.push(node1 -> right);
                q2.push(node2 -> left);
            } else {
                if(node2 -> left) return false;
            }
        }
        
        return q1.size() == 0 && q2.size() == 0;
    }
};
