using ll = long long;
const int N = 1e5 + 10;
long long p[N], rs[N];
int r[N];
long long get(int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& a, int k) {
        int n = a.size();
        ll ans = 0;
        
        for(int i = 0; i < a.size(); i++) {
            p[i] = a[i];
            if(i) p[i] += p[i - 1];
        }
        
        for(int i = 0; i < n; i++) {
            r[i] = -1;
            rs[i] = 0;
        }
        
        vector<int> stk;
        for(int i = 0; i < n; i++) {
            while(stk.size() > 0 && a[i] > a[stk.back()]) {
                int index = stk.back();
                r[index] = i;
                rs[index] = (i - index + 0ll) * a[index] - get(index, i - 1);
                stk.pop_back();
            }
            stk.push_back(i);
        }
        
        while(stk.size() > 0) {
            int index = stk.back(); stk.pop_back();
            rs[index] = (n - index + 0ll) * a[index] - get(index, n - 1);
        }
        
        
        deque<int> dq;
        long long s = 0;
        int last = -1;
        for(int i = 0; i < n; i++) {
            if(dq.size() > 0 && a[i] > a[dq.back()]) {
                dq.push_back(i);
            } else {
                if(dq.size() == 0) {
                    dq.push_back(i);
                } else {
                    s += (a[dq.back()] - a[i]);
                }
            }
            
            
            while(dq.size() > 0 && s > k) {
                int j = dq.front();
                int first = dq.front(); dq.pop_front();
                if(dq.size() > 0) {
                    s -= rs[first];
                } else {
                    s -= (((a[first] + 0ll) * (i - first + 1)) - get(first, i));
                }
                //reconstruct
                vector<int> b;
                first++;
                while(true) {
                    if(dq.size() > 0) {
                        if(first == dq.front()) break;
                        s += rs[first];
                        b.push_back(first);
                        first = r[first];
                    } else {
                        if(first > i) break;
                        int nxt = r[first];
                        if(nxt == -1 || nxt > i) {
                            s += (((a[first] + 0ll) * (i - first + 1)) - get(first, i));
                            b.push_back(first);
                            break;
                        } else {
                            s += rs[first];
                            b.push_back(first);
                            first = nxt;
                            
                        }
                    }

                }
                reverse(b.begin(), b.end());
                for(int ind : b) dq.push_front(ind);
            }
            ans += (i - dq.front() + 1);
        }
        return ans;
    }
    
};
