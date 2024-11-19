#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct Complex
{
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
};

namespace FFT {
    const int N = 1e6 + 10;
    const double PI = acos(-1);
    int rev[N], bit, tot;
    Complex a[N], b[N];
    int n, m;
    
    void fft(Complex a[], int inv)
    {
        for (int i = 0; i < tot; i ++ )
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int mid = 1; mid < tot; mid <<= 1)
        {
            auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
            for (int i = 0; i < tot; i += mid * 2)
            {
                auto wk = Complex({1, 0});
                for (int j = 0; j < mid; j ++, wk = wk * w1)
                {
                    auto x = a[i + j], y = wk * a[i + j + mid];
                    a[i + j] = x + y, a[i + j + mid] = x - y;
                }
            }
        }
    }

    void solve(vector<Complex>& v1, vector<Complex>& v2) {
        n = v1.size() - 1;
        m = v2.size() - 1;
        tot = 0; bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        for(int i = 0; i < tot; i++) a[i] = {0, 0}, b[i] = {0, 0};
        for(int i = 0; i <= n; i++) a[i] = v1[i];
        for(int i = 0; i <= m; i++) b[i] = v2[i];
        fft(a, 1), fft(b, 1); 
        for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        fft(a, -1); 
        
        vector<int> coe;
        for (int i = 0; i <= n + m; i ++ ) {
            coe.push_back((int)(a[i].x / tot + 0.5));
        }
        
        int add = 0;
        vector<int> ans;
        for(int i = coe.size() - 1; i >= 0; i--) {
            int x = (coe[i] + add) % 10;
            add = (coe[i] + add) / 10;
            ans.push_back(x);
        }
        if(add) ans.push_back(add);
        reverse(ans.begin(), ans.end());
        for(int x : ans) cout << x;
    }
}

void solve() {
    vector<Complex> a, b;
    string s, t;
    cin >> s >> t;
    for(int i = 0; i < s.size(); i++) {
        a.push_back({s[i] - '0', 0});
    }
    for(int i = 0; i < t.size(); i++) {
        b.push_back({t[i] - '0', 0});
    }
    
    FFT :: solve(a, b);
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

