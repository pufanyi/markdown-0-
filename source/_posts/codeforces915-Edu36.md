---
title: codeforces915-Edu36
tags:
 - codeforces
---

当$xza$秒掉C题的时候，我刚做完B题。

当$wzp$1小时AK共$7problem$。

当比赛结束的时候，我还是只做了三题。

讲道理F题的做法我也差不多想到了，可就差这么一点点。

讲道理G题应该可以做，却认为是最后一题只看了看就没想。

终归我还是太弱，连D题都想不到，连C题都码不出。

<!--more-->

猛然翻$wzp$的CF刷题记录，更是震撼。各种E题……

我？大概已经颓了三个礼拜了。

我得努力啊！

### A. Garden

​	直接做。

### B. Browser

​	直接做。

### D. Almost Acyclic Graph

​	暴力一点，直接先找到一个环(O(n+m))，枚举环上的边试着去掉之后再找环(O(n * (n+m)))。

​	因为环最多不超过n条边QAQ

### E. Physical Education Lessons

​	给你一个一开始全部是1的序列，支持区间覆盖为0，区间覆盖为1，求序列中有多少1。

​	序列长度<=1e9，询问<=3e5。

​	离散化之后直接线段树lazy维护啊。

### F. Imbalance Value of a Tree

​	考虑把Max 和 Min分别处理。

​	对于Max，我们把每一条边的边权赋值成它两端较大的那个点权，然后忽略点权。

​	这样就可以对边排序一下，然后并查集维护size域即可。

​	小于同理。

### G. Coprime Arrays

​	设$f[i]$为当选择为$1$~$i$时候答案。

​	$\large f[k] = \sum_{a1=1}^{k}\sum_{a2=1}^{k}…\sum_{an=1}^{k} * (gcd(a1,a2……ak)==1)$

​		$\large = \sum_{a1=1}^{k}\sum_{a2=1}^{k}…\sum_{an=1}^{k} * \sum_{D|a_1,…,D|a_n} mu[D]$

​		$\large =\sum_{D=1}^{k} mu[D] * (k/D)^n$

​	然后得到一个mu[D]的前缀和，根据$k/d$只有本质不同的$O(sqrt(k))$个来计算。这么做是$O(nsqrt(n))$的。听说CF机子很好。

​	然而看到$wzp$是用$n log n$算的。

​	试着做一下。

​	考虑差分	$\large f[k] - f[k-1] = \sum_{D=1}^{k-1} (mu[D] * ((k/D)^n - ((k-1)/D)^n))  + mu[k]*(k/k)^n$

然后考虑只有当$D|k$的时候，$k/D$和$(k-1)/D$会有1的差别。

证明：

​	$k/D = k - k \% D$,||||||||||||||||$(k-1) / D = k - (k-1) \% D - 1$

​	然后可以知道，当$k\%D$不是1的时候，$(k-1)\%D = k\%D-1$然后就抵消掉了。

​	于是只需要计算$k|D$的情况。

​	根据调和级数，得到时间复杂度是$O(n log n)$

```c++
int main(){
	n = read(),k = read();
	init();
	for (int i=1;i<=k;i++){
		for (int j=i;j<=k;j+=i){
			ans[j] = (1LL * ans[j] + 1LL * mu[i] * Pow[j/i]%Mod)%Mod;
			if (i!=j)
			ans[j] = (1LL * ans[j] - 1LL * mu[i] * Pow[j/i-1]%Mod + Mod)%Mod;
		}
	}
	for (int i=1;i<=k;i++){
		ans[i] = (ans[i] + ans[i-1]) % Mod;
		res = (res + (ans[i] ^ i)) % Mod;
	}
	writeln(res);
	return 0;
}
```
