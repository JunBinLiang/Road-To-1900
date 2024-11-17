bool comp(pair<long long, long long>& p1, pair<long long, long long>& p2) {
    return p1.second < p2.second;
}

class Solution {
public:
    int minDifference(vector<int>& a) {
        int n = a.size();
        vector<int> b;
        for(int i = 0; i < n; i++) {
            if(a[i] != -1) {
                b.push_back(i);
            }
        }
        
        if(b.size() == 0) {
            return 0;
        }
        
        int l = 0, r = 2e9, ans = -1;
        for(int i = 1; i < n; i++) {
            if(a[i] != -1 && a[i - 1] != -1) {
                l = max(l, abs(a[i] - a[i - 1]));
            }
        }
        
        if(b.size() == n) {
            return l; //no -1
        }
        
        while(l <= r) {
            long long mid = l + (r - l) / 2;
            vector<pair<long long, long long>> c, d;
            bool two = false;
            bool ok = true;
            for(int i = 1; i < b.size(); i++) {
                if(b[i] - b[i - 1] == 1) continue;
                if(b[i] - b[i - 1] == 2) {
                    pair<long long, long long> p1 = {a[b[i]] - mid, a[b[i]] + mid};
                    pair<long long, long long> p2 = {a[b[i - 1]] - mid, a[b[i - 1]] + mid};
                    pair<long long, long long> in = inter(p1, p2);
                    if(in.first == -1000000000000000000) ok = false;
                    c.push_back(in);
                } else {
                    pair<long long, long long> p1 = {a[b[i]] - mid, a[b[i]] + mid};
                    pair<long long, long long> p2 = {a[b[i - 1]] - mid, a[b[i - 1]] + mid};
                    c.push_back(p1);
                    c.push_back(p2);
                }
            }
            
            if(b[0] != 0) {
                c.push_back({a[b[0]] - mid, a[b[0]] + mid});
            }
            if(b.size() > 0 && b.back() != n - 1) {
                c.push_back({a[b.back()] - mid, a[b.back()] + mid});
            }
            
            if(!ok) {
                l = mid + 1;
                continue;
            }
            
            sort(c.begin(), c.end(), comp);
            long long first = c[0].second;
            for(int i = 1; i < b.size(); i++) {
                if(b[i] - b[i - 1] == 1) continue;
                if(b[i] - b[i - 1] == 2) {
                    pair<long long, long long> p1 = {a[b[i]] - mid, a[b[i]] + mid};
                    pair<long long, long long> p2 = {a[b[i - 1]] - mid, a[b[i - 1]] + mid};
                    pair<long long, long long> in = inter(p1, p2);
                    if(!inside(in, first)) {
                        d.push_back(in);
                    }
                    
                } else {
                    pair<long long, long long> p1 = {a[b[i]] - mid, a[b[i]] + mid};
                    pair<long long, long long> p2 = {a[b[i - 1]] - mid, a[b[i - 1]] + mid};
                    if(!inside(p1, first) && !inside(p2, first)) {
                        d.push_back(p1);
                        d.push_back(p2);
                    } else if(!inside(p1, first)) {
                        two = true;
                        d.push_back(p1);
                    } else if(!inside(p2, first)) {
                        two = true;
                        d.push_back(p2);
                    }
                }
            }
            
            if(b[0] != 0) {
                pair<long long, long long> p = {a[b[0]] - mid, a[b[0]] + mid};
                if(!inside(p, first)) d.push_back(p);
            }
            if(b.size() > 0 && b.back() != n - 1) {
                pair<long long, long long> p = {a[b.back()] - mid, a[b.back()] + mid};
                if(!inside(p, first)) d.push_back(p);
            }
            
            sort(d.begin(), d.end(), comp);
            long long second = -1;
            if(d.size() > 0) {
                second = d[0].second;
                if(two) second = min(second, first + mid);
                for(int i = 0; i < d.size(); i++) {
                    if(!inside(d[i], second)) {
                        ok = false;
                    }
                }
            }
            
            /*cout << "bin: " << mid << "     |" << first <<" "  << second <<"    " << two << endl;
            for(auto p : c) cout << p.first << "  " << p.second << endl;
            cout << "_________________" << endl;
            for(auto p : d) cout << p.first << "  " << p.second << endl;
            cout << endl;*/
            
            if(ok) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
            
        }
        return ans;
    }
    
    pair<long long, long long> inter(pair<long long, long long>& p1, pair<long long, long long>& p2) {
        if(p1.first > p2.first) swap(p1, p2);
        if(p2.first > p1.second) return {-1000000000000000000, -100000000000000000};
        return {max(p1.first, p2.first), min(p1.second, p2.second)};
    }
    
    bool inside(pair<long long, long long>& p, long long x) {
        return p.first <= x && x <= p.second;
    }
};
