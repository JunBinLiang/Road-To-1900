class Solution {
    List<Integer> graph[];
    int[] dp;
    int[] fa;
    int[] sz;
    public int minimumScore(int[] a, int[][] edges) {
        int n = a.length;
        dp = new int[n];
        fa = new int[n];
        sz = new int[n];
        graph = new ArrayList[n];
        Arrays.setAll(graph, e -> new ArrayList<>());
        for(int[] e : edges) {
            graph[e[0]].add(e[1]);
            graph[e[1]].add(e[0]);
        }

        dfs1(a, -1, 0);

        int ans = Integer.MAX_VALUE;
        for(int i = 0; i < edges.length; i++) {
            int u = edges[i][0], v = edges[i][1];
            int first = dp[0], second = 0, firstsz = 0;
            List<Integer> xos1 = new ArrayList<>();
            if(fa[u] == v) {
                second = dp[u];
                firstsz = n - sz[u];
                if(sz[u] > 1) {
                    dfs2(xos1, v, u);
                }
            } else {
                second = dp[v];
                firstsz = n - sz[v];
                if(sz[v] > 1) {
                    dfs2(xos1, u, v);
                }   
            }
            first ^= second;

            List<Integer> xos2 = new ArrayList<>();
            if(firstsz > 1) {
                dfs3(xos2, a, -1, 0, u, v);
            }

            //ignore the first as it treat the tree as whole
            for(int j = 1; j < xos1.size(); j++) {
                int xo = xos1.get(j);
                ans = Math.min(ans, cal(first, second ^ xo, xo));
            }

            for(int xo : xos2) {
                ans = Math.min(ans, cal(first ^ xo, xo, second));
            }
        }
        return ans;
    }

    public int cal(int a, int b, int c) {
        int[] t = new int[]{a, b, c};
        Arrays.sort(t);
        return t[2] - t[0];
    }

    public void dfs1(int[] a, int pa, int u) {
        dp[u] = a[u];
        fa[u] = pa;
        sz[u] = 1;
        for(int v : graph[u]) {
            if(v == pa) continue;
            dfs1(a, u, v);
            dp[u] ^= dp[v];
            sz[u] += sz[v];
        }
    }

    public void dfs2(List<Integer> xos, int pa, int u) {
        xos.add(dp[u]);
        for(int v : graph[u]) {
            if(v == pa) continue;
            dfs2(xos, u, v);
        }
    }

    public int dfs3(List<Integer> xos, int[] a, int pa, int u, int ban1, int ban2) {
        int xo = a[u];
        for(int v : graph[u]) {
            if(v == pa) continue;
            if((u == ban1 && v == ban2) || (u == ban2 && v == ban1)) continue;
            xo ^= dfs3(xos, a, u, v, ban1, ban2);
        }
        if(pa != -1)
            xos.add(xo);
        return xo;
    }
}
