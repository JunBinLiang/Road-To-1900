/*
Given BST, 2 nodes are swapped, repair to the original BST
*/

using namespace std;

// This is an input class. Do not edit.
class BST {
 public:
  int value;
  BST* left = nullptr;
  BST* right = nullptr;

  BST(int value) { this->value = value; }
};

BST* repairBst(BST* root) {
  // Write your code here.
  if(root == NULL) return root;
  BST* ans = root;
  BST* node1 = NULL;
  BST* node2 = NULL;

  vector<BST*> stk;
  while(root) {
    stk.push_back(root);
    root = root -> left;
  }

  int p = -1;
  while(stk.size()) {
    BST* u = stk.back(); stk.pop_back();
    BST* cur = u;
    bool bad = false;
    if(p != -1 && u -> value < p) {
      bad = true;
    }
    p = u -> value;
    int curval = u -> value;
    u = u -> right;
    while(u) {
      stk.push_back(u);
      u = u -> left;
    }
    if(stk.size() && curval > stk.back() -> value) {
      bad = true;
    }
    if(bad) {
      if(node1 == NULL) node1 = cur;
      else node2 = cur;
    }
  }
  
  swap(node1 -> value, node2 -> value);
  return ans;
}
