using namespace std;

int get(vector<int>& a, int i) {
  if(i < 0) return -1;
  else if(i >= a.size()) return 1000000000;
  return a[i];
}

int find(vector<int>& a, vector<int>& b, int k) {
  int n = a.size(), m = b.size();
  int l = 0, r = min(n - 1, k - 1);
  int ans = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    int more = k - (mid + 1);
    if(get(b, more - 1) <= a[mid] && get(b, more) >= a[mid]) {
      return a[mid];
    } else if(get(b, more - 1) > a[mid]) {
      l = mid + 1;
    } else if(get(b, more - 1) <= a[mid] && get(b, more) <= a[mid]) {
      r = mid - 1;
    }
  }
  return find(b, a, k);
}

float medianOfTwoSortedArrays(vector<int> a, vector<int> b) {
  // Write your code here.
  if(a.size() > b.size()) {
    swap(a, b); 
  }
  int n = a.size(), m = b.size();
  if((n + m) % 2 == 1) {
    return find(a, b, (n + m + 1) / 2);
  } else {
    return (find(a, b, (n + m + 1) / 2) + find(a, b, (n + m + 1) / 2 + 1) + 0.0) / 2;
  }
}
