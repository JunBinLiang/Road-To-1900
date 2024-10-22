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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> q;
        q.push(root);
        vector<long long> a;
        while(q.size()) {
            int sz = q.size();
            long long s = 0;
            for(int i = 0; i < sz; i++) {
                TreeNode* u = q.front(); q.pop();
                s += (u -> val);
                if(u -> left != NULL) q.push(u -> left);
                if(u -> right) q.push(u -> right);
            }
            a.push_back(s);
        }
        sort(a.begin(), a.end());
        return a.size() < k ? -1 : a[a.size() - k];
    }
};
