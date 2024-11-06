struct Node {
    Node* childs[26];
    vector<string> a;
    
    void add(string s) {
        a.push_back(s);
        sort(a.begin(), a.end());
        while(a.size() > 3) a.pop_back();
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Node* root = new Node();
        for(string& product : products) {
            Node* u = root;
            for(int i = 0; i < product.size(); i++) {
                int c = product[i] - 'a';
                if(u -> childs[c] == NULL) {
                    u -> childs[c] = new Node();
                }
                u = u -> childs[c];
                u -> add(product);
            }
        }
        
        vector<vector<string>> ans(searchWord.size());
        Node* u = root;
        for(int i = 0; i < searchWord.size(); i++) {
            int c = searchWord[i] - 'a';
            u = u -> childs[c];
            if(u == NULL) break;
            ans[i] = vector<string>(u -> a.begin(), u -> a.end());
        }
        return ans;
    }
};
