/*
Change Binary Tree to double linkedlist as in order traversal
*/
#include <vector>
using namespace std;

// This is the class of the input root. Do not edit it.
class BinaryTree {
 public:
  int value;
  BinaryTree* left = nullptr;
  BinaryTree* right = nullptr;

  BinaryTree(int value);
};
//In order Traversal

pair<BinaryTree*, BinaryTree*> dfs(BinaryTree* u) {

  if(u -> left == NULL && u -> right == NULL) {
    return {u, u};
  } else if(u -> left == NULL) {
    BinaryTree* right = u -> right;
    u -> right = NULL;
    pair<BinaryTree*, BinaryTree*> p = dfs(right);
    u -> right = p.first;
    return {u, p.second};
  } else if(u -> right == NULL) {
    BinaryTree* left = u -> left;
    u -> left = NULL;
    pair<BinaryTree*, BinaryTree*> p = dfs(left);
    p.second -> right = u;
    return {p.first, u};
  } else {
     BinaryTree* left = u -> left;
     u -> left = NULL;
     BinaryTree* right = u -> right;
     u -> right = NULL;
     pair<BinaryTree*, BinaryTree*> p1 = dfs(left);
     pair<BinaryTree*, BinaryTree*> p2 = dfs(right);
     p1.second -> right = u;
     u -> right = p2.first;
     return {p1.first, p2.second};
  }
}

BinaryTree* flattenBinaryTree(BinaryTree* root) {
  // Write your code here.
  pair<BinaryTree*, BinaryTree*> p = dfs(root);
  BinaryTree* u = p.first;
  while(u) {
    BinaryTree* nxt = u -> right;
    if(nxt) nxt -> left = u;
    u = nxt;
  }
  return p.first;
}
