class Solution {
public:
    int maximumAND(vector<int>& nums, int k, int m) {
        int ans = 0;
        vector<int> select, candidate;
        candidate = nums;

        for (int i = 30; i >= 0; i--) {
            cout << "____________________" << endl;
            vector<pair<int, int>> a;
            for(int x : select) a.push_back({x, 1});
            for(int x : candidate) a.push_back({x, 0});

            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
            long long need = 0;
            int more = m - select.size();
            int cantake = 0, moretake = 0;
            for(auto& p : a) {
                int x = p.first, type = p.second;
                if(type == 1) { //always take
                    if(x & (1 << i)) {
                        
                    } else {
                        need += ((1 << i) - x);
                    }
                } else {
                    if(x & (1 << i)) {
                        cantake++;
                    } else {
                        if(cantake + moretake < m - select.size()) {
                            moretake++;
                            need += ((1 << i) - x);
                        }
                    }
                }
            }

            if(need <= k) { // perform
                cout << "can " << cantake << endl;
                ans += (1 << i);
                k -= need;
                vector<int> news, newc;
                
                if(cantake >= (m - select.size())) {
                    for(int& x : select) {
                        if(x & (1 << i)) x -= (1 << i);
                        else x = 0;
                    }
                    for(int & x : candidate) {
                        if(x & (1 << i)) {
                            newc.push_back(x - (1 << i));
                        }
                    }
                    candidate = newc;
                    continue;
                }

                for(int& x : select) {
                    if(x & (1 << i)) x -= (1 << i);
                    else x = 0;
                }
                int tottake = cantake + moretake;
                for(auto &p : a) {
                    if(p.second == 1) continue;
                    if(tottake == 0) continue;
                    tottake--;
                    int x = p.first;
                    if(x & (1 << i)) x ^= (1 << i);
                    else x = 0;
                    select.push_back(x);
                }
            } else { //do nothing
                del(select, i);
                del(candidate, i);
            }
        }

        return ans;
    }

    void del(vector<int>& a, int i) {
        for (int& x : a) {
            if (x & (1 << i)) {
                x ^= (1 << i);
            }
        }
    }
};
