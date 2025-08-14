/*
题意 : reconstruct BST based on a given preorder traversal array input
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

BST* reconstructBst(vector<int> a) {
  if(a.size() == 0) {
    return nullptr;
  }
  // Write your code here.
  BST* root = new BST(a[0]);
  vector<int> left, right;
  for(int i = 1; i < a.size(); i++) {
    if(a[i] < a[0]) left.push_back(a[i]);
    else right.push_back(a[i]);
  }
  root -> left = reconstructBst(left);
  root -> right = reconstructBst(right);
  return root;
}
