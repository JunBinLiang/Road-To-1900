//任意模数多项式乘法
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

//https://blog.csdn.net/weixin_43346722/article/details/121155688?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-121155688-blog-135758423.235^v43^pc_blog_bottom_relevance_base1&spm=1001.2101.3001.4242.1&utm_relevant_index=3
struct Complex
{
    long double x, y;
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

namespace MTT {
    const int N = 1e6 + 10, lim = 32000;
    const long double PI = acos(-1);
    int rev[N], bit, tot;
    Complex p1[N], p2[N], q[N];
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

    void solve() {
        int n, m, MOD;
        cin >> n >> m >> MOD;
        for(int i = 0; i <= n; i++) {
            int x;
            cin >> x;
            p1[i] = {x / lim, x % lim};
            p2[i] = {x / lim, -x % lim};
        }

        for(int i = 0; i <= m; i++) {
            int x;
            cin >> x;
            q[i] = {x / lim, x % lim};
        }

        tot = 0; bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ ) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }

        /*
        (a1 * lim + b1) * (a2 * lim + b2) = a1 * a2 * lim * lim + b1 * b2 + (a1 * b2 + a2 * b1) * lim
         p1 = a1 + b1 * i
         p2 = a1 - b1 * i
         q = a2 + b2 * i
         p1 * q = a1 * a2 - b1 * b2 + (a1 * b2 + a2 * b1) * i
         p2 * q = a1 * a2 + b1 * b2 + (a1 * b2 - a2 * b1) * i
        */  
        fft(p1, 1); fft(p2, 1); fft(q, 1);
        for (int i = 0; i < tot; i++) q[i].x /= tot, q[i].y /= tot; //先除了后面就不用除
	      for (int i = 0; i < tot; i++) p1[i] = p1[i] * q[i], p2[i] = p2[i] * q[i];
	      fft(p1, -1); fft(p2, -1);
        for (int i = 0; i <= n + m; i++) {
            long long a1a2 = (long long) floor((p1[i].x + p2[i].x) / 2 + 0.5) % MOD;
            long long b1b2 = (long long) floor(p2[i].x + 0.5 - a1a2);
            b1b2 %= MOD;
            if(b1b2 < 0) b1b2 += MOD;
            long long a1b2 = (long long) floor((p1[i].y + p2[i].y) / 2 + 0.5) % MOD;
            long long a2b1 = (long long)floor(p1[i].y + 0.5 - a1b2);
            a2b1 %= MOD;
            if(a2b1 < 0) a2b1 += MOD;
            long long ans = (a1a2 * lim * lim % MOD) + (b1b2) + (a1b2 + a2b1) * lim % MOD;
            ans %= MOD;
            if(ans < 0) ans += MOD;
            cout << ans << " ";
        }
    }
}

void solve() {
    MTT :: solve();
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
