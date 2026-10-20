const int N = 1e5 + 10;
bool initDone = false;
vector<int> p[N + 10];
void init() {
    if(initDone) {
        return;
    }
    initDone = true;
    for(int i = 2; i < N; i++) {
        for(int j = i; j < N; j += i) {
            p[j].push_back(i);
        }
    }
}

int uf(vector<int>& f, int x) {
    if(f[x] == x) {
        return x;
    }
    return f[x] = uf(f, f[x]);
}


class Solution {
public:
    bool gcdSort(vector<int>& a) {
        init();
        int n = a.size();
        int mx = 0;
        for(int x : a) mx = max(mx, x);
        vector<int> f(mx + 2);
        for(int i = 0; i < f.size(); i++) {
            f[i] = i;
        }


        for(int i = 0; i < n; i++) {
            int x = a[i];
            int r1 = uf(f, x);
            for(int y : p[x]) {
                int r2 = uf(f, y);
                if(r1 != r2) {
                    //important, small -> large merge
                    f[r2] = r1;
                }
            }
        }

        map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) {
            int r = uf(f, a[i]);
            mp[r].push_back(a[i]);
        }

        for(auto it = mp.begin(); it != mp.end(); it++) {
            vector<int>& vec = it -> second;
            sort(vec.begin(), vec.end());
            reverse(vec.begin(), vec.end());
        }

        for(int i = 0; i < n; i++) {
            int r = uf(f, a[i]);
            a[i] = mp[r].back();
            mp[r].pop_back();
        }

        for(int i = 0; i < n - 1; i++) {
            if(a[i] > a[i + 1]) {
                return false;
            }
        }

        return true;
    }
};
