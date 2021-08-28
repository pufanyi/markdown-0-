---
title: 后缀自动机学习笔记
tags: 
 - 学习笔记
 - 字符串
 - 后缀自动机

---

**坑，也许不填了**

### 定义

S的后缀自动机的节点中包含且仅包含了S所有的子串。并且其状态最简（节点尽可能少）

后缀自动机（suffix automaton，简称SAM）一般由2部分组成:**DAWG**和**Suffix Link**

<!--more-->

#### DAWG

定义$trans[x][c]$表示从节点（状态）x，加入字符c后到达的状态，可以类比AC自动机构建出的$trie$图。但它是一个**DAG** 。从根到达某一个点的路径其实就是子串的若干字符



### 概念

#### 1、字符串的子串。

一个状态能代表字符串的子串，根据定义可以知道所有节点代表的字符串的集合的并就是S的所有子串，容易理解每个节点代表的字符串的子串都应该是不重复的。

其中一个节点能表示的子串相当于root顺着trans能走到它的一些路径

> 字符串`aabaabaab`中，某一个节点x表示字符串{`aab`,`ab`,`b`}
>
> > 为了简化状态，一个节点可以表示多个子串，如某个节点表示{`aa`}，那么可以表示第一个a，也可以表示第二个，第四个……而且得保证之后不会再有节点表示`aa`

有一个性质就是，每个串都是比它长的那一个串的后缀。而且长度相差为1。

#### 2、max和min

定义max为某个串能表示的所有子串中长度最长的，min表示能表示的串中长度最短的。

注意，min不一定为1。

根据定义，$max-min+1$就是这个串能表示的所有本质不同的子串的数量。

同样知道$\sum _{i=1}^{maxnode} max[i]-min[i]+1$就是S中本质不同的字符串的数量。

#### 3、$right$集合($endpos$)

一个状态的$endpos$代表它能代表的子串的结束位置

同时定义$Cntpos$为$|endpos|$

> 字符串`aabaabaab`中，若某一个节点x表示{`aab`,`ab`,`b`}right集合有{3,6,9}，其$Cntpos$ = 3

所有节点的$Cntpos$再乘上其能表示的子串大小之和就是S所有子串的数目。

#### 4、转移边

定义$trans(x,c)$表示状态$x$加入字符$c$后能转移到哪里。

#### 5、后缀链接(Suffix Link)和parents树

用$next(i)$表示$i$的后缀链接

一个状态有且仅一个后缀链接，表示这个串能表示的最短子串能从哪个状态所代表的最长子串通过去点最前面那个字符得到

如某个状态x表示{`aab`,`aaab`}，如果有一个状态y**包含**{`ab`}，那么x的后缀链接(Suffix Link)就连向y，如果这时候有一个状态z表示{`b`}，那么y的后缀链接转移到z。

容易发现，$min(x) = max(next(x)) + 1$

由于S的所有子串当且仅当在一个节点中出现，所以每个点只可能有一条后缀链接（开始节点没有后缀连接），后缀链接能构成一棵树。我们叫它前缀树或者parents树。

### 举例

> > 蓝色表示转移边
>
> > 绿色表示后缀链接
>
> > {}表示集合
>
> 比如说字符串`aab`构建的后缀自动机（注意节点个数由于可能出现无法表示的点而不一定只有串长个，这里的例子没有出现）
>
> 当然1号点（root）的后缀链接是连向NULL![举例](C:/Users/cqz15/Desktop/hexo%E5%A4%87%E4%BB%BD/source/_posts/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/WF.png)

那么从1走到4的路径有$1->4|1->2->4|1->2->3->4$，显然能代表3个子串

2号点的right集合为{1,2}，right集合可以通过Suffix Link推得到（当前这个节点代表的和它的后缀链接链到的）

### 构造

我讲不清的呀

丢参考链接跑

