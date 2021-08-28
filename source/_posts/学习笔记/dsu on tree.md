---
title: dsu on tree
---

大概是看了一波，然后感觉

​	貌似大多数情况下还是点分优秀？

​		也许能解决一些点分不能解决的题。

​	貌似大多数情况下还是莫队好写？

​		而且有时候复杂度是两只log，而莫队只要一个根号+小常数。

<!--more-->

推荐并感谢：http://codeforces.com/blog/entry/44351

#### dsu on tree是什么

​	大概是基于启发式的树上某离线算法。

#### dsu on tree能干什么？

​	**离线**解决一些关于某个节点的子树的问题。

#### $dsu on tree$大概有多慢

​	外层套着的复杂度是$O(n log n)$的。但是常数小呀——因为是基于树剖的呀。

#### 预备知识

​	其实并没有。只需要知道一点类似树链剖分(heavy-light decomposition)的关于重儿子的概念。



#### 例题：

**codeforces600E. Lomsat gelral**


​	http://codeforces.com/contest/600/problem/E

​	**题意：**


​		n个点的有根树，以1为根，每个点有一种颜色。我们称一种颜色占领了一个子树当且仅当没有其他颜色在这个子树中出现得比它多。求占领每个子树的所有颜色之和。

​	**题解:**


​		考虑暴力的做法，我们可以遍历这个子树内的每一个节点，然后把占领颜色最多的通过一个数组计算出来。

​		做完之后暴力删除这个节点的贡献。

​		时间复杂度$O(n^2)$

贡献大概可以类似地算:

```
cnt[c[u]]++;
if(cnt[c[u]]>=cmax){
	if(cnt[c[u]] > cmax){
		cmax = cnt[c[u]];
		sum = 0;
	}
	sum += c[u];
}
```

​		我们注意到，有些有用的信息也被删除了。

​		考虑一种优化，我们对于每一个节点都保存这样的值，然后合并到它的父亲上，用set来进行启发式合并，这样能时间复杂度是$O(n log^2n)$

​	还可以这么做：

​		我们对于一棵树每一个节点找出重儿子，每次先处理轻儿子，暴力删除轻儿子的贡献，然后把重儿子（因为是最后处理的，所以不会对前面的轻儿子的处理产生干扰）的贡献传递给父亲。

​		到要处理一个点的时候，暴力算轻儿子的贡献。这样的复杂度对吗？

​		因为一条路径上最多只会有$log$个轻边，而每个点只有上面的轻边的时候才会被删除，所以复杂度是$O(n log n)$。

​	这其实是**dsu on tree**的一种通用解法。



#### 练习题

​	让自己慢慢做吧。

​	我还是太弱了。





题面:http://codeforces.com/contest/600/problem/E

> 代码:http://codeforces.com/contest/600/submission/33974891



题面: http://codeforces.com/problemset/problem/570/D

> 代码: http://codeforces.com/contest/570/submission/33975177
>
> ​	这题的做法大概就是update的时候用树状数组来维护。



题面: http://codeforces.com/problemset/problem/208/E

> 代码: http://codeforces.com/contest/208/submission/33975619



题面: http://codeforces.com/problemset/problem/375/D

> 用dsu on tree貌似超时了，应该是我哪里写错了
>
> 代码1(TLE): http://codeforces.com/contest/375/submission/33976745
>
> 大概是改不对，所以抄一个莫队……
>
> 代码2(AC): http://codeforces.com/contest/375/submission/33976761



题面：http://codeforces.com/problemset/problem/741/D

> 大概就是用一个1<<22的数组来保存一个点到根路劲上的状态（是奇数还是偶数），然后回文就是只有一个或者没有是奇数的，那么枚举哪个是奇数。update一下。代码：http://codeforces.com/contest/741/submission/33978144



题面：http://www.lydsy.com/JudgeOnline/problem.php?id=2599

> 太难，不做了。