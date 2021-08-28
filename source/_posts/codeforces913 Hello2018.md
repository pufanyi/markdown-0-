---
title: codeforces913-Hello2018
tags:
 - codeforces
---

官方题解：http://codeforces.com/blog/entry/56992

### A. Modular Exponentiation

> 给你n和m，求$m$ $mod$ $2^n$ $n,m<=1e8$

​	显然暴力计算$2^n$，一旦大于m直接输出m。

```c++
int n,m;
int Pow(int b){
	int ans = 1;
	while (b){
		ans = ans * 2;
		if (ans > m) return m+1;
		b--;
	}
	return ans;
}
int main(){
	n = read(), m = read();
	printf("%d\n",m%Pow(n));
	return 0;
}
```

### B. Christmas Spruce

	>给你一棵有根树(a rooted tree)，问它是否满足所有非叶子结点都有至少3个儿子。

​	直接计算也可以呀，我用了$dfs$

```c++
bool dfs(int u){
	if (first[u]==-1) return true; 
	int res = 0;
	for (int e=first[u];~e;e=edge[e].nxt){
		int v = edge[e].to;
		if (first[v] == -1) res++;
		if (!dfs(v)) return false;
	}
	if (res >= 3) return true; else return false;
}
int n;
int main(){
	n = read();
	memset(first,-1,sizeof(first));nume = 0;
	for (int i=2;i<=n;i++){
		int x = read();
		Addedge(x,i);
	}
	if (dfs(1)) puts("Yes"); else puts("No");
	return 0;
}
```

### C. Party Lemonade

>有一些价格分别为$c_i$，并且容量为$2^{i-1}$的瓶子，为最小的代价得到至少的容量。

考虑对于$c[i]$，显然可以用$2*c[i-1]$和$c[i+1]$来update(一直递推过去)。

考虑贪心，从高位到低位，每次一定是删除到几乎没有

然后考虑要不要删除最后一个，更新一个答案即可。

```c++
ll n,L;
ll c[33];
ll res;
int main(){
	n = read(),L = read();
	c[0] = c[n+1] = 1e9+1;
	
	for (int i=1;i<=n;i++) c[i] = read();
	for (int i=n;i>=1;i--) c[i] = min(c[i],c[i+1]);
	for (int i=1;i<=n;i++) c[i] = min(c[i],2*c[i-1]);
	ll ans = 0;
	ll res = 1e18+1;
	ll p = 1;
	for (int i=2;i<=n;i++) p = p * 2;
	for (int i=n;i>=1;i--){
		if (L >= p){
			ans += (L/p) * c[i];
			L -= (L/p)*p;
		}
		res = min(res,L==0?ans:ans+c[i]);
		p=p/2;
	}
	printf("%I64d\n",res);
	return 0;
}
```

### D. Too Easy Problems

>给你$n$和$T$,给你一些$a_i$,$t_i$，选择一些数，使得$\sum t_i <= T$选了$ans$个数，则对于选择的数中所有满足$a_i$>=$ans$的，对答案都有贡献，问满足最大贡献的一组数

​	显然，要选的满足$ans=答案$一定是最优秀的，那么我们可以二分答案，然后对于大于等于$ans$的，直接排序后贪心

​	时间复杂度$O(n log_2T log _2n)$

```c++
int n,T;
struct P{
	int a,t,id;
	bool operator < (const P &x) const{
		return t < x.t;
	}
}p[N];
int L,R,ans;
int tmp[N];
bool check(int k){
	tmp[0] = 0;
	for (int i=1;i<=n;i++)
		if (p[i].a >= k) tmp[++tmp[0]] = p[i].t;
	if (tmp[0] < k) return false;
	sort(tmp+1,tmp+1+tmp[0]);
	ll res = 0;
	for (int i=1;i<=k;i++) res += tmp[i];
	if (res <= T) return true; else return false;
}
int main(){
	L = 0,R = 0;ans = -1;
	n = read(),T = read();
	for (int i=1;i<=n;i++){
		p[i].a = read();p[i].t = read();p[i].id = i;
		R = max(R,p[i].a);
	}
	while(L<=R){
		int mid = (L+R)>>1;
		if (check(mid)){
			ans = mid;
			L = mid+1;
		} else 
			R = mid-1;
	}
	printf("%d\n",ans);
	printf("%d\n",ans);
	for (int i=1;i<=n;i++)
		if (p[i].a < ans) p[i].t = 0x7fffffff;
	sort(p+1,p+1+n);
	for (int i=1;i<=ans;i++) printf("%d ",p[i].id);
	return 0;
}
```

### E. Logical Expression

	>设![img](http://codeforces.com/predownloaded/16/bf/16bf4b244da0bb4b671053081fa2353ebb1c37b8.png), ![img](http://codeforces.com/predownloaded/7c/a5/7ca565369760ee0652ecbeebb25ff95c8c220370.png)and ![img](http://codeforces.com/predownloaded/c2/65/c265ac652438dfb87b2009bf26c963a332fc6e13.png).对于$j∈[1,8]$ ，求一个由$x$$y$$z$$!$$|$$\&$构成的布尔表达式，满足对于j取不同值的时候，其真假为1或0

考虑对于"x&y，如果设其在不同的时候值为$f_i$，满足$1<=i<=8$，同样设"x|y"，其值为$g_i$

那么对于$(x\&y)|(x|y)$答案就是$fi | gi$，对于$(x\&y)\&(x|y)$，答案就是$fi\&gi$，设$(A)$的值为$ti$，则$!(A)$的值就是$ti$取反的后8位。

​	通过这些信息，我们就可以BFS了。用优先队列保证字典序。

考虑得到最后一步操作是not还是and还是or。然后更新的时候要不要括号。

见