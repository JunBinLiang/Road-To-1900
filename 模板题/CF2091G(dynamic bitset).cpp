#include <bits/stdc++.h>
#include <tr2/dynamic_bitset>
using namespace std;
using namespace tr2;
void solve()
{
    int s, k;
    cin >> s >> k;
    if (s >= k * k)
        return cout << (s % k ? max(1, k - 2) : k) << '\n', void();
    vector<dynamic_bitset<>> f(k + 1);
    for (int i = 0; i <= k; i++)
        f[i].resize(s + 1);
    for (int i = 0; i <= s; i += k)
        f[k][i] = 1;
    for (int i = k; i >= 2; i--)
    {
        if (f[i][s])
            return cout << i << '\n', void();
        if (k - i & 1)
        {
            for (int j = 0; j <= s; j += i - 1)
                f[i - 1] |= (f[i] <<= (i - 1));
        }
        else
        {
            for (int j = 0; j <= s; j += i - 1)
                f[i - 1] |= (f[i] >>= (i - 1));
        }
        // cout << i - 1 << '\n';
        // for (int j = 0; j <= s; j++)
        //     cout << f[i - 1][j] << ' ';
        // cout << '\n';
    }
    cout << 1 << '\n';
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
