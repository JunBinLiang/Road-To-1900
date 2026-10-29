const int N = 1e5 + 10;
struct Node {
    int l, r, mn = 0, mx = 0;
} tr[N * 4];

void build(vector<int>& a, int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].mn = tr[u].mx = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid};
    tr[u * 2 + 2] = {mid + 1, r};
    build(a, u * 2 + 1);
    build(a, u * 2 + 2);
    tr[u].mn = min(tr[u * 2 + 1].mn, tr[u * 2 + 2].mn);
    tr[u].mx = max(tr[u * 2 + 1].mx, tr[u * 2 + 2].mx);
}

pair<int, int> q(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return {tr[u].mn, tr[u].mx};
    }
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        return q(u * 2 + 1, s, e);
    } else if(s >= mid + 1) {
        return q(u * 2 + 2, s, e);
    } else {
        pair<int, int> p1 = q(u * 2 + 1, s, mid);
        pair<int, int> p2 = q(u * 2 + 2, mid + 1, e);
        return {min(p1.first, p2.first), max(p1.second, p2.second)};
    }
}

class Solution {
public:
    int sortableIntegers(vector<int>& a) {
        int n = a.size();
        tr[0] = {0, n - 1};
        build(a, 0);
        vector<int> to(n); // maximum it can extend
        vector<vector<int>> vec;
        for(int i = 0; i < n; i++) {
            vector<int> v = {a[i]};
            int j = i + 1;
            while(j < n && a[j] >= a[j - 1]) {
                v.push_back(a[j]);
                j++;
            }
            vec.push_back(v);
            i = j - 1;
        }

        int index = 0;
        for(int i = 0; i < vec.size(); i++) {
            vector<int>& v = vec[i];
            for(int j = 0; j < v.size(); j++) {
                to[index] = index +  (v.size() - j - 1);
                if(i + 1 < vec.size()) {
                    int more = find(vec[i + 1], v[j]);
                    to[index] += (more + 1);
                } 
                index++;
            }
        }

        int ans = 0;
        for(int k = 1; k <= n; k++) {
            if(n % k != 0) continue;
            bool ok = true;
            int pmax = -1;
            for(int i = 0; i < n; i += k) {
                if(to[i] < i + k - 1) {
                    ok = false;
                    break;
                }
                pair<int, int> p = q(0, i, i + k - 1);
                if(p.first < pmax) {
                    ok = false;
                    break;
                }
                pmax = max(pmax, p.second);
            }
            if(ok) {
                ans += k;
            }
        }
        return ans;
    }

    int find(vector<int>& a, int x) {
        int ans = -1;
        int l = 0, r = a.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(a[mid] <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return ans;
    }

    void print(vector<int>& a) {
        for(int x : a) cout << x << " ";
        cout << endl;
    }
};
