#include <bits/stdc++.h>
using i64 = long long;
constexpr int V = 1e6 + 10;

std::array<int, V> mu, comp;
std::vector<int> primes;

void solve() {
    int n, m = 0;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<int> mul(m+1), deg(n), mp(m+1);
    for (int i = 0; i < n; ++i) {
        mp[a[i]]++;
    }
    for (int j = 1; j <= m; ++j) {
        for (int x = j; x <= m; x += j) {
            mul[j] += mp[x];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j == 0) {
                deg[i] += mu[j] * mul[j];
                if (j * j < a[i]) {
                    deg[i] += mu[a[i] / j] * mul[a[i] / j];
                }
            }
        }
        if (a[i] == 1) --deg[i];
    }
    std::array<int, 4> ans;
    int u = 0, v = 0, mind = INT32_MAX;
    for (int i = 1; i < n; ++i) {
        if (deg[i] > deg[u]) {
            u = i;
        }
    }
    if (!deg[u]) {
        std::cout << "0\n";
        return;
    }
    deg[u] = 0;
    for (int i = 0; i < n; ++i) {
        if (i == u) continue;
        if (std::gcd(a[i], a[u]) == 1) {
            --deg[i];
            if (mind > deg[i]) {
                mind = deg[i];
                v = i;
            }
        }
    }
    ans[0] = u;
    ans[1] = v;
    deg[v] = 0;
    for (int i = 0; i < n; ++i) {
        if (i == u || i == v) continue;
        if (std::gcd(a[i], a[v]) == 1) {
            --deg[i];
        }
    }
    u = 0;
    for (int i = 1; i < n; ++i) {
        if (deg[i] > deg[u]) {
            u = i;
        }
    }
    if (!deg[u]) {
        std::cout << "0\n";
        return;
    }
    v = -1;
    for (int i = 0; i < n; ++i) {
        if (i == u || !deg[i]) continue;
        if (std::gcd(a[i], a[u]) == 1) {
            v = i;
            break;
        }
    }
    assert(v >= 0);
    ans[2] = u; ans[3] = v;
    for (int i = 0; i < 4; ++i) {
        std::cout << ans[i] + 1 << " \n"[i == 3];
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    std::cin >> T;
    mu[1] = 1;
    for (int i = 2; i < V; ++i) {
        if (!comp[i]) {
            primes.emplace_back(i);
            mu[i] = -1;
        }
        for (auto p: primes) {
            int q = i * p;
            if (q >= V) break;
            comp[q] = true;
            if (i % p == 0) {
                mu[q] = 0;
                break;
            } else {
                mu[q] = -mu[i];
            }
        }
    }
    while (T--) solve();
    return 0;
}