[menci的博客](https://oi.men.ci/suffix-automaton-notes/)

[陈老师的讲稿](https://wenku.baidu.com/view/fa02d3fff111f18582d05a81.html)

具体思想就是在一个构建好的后缀自动机后面加入一个字符c。

需要维护新加入节点和之前节点的trans和suffix_link。这个可以类比AC自动机。

我们原来的有一个结束状态last。表示上次最后插入的那个状态。

> 令之前的串为S。
>
> 显然last能表示的S的一些后缀。
>
> S到last的路径并没有包含所有后缀，因为有一些后缀是前面出现过的，根据状态最简，所以有一些后缀之前已经出现过了。
>
> 但是我们能够想到，最长的后缀一定是它能代表（包含）的。因为不可能有其他状态能表示。那么根据定义，last能表示的后缀是连续的一段。那么另外一些后缀根据定义，是last所指状态的后缀链接链向的。
>
> 例如S为`abaaab`
>
> 比如说last能代表{`aaab`,`aab`}，那么last的后缀链接能连向一个节点v，v代表{`ab`,`b`}。

所以说，只要顺着last的后缀链接，就能到达所有后缀，只要所有后缀都能链向新节点，如果能遍历所有后缀（包括空也算后缀），就能够完成操作。

但问题在于，万一加入的一个字符使得前面某个后缀已经有转移状态了呢？

假设当前处理到节点v，使得$trans[v][c] != NULL$ ，令$trans[v][c]$ = o

> 还是通过一个实例来理解一下
>
> **强烈建议各位在纸上自己画一画，特别是把代表的字符串画出来**
>
> S = `ababb`
>
> 先插入一个节点代表root，使得其max=0，令last=root
>
> 然后插入第一个节点，简称（1），其表示的子串为`a`，那么从root的`a`的转移便是1，此时1的max=1，同时1号点的Link指向root。令last=1
>
> 然后再插入第二个点（2），注意到1是最后插入的，也就是1的后缀链接能走通所有后缀，那么我们让$trans[1][b] = 2$，表示从1通过在1的所有子串后面加上一个`b`就能组成2集合的一部分。此时（2）可以表示子串{`ab`}，那么顺着后缀链接到字符串`a`的一个后缀（不妨把空也看作后缀），那么从空到（2）一条转移边，意义同上一条转移边，此时2能代表{`b`,`ab`}，令2的Link指向root，因为（2）没能代表的子串只有{空}，令last=2
>
> ![构造2](C:/Users/cqz15/Desktop/hexo%E5%A4%87%E4%BB%BD/source/_posts/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/%E6%9E%84%E9%80%A02.jpg)
>
> 同样的道理插入第三个点，令$trans[2][a] = 3$，$max[3] = max[2]+1 = 3$（至少一定要代表当前的整个前缀。
>
> 那么我们再指向root，发现root已经有a的边的，强行把root的转移边指向3会引发一系列的惨案。我们注意新加入一个串还有一个子串没有处理{`a`}，但事实上，第一个节点代表的就是`a`（而1就正好是root的`a`转移所指向的点），出于最简状态，我们把3号点的Link指向1，发现什么事情都没有发生，还是满足后缀自动机的若干性质，于是令last = 3.
>
> ![构造3](C:/Users/cqz15/Desktop/hexo%E5%A4%87%E4%BB%BD/source/_posts/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/%E6%9E%84%E9%80%A03.jpg)

好奇怪的操作？？？？那么我们加入下一个节点

与第三个节点类似的操作，指向第一个被控制的指向的那个节点），发现竟然依旧满足性

![构造4](C:/Users/cqz15/Desktop/hexo%E5%A4%87%E4%BB%BD/source/_posts/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/%E6%9E%84%E9%80%A04.jpg)

是不是所有情况都可以这么处理？不是。

什么情况下可以这么处理？

假设当前处理到节点v，使得$trans[v][c] != NULL$ ，令$trans[v][c]$ = o

当$max[v]+1 = max[o]$的时候可以直接这么处理。为什么？

注意到这时候我们缺的是v的所以代表的子串在最后面加上一个字符c，所能得到的那些子串的集合。而o正好包含了这些的集合，也就包含了当前缺少的长度最长的那个串T。由于每个节点所能表示的子串都是后缀关系，显然只要它不代表长度大于T的串即可，其等价于它最长的串的长度刚好是max[v]+1，也就是当前缺少的那个串。

> 继续模拟这个过程，我们加入一个字符`b`注意此时有大问题出现了
>
> 模拟4号节点插入5号节点，直到当前处理的v = root，因为root有一条b的转移边。
>
> 注意到5号节点目前代表的集合是{`ababb`,`babb`,`abb`,`bb`}如果强行把5号节点的Link指向2号节点，必然导致`ab`并不是它的子串的后缀。那么问题有点麻烦，怎么办呢？新建一个点，让它只代表{`b`}，让2号点只代表{`ab`}，然后进行一系列的操作，使得满足Link的性质。操作完成之后是这样的。具体步骤就是把2号点的所有转移边复制到6号点，再让6号点的Link指向root，让2号点的Link指向6号，让5号点的Link指向6号。
>
> ![构造5](C:/Users/cqz15/Desktop/hexo%E5%A4%87%E4%BB%BD/source/_posts/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/%E6%9E%84%E9%80%A05.jpg)
>
> 巧妙的数据结构！

很多时候，我们需要得到right集合。具体操作是，一开始在所有结束位置标记一下，然后遍历整个parents树，将其子节点的right集合合并成其的right集合——考虑parents树的性质：一个节点的祖先代表的字符串一定是它代表的字符串的后缀。

### 实现

要记录哪些东西？

一般需要记录max，记录trans（如果字符集大小很大，一般用map来存，否则直接数组存），下面用ch表示，还要记录suffixLink，下面用next表示。

```c++
struct SuffixAutomaton{
	struct Node{
		int ch[26],next,max;
	}node[maxn];
	int start,last;
	int tot;
	SuffixAutomaton(){
		tot = 0;
		start = last = newnode(0);
	}
	int newnode(int max){
		int x = ++tot;
		node[x] . max = max;
		mem(node[x].ch,0);
		node[x] . next = 0;
		return x;
	}
	void extend(int c){
		int u = newnode(node[last] . max + 1),v = last;
		size[u] = 1;
		for(;v && !node[v].ch[c];v = node[v].next)
			node[v].ch[c] = u;
		if(!v){
			node[u] . next = start;
		} else
		if(node[node[v].ch[c]].max == node[v].max + 1){
			node[u].next = node[v].ch[c];
		} else{
			int n = newnode(node[v].max+1),o = node[v].ch[c];
			rep(k,0,26) node[n].ch[k] = node[o].ch[k];
			node[n] . next = node[o].next;
			node[o].next = node[u].next = n;
			for(;v && node[v].ch[c] == o;v=node[v].next)
				node[v].ch[c] = n;
		}
		last = u;
	}
}sam;
```

注：在字符集大小比较大的情况下可以把.ch[]换成map。

**update：2018/9/8：**现在习惯用T[]来表示node[]，用nxt[]表示ch[]，用link表示next。下面附上带有合并right集合的。

```C++
struct SAM{
	static const int maxm = maxn * 2;
	struct node{
		int link,nxt[26],max;
	}T[maxm];
	int tot,start,last;
	SAM(){
		tot = 0;
		start = last = newnode(0);
	}
	int newnode(int x){
		++tot;
		T[tot] . link = 0;
		mem(T[tot].nxt,0);
		T[tot] . max = x;
		return tot;
	}
	int tpos[maxm];
	void extend(char c,int tmpp){
		int u = newnode(T[last].max+1),v = last;
		tpos[u] = tmpp;
		for(;v && T[v].nxt[c] == 0;v = T[v].link){
			T[v] . nxt[c] = u;
		}
		if(!v){
			T[u] . link = start;
		} else
		if(T[v].max+1 == T[T[v].nxt[c]].max){
			T[u] . link = T[v] . nxt[c];
		} else{
			int n = newnode(T[v].max + 1),o = T[v].nxt[c];
			rep(i,0,26) T[n] . nxt[i] = T[o] . nxt[i];
			T[n] . link = T[o] . link;
			T[o] . link = T[u] . link = n;
			for(;v && T[v] . nxt[c] == o;v = T[v].link)
				T[v] . nxt[c] = n;
		}
		last = u;
	}
	vector<int> edge[maxm];
	void dfs(int u){
		for(auto v : edge[u]){
			dfs(v);
			root[u] = merge(root[u],root[v]);
		}
	}
	void init(){
		Rep(i,1,tot) root[i] = 0;
		Rep(i,1,tot) if(tpos[i]){
			insert(root[i],1,n,tpos[i]);
		}
		Rep(i,2,tot){
			edge[T[i] . link] . push_back(i);
		}
		dfs(1);
	}
}sam;
```



### 复杂度

$O(n * alpha)$，$alpha$表示字符集大小。

证明这种东西，我这么菜完全不会。

### 性质

#### parents树

一个节点的parents树上的祖先节点所代表的字符串都是这个节点所代表的字符串的后缀。

换句话说，一个节点的子树中的字符串都是这个节点的字符串在前面加上若干字符得到的。

**字符串S的反串的SAM里面的parents树就是S的后缀树。**这个通过理解parents树的性质很容易理解。

多出来的节点是分叉的时候的显式节点，本来就有的是叶节点。然后可以利用**后缀树的LCA为两个后缀的LCP**来搞事情。

#### right集合（endpos)

就是这个节点所代表的字符串在原串中出现的位置的结束位置的集合。

得到SAM后，我们可以得到S串的所有前缀出现的结束位置，容易发现S的所有前缀的后缀就是S的所有子串，而对于字符串S，它的后缀就是其parents树上的祖先，所以我们可以先在所有字符串S的前缀的结束位置打上一个标记，然后遍历整个树，用线段树合并可以得到right集合。



### 例题

#### codeforces1037H. Security

**update：2018/9/8**

**题意：**

给你一个长度不超过1e5字符串S，接下来m个询问，每个询问给出L,R,T，T是一个总长度不超过2e5的字符串，让你取出S在区间[L,R]的部分得到一个子串SS，然后找SS的子串中字典序严格比T大的最小的字符串，如果不存在输出-1。

**做法：**

如果对于一个固定的前缀，那么后面一定是加上一个字符（多个字符显然更劣）。
对于每一个，我们枚举前缀，然后枚举新的字符（满足变成的字典序要比原来的大），然后判断区间是否存在某个字符串。 
这是一个经典的SAM问题。 
我们先建立出后缀自动机，然后线段树合并爆出right集合，然后找到代表这个字符串的节点，并在其查询right中查询是否存在一个字符串出现在区间内。
处理部分时间复杂度 $O(lenT * 26 * log(lenS))$
注意到我们只需要看每一个位置的下一个即可，我们考虑把right集合作一个转化，转化成下一个字符是否可以是某个值。
然后继续爆"right集合"，这样就可以得到一个前缀在字符串的某个区间能能否加某个字符，注意到这是可以状态压缩的，直接$2^{26}$存每个位置的是否可以即可。
这样枚举下一个字符填什么，就可以$O(1)$判断了。
处理部分时间复杂度 $O(lenT * (26 + log lenS))$。

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
#define Rep(i,a,b) for(register int i=(a);i<=int(b);++i)
#define Dep(i,a,b) for(register int i=(a);i>=int(b);--i)
#define rep(i,a,b) for(register int i=(a);i<int(b);++i)
#define mem(x,v) memset(x,v,sizeof(x))
#define fi first
#define se second
#define gc getchar
#define pc putchar
inline ll rd(){
    ll x=0,f=1;char c=gc();
    for(;!isdigit(c);c=gc())if(c=='-')f=-1;
    for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return x*f;
}
void write(ll x){if(x<0)x=-x,pc('-');if(x>=10)write(x/10);putchar(x%10+'0');}
void writeln(ll x){write(x);puts("");}
const int maxn = 2e5+233;
namespace SegmentTree{
	const int maxm = maxn * 60;
	int lc[maxm],rc[maxm],T[maxm],tot=0;
	inline void insert(int &o,int l,int r,int x,int v){
		if(!o) o = ++tot,T[o] = 0;
		T[o] |= v;
		if(l==r) return;
		int mid = (l + r) >> 1;
		if(x <= mid) insert(lc[o],l,mid,x,v); else
					 insert(rc[o],mid+1,r,x,v);
	}
	inline int query(int o,int l,int r,int x,int y){
		if(!o) return 0;
		if(l==x && r==y) return T[o];
		int mid = (l + r) >> 1;
		if(y <= mid) return query(lc[o],l,mid,x,y); else
		if(mid+1<=x) return query(rc[o],mid+1,r,x,y); else
		return query(lc[o],l,mid,x,mid) | query(rc[o],mid+1,r,mid+1,y);
	}
	inline int merge(int x,int y){
		if(!x || !y) return x + y;
		int z = ++tot;
		T[z] = T[x] | T[y];
		lc[z] = merge(lc[x],lc[y]);
		rc[z] = merge(rc[x],rc[y]);
		return z;
	}
}
using SegmentTree::insert;
using SegmentTree::merge;
using SegmentTree::query;
int root[maxn*2],n;
struct SAM{
	static const int maxm = maxn * 2;
	struct node{
		int link,nxt[26],max;
	}T[maxm];
	int tot,start,last;
	SAM(){
		tot = 0;
		start = last = newnode(0);
	}
	int newnode(int x){
		++tot;
		T[tot] . link = 0;
		mem(T[tot].nxt,0);
		T[tot] . max = x;
		return tot;
	}
	int tpos[maxm],vpos[maxm];
	void extend(char c,int flag){
		int u = newnode(T[last].max+1),v = last;
		tpos[v] = flag;vpos[v] = c;
		for(;v && T[v].nxt[c] == 0;v = T[v].link){
			T[v] . nxt[c] = u;
		}
		if(!v){
			T[u] . link = start;
		} else
		if(T[v].max+1 == T[T[v].nxt[c]].max){
			T[u] . link = T[v] . nxt[c];
		} else{
			int n = newnode(T[v].max + 1),o = T[v].nxt[c];
			rep(i,0,26) T[n] . nxt[i] = T[o] . nxt[i];
			T[n] . link = T[o] . link;
			T[o] . link = T[u] . link = n;
			for(;v && T[v] . nxt[c] == o;v = T[v].link)
				T[v] . nxt[c] = n;
		}
		last = u;
	}
	vector<int> edge[maxm];
	void dfs(int u){
		for(auto v : edge[u]){
			dfs(v);
			root[u] = merge(root[u],root[v]);
		}
	}
	void init(){
		Rep(i,1,tot) root[i] = 0;
		Rep(i,1,tot) if(tpos[i]){
			insert(root[i],1,n,tpos[i],1<<vpos[i]);
		}
		Rep(i,2,tot){
			edge[T[i] . link] . push_back(i);
		}
		dfs(1);
	}
}sam;
char S[maxn],T[maxn];
int main(){
	scanf("%s",S+1);
	n = strlen(S+1);
	Rep(i,1,n) sam.extend(S[i]-'a',i);
	sam.init();
	int Case = rd();
	while(Case--){
		int l = rd(),r = rd();
		scanf("%s",T+1);
		T[strlen(T+1) + 2] = 0;
		T[strlen(T+1) + 1] = 'a'-1;
		int p1=-1,p2=-1;
		int u = 1;
		for(int i=1;T[i] && u;i++){
			int t = query(root[u],1,n,l+i-1,r),tmp = T[i] - 'a' + 1;
			rep(j,tmp,26) if (t >> j & 1){
				p1 = i,p2 = j;
				break;
			}
			if(T[i] >= 'a') u = sam.T[u].nxt[T[i]-'a'];
		}
		if(p1==-1){
			puts("-1");
		} else{
			rep(i,1,p1)pc(T[i]);pc('a'+p2);puts("");
		}
	}
	return 0;
}
```

