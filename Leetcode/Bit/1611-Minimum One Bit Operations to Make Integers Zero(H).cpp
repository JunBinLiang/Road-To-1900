class Solution {
public:
    long long p[31];
    int minimumOneBitOperations(int n) {
        p[0] = 2;
        for(int i = 1; i < 30; i++) {
            p[i] = p[i - 1] * 2;
        }
        return dfs(n);
    }
    
    int cal(int n) {
        if(n == 0) return 1;
        int bit = -1;
        for(int i = 30; i >= 0; i--) {
            if(n & (1 << i)) {
                bit = i; //highest bit
                break;
            }
        }
        int o = n ^ (1 << bit);
        return (1 << bit) + ((1 << bit) - cal(o) + 1);
    }
    
    int dfs(int n) {
        if(n == 0) {
            return 0;
        }
        if(n == 1) {
            return 1;
        }
        int bit = -1;
        for(int i = 30; i >= 0; i--) {
            if(n & (1 << i)) {
                bit = i; //highest bit
                break;
            }
        }
        int o = n ^ (1 << bit);
        return 1 + dfs(1 << (bit - 1)) + (p[bit - 1] - cal(o));
    }
};

/*
0000
0001
0010
0011
0100
0101
0110
0111

1000
1001
1010
1011
1100
1101
1110
1111

1XXXXXXX -> ... -> 11000000 -> 1000000 -> ... -> 0


00000
00001

00011
00010

00110
00111
00101
00100

01100
01101
01111
01110
01010
01011
01001
01000

*/
