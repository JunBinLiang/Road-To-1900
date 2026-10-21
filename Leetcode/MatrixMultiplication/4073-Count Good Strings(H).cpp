const int MOD = 1e9 + 7;

struct Matrix {
    int n, m;
    vector<vector<long long>> mat;

    void init(int row, int col, int val = 0) {
        n = row;
        m = col;
        mat = vector<vector<long long>>(n, vector<long long>(m, val));
    }

    vector<vector<long long>> mul(const vector<vector<long long>>& other) {
        if (m != other.size()) {
            cout << "Matrix size mismatch" << endl;
            return {};
        }

        int p = other.size();
        int q = other[0].size();

        vector<vector<long long>> ans(n, vector<long long>(q, 0));
        for (int r = 0; r < n; r++) {
            for (int k = 0; k < m; k++) {
                for (int c = 0; c < q; c++) {
                    ans[r][c] += mat[r][k] * other[k][c];
                    ans[r][c] %= MOD;
                }
            }
        }
        return ans;
    }

    void print() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << mat[i][j] << " ";
            } cout << endl;
        }
        cout << "_____________________________" << endl;
    }
} m1, m2;

class Solution {
public:
    int countGoodStrings(long long n) {
        // f(0) = 1
        // f(1) = 1
        // f(2) = 1
        // f(3) = f(0) + f(2) = f(1) + f(2) = 2;
        // f(4) = f(1) + f(3) = f(2) + f(3)
        // f(5) = f(0) + f(2) + f(4) = f(4) + f(3)
        // f(6) = f(1) + f(3) + f(5) = f(4) +  f(5)
        // f(7) = f(0) + f(2) + f(4) + f(6) = f(6) + f(5) 
 
        long long res = 0;
        if(n == 0 || n == 1 || n == 2) {
            res = 1;
        } else {
            m1.init(1, 2, 1);
            m2.init(2, 2, 1);
            m2.mat[0][0] = 0; // base

            long long t = n - 2; 
            for(int i = 0; i < 60; i++) {
                if((t & (1ll << i)) > 0) {
                    m2.print();
                    vector<vector<long long>> vec = m1.mul(m2.mat);
                    m1.mat = vec;
                }
                vector<vector<long long>> vec = m2.mul(m2.mat);
                m2.mat = vec;
            }
            res = m1.mat[0][1];
        }
        res *= 2;
        res %= MOD;
        return res;
    }
};
