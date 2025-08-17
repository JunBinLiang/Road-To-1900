class Solution {
public:
    int candy(vector<int>& a) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int j = i + 1;
            vector<int> b;
            bool add = true;
            while(j < n && a[j] != a[j - 1]) {
                if(a[j] > a[j - 1]) { // + 1
                    b.push_back(1);
                } else { // - 1
                    b.push_back(-1);
                }
                j++;
            }
            i = j - 1;
            ans += cal(b);
        }
        return ans;
    }

    int cal(vector<int>& a) {
        if(a.size() == 0 || a[0] == 0) {
            return 1;
        }
        int n = a.size();
        vector<int> b;
        for(int i = 0; i < n; i++) {
            int j = i;
            int cnt = 0;
            while(j < n && a[j] == a[i]) {
                j++;
                cnt++;
            }
            if(a[i] < 0) b.push_back(-cnt);
            else b.push_back(cnt);
            i = j - 1;
        }

        int s = 0;
        if(b[0] < 0 || b.size() == 1) {
            int t = abs(b[0]) + 1;
            s += ((1 + t) * t / 2);
        } else {
            int t = b[0] + 1;
            if(b.size() > 1 && b[0] < abs(b[1])) {
                s += ((t - 1) * t / 2);
                s += (abs(b[1]) + 1);
            } else {
                s += ((1 + t) * t / 2);
            }
        }
        for(int i = 1; i < b.size(); i++) {
            int t = abs(b[i]);
            if(b[i] < 0) {
                s += ((1 + t) * t / 2);
            } else {
                t++;
                if(i == b.size() - 1) {
                    s += ((1 + t) * t / 2);
                    s--;
                } else {
                    if(b[i] < abs(b[i + 1])) {
                        s += ((t - 1) * t / 2);
                        s += (abs(b[i + 1]) + 1);
                        s--;
                    } else {
                        s += ((1 + t) * t / 2);
                        s--;
                    }
                }
            }
        }
        return s;
    }
};
