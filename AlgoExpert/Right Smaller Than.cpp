using namespace std;

vector<int> ans;
vector<pair<int, int>> mergesort(vector<pair<int, int>>& a, int l, int r) {
  if(l == r) {
    return {a[l]};
  }
  int mid = l + (r - l) / 2;
  vector<pair<int, int>> b = mergesort(a, l, mid);
  vector<pair<int, int>> c = mergesort(a, mid + 1, r);

  int i = 0, j = 0;
  vector<pair<int, int>> d;
  unordered_map<int, int> mp;
  while(i < b.size() && j < c.size()) {
    if(b[i].first < c[j].first) {
      ans[b[i].second] += j;
      ans[b[i].second] -= mp[b[i].first];
      d.push_back(b[i]);
      i++;
    } else if(c[j].first < b[i].first) {
      mp[c[j].first]++;
      d.push_back(c[j]);
      j++;
    } else {
      ans[b[i].second] += j;
      ans[b[i].second] -= mp[b[i].first];
      d.push_back(b[i]);
      i++;
    }
  }
  while(i < b.size()) {
    ans[b[i].second] += j;
    ans[b[i].second] -= mp[b[i].first];
    d.push_back(b[i]);
    i++;
  }
  while(j < c.size()) {
    d.push_back(c[j]);
    j++;
  }
  return d;
}

vector<int> rightSmallerThan(vector<int> a) {
  // Write your code here.
  int n = a.size();
  if(n == 0) {
    return {};
  }
  vector<pair<int, int>> b;
  for(int i = 0; i < n; i++) {
    b.push_back({a[i], i});
  }
  ans = vector<int>(n);
  mergesort(b, 0, n - 1);
  return ans;
}
