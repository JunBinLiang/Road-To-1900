/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        dfs(s, root);
        return s;
    }
    
    void dfs(string& s, TreeNode* root) {
        if(root == NULL) {
            s += "#,";
            return;
        }
        s += to_string(root -> val);
        s += ",";
        dfs(s, root -> left);
        dfs(s, root -> right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> vec = parse(data);
        if(vec.size() == 1) {
            return NULL;
        }
        
        TreeNode* root = new TreeNode(toint(vec[0]));
        vector<pair<TreeNode*, int>> stk;
        stk.push_back({root, 0});
        for(int i = 1; i < vec.size(); i++) {
            if(vec[i][0] == '#') {
                while(stk.size()) {
                    stk.back().second++;
                    if(stk.back().second == 2) {
                        stk.pop_back();
                    } else {
                        break;
                    }
                }
            } else {
                TreeNode* node = new TreeNode(toint(vec[i]));
                if(stk.back().second == 0) {
                    stk.back().first -> left = node;
                } else {
                    stk.back().first -> right = node;
                }
                stk.push_back({node, 0});
            }
        }
        return root;
    }
    
    int toint(string s) {
        if(s[0] == '-') return -toint(s.substr(1, s.size() - 1));
        int n = 0;
        for(char c : s) n = n * 10 + c - '0';
        return n;
    }
    
    vector<string> parse(string& data) {
        vector<string> ans;
        for(int i = 0; i < data.size(); i++) {
            int j = i;
            string s = "";
            while(j < data.size() && data[j] != ',') {
                s += data[j];
                j++;
            }
            ans.push_back(s);
            i = j;
        }
        return ans;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
