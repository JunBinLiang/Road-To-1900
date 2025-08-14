using namespace std;

int majorityElement(vector<int> a) {
  // Write your code here.
  int n = a.size();
  int cur = a[0], t = 1;
  for(int i = 1; i < n; i++) {
      if(a[i] == cur) t++;
      else {
        if(t == 0) {
          cur = a[i];
          t = 1;
        } else {
          t--;
        }
      }
  }
  return cur;
}
