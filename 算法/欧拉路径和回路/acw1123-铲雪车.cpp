#include <iostream>
#include <cmath>
using namespace std;

/*
欧拉路劲/回路
路径: 每条边经过一次。
回路：每条边经过一次并回到原点。


无向图
欧拉路劲存在必要条件: 所有度数为奇数的点只能有0 或者 2 个。 (从奇数点开始搜)
欧拉回路存在必要条件: 所有度数为奇数的点只能有0。 (可以从任何点搜)


有向图：
欧拉路劲存在必要条件: 所有点入度等于出度 或者 除两个点所有点入度等于出度，两个点一个满足出度比入度多1一个满足入度比出度多1
欧拉回路存在必要条件: 所有点入度等于出度

必要条件: 在充分条件下，是否可以有种方式一定可以构造一个方案。(是的)


注意:我们需要把搜索的边删除掉。如果是无向图，需要删掉反向边

*/


int main () {
    //两个方向均需要铲雪 -> 必然存在有向图欧拉回路
    double x1, y1, x2, y2;
    cin >> x1 >> y1;
    double ans = 0;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        double dx = x1 - x2,dy = y1 - y2;
        ans += sqrt (dx * dx + dy * dy) * 2;
    }
    int minutes = round (ans / 1000 / 20 * 60);
    int hour = minutes / 60;
    minutes %= 60;
    printf ("%d:%02d\n",hour,minutes);
    return 0;
}
