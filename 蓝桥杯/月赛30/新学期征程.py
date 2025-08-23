MOD = 998244353

def count_ways(n: int) -> int:
    a = (n + 1) // 2   # ceil(n/2)
    b = n // 2         # floor(n/2)
    ab = a * b
    val = pow(ab, 4, MOD) * (n * n - 4) % MOD
    inv2 = (MOD + 1) // 2   # 2 的逆元 (998244353 是质数)
    return val * inv2 % MOD

# 读入
t = int(input().strip())  # 测试用例数
for _ in range(t):
    n = int(input().strip())
    print(count_ways(n))
