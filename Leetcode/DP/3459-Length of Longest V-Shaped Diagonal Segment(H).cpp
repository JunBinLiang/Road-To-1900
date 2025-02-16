vector<vector<int>> dir = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}}; 
vector<int> t = {1, 2, 3, 0};
int dp1[510][510][4];
int dp2[510][510][4];
bool vis[510][510][4];
int n, m;
bool in(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& a) {
        n = a.size();
        m = a[0].size();
        memset(vis, 0, sizeof vis);
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                for(int k = 0; k < 4; k++) {
                    dp1[i][j][k] = dp2[i][j][k] = 0;
                }
            }
        }
        
        for(int k = 0; k < 4; k++) {
            if(k >= 2) {
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < m; j++) {
                        if(a[i][j] != 2) continue;
                        if(vis[i][j][k]) continue;
                        auto& d = dir[k];
                        int r = i, c = j;
                        int len = 0;
                        vector<pair<int, int>> b;
                        while(in(r, c)) {
                            if(len % 2 == 0) {
                                if(a[r][c] == 2) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            } else {
                                if(a[r][c] == 0) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            }
                            r += d[0];
                            c += d[1];
                        }
                        for(auto& p : b) {
                            if(a[p.first][p.second] == 2) dp1[p.first][p.second][k] = max(dp1[p.first][p.second][k], len);
                            else dp2[p.first][p.second][k] = max(dp2[p.first][p.second][k], len);
                            len--;
                        }
                    }
                }
            } else {
                for(int i = n - 1; i >= 0; i--) {
                    for(int j = 0; j < m; j++) {
                        if(a[i][j] != 2) continue;
                        if(vis[i][j][k]) continue;
                        auto& d = dir[k];
                        int r = i, c = j;
                        int len = 0;
                        vector<pair<int, int>> b;
                        while(in(r, c)) {
                            if(len % 2 == 0) {
                                if(a[r][c] == 2) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            } else {
                                if(a[r][c] == 0) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            }
                            r += d[0];
                            c += d[1];
                        }
                        for(auto& p : b) {
                            if(a[p.first][p.second] == 2) dp1[p.first][p.second][k] = max(dp1[p.first][p.second][k], len);
                            else dp2[p.first][p.second][k] = max(dp2[p.first][p.second][k], len);
                            len--;
                        }
                    }
                }
            }
        }
        
        
        
        memset(vis, 0, sizeof vis);
        for(int k = 0; k < 4; k++) {
            if(k >= 2) {
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < m; j++) {
                        if(a[i][j] != 0) continue;
                        if(vis[i][j][k]) continue;
                        auto& d = dir[k];
                        int r = i, c = j;
                        int len = 0;
                        vector<pair<int, int>> b;
                        while(in(r, c)) {
                            if(len % 2 == 0) {
                                if(a[r][c] == 0) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            } else {
                                if(a[r][c] == 2) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            }
                            r += d[0];
                            c += d[1];
                        }
                        for(auto& p : b) {
                            if(a[p.first][p.second] == 2) dp1[p.first][p.second][k] = max(dp1[p.first][p.second][k], len);
                            else dp2[p.first][p.second][k] = max(dp2[p.first][p.second][k], len);
                            len--;
                        }
                    }
                }
            } else {
                for(int i = n - 1; i >= 0; i--) {
                    for(int j = 0; j < m; j++) {
                        if(a[i][j] != 0) continue;
                        if(vis[i][j][k]) continue;
                        auto& d = dir[k];
                        int r = i, c = j;
                        int len = 0;
                        vector<pair<int, int>> b;
                        while(in(r, c)) {
                            if(len % 2 == 0) {
                                if(a[r][c] == 0) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            } else {
                                if(a[r][c] == 2) {
                                    len++;
                                    b.push_back({r, c});
                                    vis[r][c][k] = true;
                                } else {
                                    break;
                                }
                            }
                            r += d[0];
                            c += d[1];
                        }
                        for(auto& p : b) {
                            if(a[p.first][p.second] == 2) dp1[p.first][p.second][k] = max(dp1[p.first][p.second][k], len);
                            else dp2[p.first][p.second][k] = max(dp2[p.first][p.second][k], len);
                            len--;
                        }
                    }
                }
            }
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] != 1) continue;
                for(int k = 0; k < 4; k++) {
                    auto& d = dir[k];
                    int nk = t[k];
                    int r = i + d[0], c = j + d[1];
                    int len = 1;
                    ans = max(ans, 1);
                    while(in(r, c)) {
                        if(len % 2 == 1) {
                            if(a[r][c] == 2) {
                                len++;
                                ans = max(ans, len);
                                ans = max(ans, len + dp1[r][c][nk] - 1);
                            } else {
                                break;
                            }
                        } else {
                            if(a[r][c] == 0) {
                                len++;
                                ans = max(ans, len);
                                ans = max(ans, len + dp2[r][c][nk] - 1);
                            } else {
                                break;
                            }
                        }
                        r += d[0];
                        c += d[1];
                    }
                }
            }
        }
        
        return ans;
    }
};
