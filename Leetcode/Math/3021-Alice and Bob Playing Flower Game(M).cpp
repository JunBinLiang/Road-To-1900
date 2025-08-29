class Solution {
public:
    long long flowerGame(int n, int m) {
        return ((0ll + n) * m) - (n / 2ll) * (m / 2ll) - ((n + 1ll) / 2) * ((m + 1ll) / 2);
    }
};
