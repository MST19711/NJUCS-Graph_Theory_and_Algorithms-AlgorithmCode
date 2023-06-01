# NJUCS-Graph_Theory_and_Algorithms_2023-OJcode
> 这些代码可以通过2023年春季课程的的OJ中的所有测试，除此之外我无法保证她们的正确性

这个仓库包含了2023年春季学期NJUCS 图论与算法Graph_Theory_and_Algorithms(GTA)课程的4次OJ上机测试中所有题目的代码。

其涉及到的算法依次有:

## test1
1. 用于判图中存在几个联通分支的简单的DFS 
2. 用于判断图中有几个割点(Cut Vertex)并输出这些割点的Tarjan(DFSCV)算法
## test2
1. 用于找出图中所有块的Tarjan(DFSBlk)算法
2. 用于找出图中的一条欧拉迹的希尔霍尔策(Hierholzer)算法
## test3
1. 用于找出网络中最大流的Ford_Fulkerson算法
2. 用于找出二分图中最大匹配的匈牙利算法
## test4
1. 用于判断2连通简单图是否为可平面图的DMP算法
2. 使用Tarjan(DFSBlk)算法将任意简单图切割成若干2连通简单子图，然后使用DMP算法判断每个2连通简单子图是否为可平面图，从而判断整张简单图是否为可平面图

对于test4，我提供了3个样例输入用于初步测试程序是否可以正常运行。

**请不要直接将这些代码复制并提交到OJ，请遵守课程对Academic Integrity的要求**