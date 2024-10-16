//Fenwick Tree
const int FENWICK_SIZE = 100000 + 100;
struct Fenwick {
  int tree[FENWICK_SIZE];
  int sz;
  void init(int n) {
    sz = n;
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < sz){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i > 0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;
