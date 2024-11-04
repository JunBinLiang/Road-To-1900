/*
后缀自动机 
https://www.acwing.com/solution/content/59210/

存一个字符串的所有子串。（任何一条从 起点 出发到某一条结束的路径，代表一个原字符串的子串）
有向无环图。点数边数 -> O(n)

每个点对应若干个子串。这些子串一定是里面最长那个子串的连续后缀。
例如这些所有对应子串中的最长子串是abcde, 其它的可能是cde, bcde ...

两种边：(假设当前的点代表以下子串 : cde bcde abcde)
1. 表示这些所有的子串都加一个字母。例如向f连边，那这个f就多了 (cdef bcdef abcdef) 这些子串
2. 找出这些所有子串的最短一个（cde），删掉第一个(变成de), 像它所在的点连边 (边是唯一的，这类边是一棵树)


构造:
s = "aabbabd"
       
E("ab") = {3, 6}  (用最后出现的下标表示，这里是1-index)

有可能有两个子串完全一样的集合。例如aabb = {4}, abb = {4}。我们可以把集合完全一样的称为等价类
我们可以用定义的等价类表达自动机的每一个状态

E的性质：
1. |s1| <= |s2| 并且s1 是s2 的后缀， 那么 E(s1) 包含 E(s2)。如果s1 不是s2的后缀，那E(s1) 和E(s2) 无交集
2. 两个子串的E只有两种情况: 有交集那必定是包含关系或者无交集
3. 如果两个子串的E相同，那短串必定是长串的后缀
4(最重要): 对于任何一个状态(等价类)st, 每个等价类可能有很多个子串(这些子串E相同)。 
longest(st) 表示这里面最长的子串。shortest(st) 表示这里面最短的子串。
shortest(st) 是longest(st) 后缀，他们之间的后缀都属于st 这个等价类。
例如 longest(st) = abcdef， shortest(st) = def, 那cdef bcdef abcdef 也一定是同样的st
一定所有都包含了(长度介于最长和最短中间的所有子串)。更短的话例如ef,可能出现在其它状态里。

对应上面性质: 每个点对应若干个子串。这些子串一定是里面最长那个子串的连续后缀。存了所有最短到最长串。

## 用E 等价类表示每一个点状态。

*/

struct SAM { 
    struct Node {
        int maxL, fa;
        int ch[26];
    } nodes[10000 + 100];
    
    long long cnt[10000 + 100];
    int tot = 1, last = 1; //当前点编号 和 上一个点
    void init() {

    }

    void extend(int c) { 
        int p = last; //上一个状态
        int cur = last = ++tot; //现在状态
        nodes[cur].maxL = nodes[p].maxL + 1; //新状态长度是上一个状态长度 +1
        cnt[tot] = 1; //是前缀 
        while(p && nodes[p].ch[c] == 0) { //沿着fa走，如果没有c 这个儿子就指向cur
            nodes[p].ch[c] = cur;
            p = nodes[p].fa;
        }
        if(!p) { //p变成空 => 沿着fa走这条路径全没有c这个儿子
            nodes[cur].fa = 1; //连向起始点, 代表 shortest(st) = 1，包含了全部
        } else {
            int u = nodes[p].ch[c];
            if (nodes[p].maxL + 1 == nodes[u].maxL) nodes[cur].fa = u;
            else {
                int newu = ++tot; //new node
                nodes[newu] = nodes[u], nodes[newu].maxL = nodes[p].maxL + 1;
                nodes[u].fa = nodes[cur].fa = newu;
                //替换
                while(p && nodes[p].ch[c] == u) {
                    nodes[p].ch[c] = newu;
                    p = nodes[p].fa;
                }
            }
        }
    }
};
