---
title: codeforces915
tags:
 - codeforces
 - bitset
 - 博弈
---

做完A,B，C总共WA了3次（没有特判0），然后做D，写着写着B被hack了。先回去改了B。

等我做完4题，已经一个半小时过去了，而WZP用了40分钟就A了4题。

看E题：dsu on tree?点分治？没写过，算了。弃疗。hack了4发C(哇，别人都没有特判1的情况)。

貌似wzp没有刚出E……

<!--more-->



#### [A:Perfect Squares](http://codeforces.com/contest/914/problem/A)

题解:模拟

### [B:Conan and Agasa play a Card Game](http://codeforces.com/contest/914/problem/B)

题解:如果存在一个是奇数，那么先手比赛，否则先手必输。

### [C:Travelling Salesman and Special Numbers](http://codeforces.com/contest/914/problem/C)

题解：数位DP，注意特判k=0和k=1.

```c++
//省略一堆头文件
int f[2333],k;
int count(int x){
	int ans = 0;
	while(x) x&=x-1,ans++;
	return ans;
}
int dp[1199][1199];
char s[2399];int len,ans;
int dfs(int i,int num,bool flag){
	if(num < 0) return 0;
	if (i == len+1){
		if (num == 0) return 1;
		return 0;
	}
	if (flag){
		int res = 0;
		if (s[i]=='1') res = (res + dfs(i+1,num-1,true)) % Mod;
		res = (res + dfs(i+1,num,(s[i]-'0'==0))) % Mod;
		return res;
	} else{
		int &res = dp[i][num];
		if (res != -1) return res;
		res = (dfs(i+1,num-1,false)+dfs(i+1,num,false)) % Mod;
		return res;
	}
}
int main(){
	scanf("%s",s+1);
	len = strlen(s+1);
	
	k = read();
	f[1] = 0;
	for (int i=2;i<=1005;i++){
		f[i] = f[count(i)] + 1;
	}
	ans = 0;
	memset(dp,-1,sizeof(dp));
	for (int i=1;i<=1005;i++){
		if (f[i] + 1 == k)
			ans = (ans + dfs(1,i,true)) % Mod;
	}
	if(k==1) ans = (ans - 1 + Mod) % Mod;
	if(k==0) ans = 1;
	printf("%d\n",ans);
	return 0;
}
```

### [D;Bash and a Tough Math Puzzle](http://codeforces.com/contest/914/problem/D)

题解:考虑用一棵线段树维护区间的gcd。

显然，如果区间内有超过1个数不是x的倍数，那么答案是NO

我们可以在线段树上查询，如果区间gcd是x的倍数，那么可以直接跳了，否则搜下去，直到叶子结点，那么res++。

注意到最多不会超过log次就能查询到整段的。

PS：

你首先通过不超过log次，能够得到一个分叉口，那么分叉往下，左边一半一定只有一个会一直往下，所以不超过log，右边同样不超过log。

然后算上$gcd$，大概是$O(n log^2)$。

```c++
//省略一堆头文件
#define N 500005
int gcd(int a,int b){return (!b)?a:gcd(b,a%b);}
#define mid ((l+r)>>1)
#define lson ((o<<1))
#define rson ((o<<1)|1)
int T[N*4],a[N],n;
void build(int o,int l,int r){
	if (l == r){T[o] = a[l];return ;}
	build(lson,l,mid);
	build(rson,mid+1,r);
	T[o]=gcd(T[lson],T[rson]);
}
int pos;
void findpos(int o,int l,int r,int x,int y,int v){
	if(T[o]%v==0)return;
	if(pos>=2)return;
	if(l==r){pos++;return;}
	if(y<=mid) findpos(lson,l,mid,x,y,v); else
	if(mid+1<=x) findpos(rson,mid+1,r,x,y,v); else{
		findpos(lson,l,mid,x,mid,v);
		if(pos>=2) return;
		findpos(rson,mid+1,r,mid+1,y,v);
	}
}
void update(int o,int l,int r,int x,int v){
	if(l==r){T[o]=v;return;}
	if(x<=mid)update(lson,l,mid,x,v); else
			  update(rson,mid+1,r,x,v);
	T[o]=gcd(T[lson],T[rson]);
}
int main(){
	n = read();
	for (int i=1;i<=n;i++) a[i] = read();
	build(1,1,n);
	int Q = read();
	while(Q--){
		int op = read();
		if (op == 1){
			int l = read(),r = read(),x = read();
			pos = 0;
			findpos(1,1,n,l,r,x);
			if(pos>=2) puts("NO"); else puts("YES");
		} else{
			int x = read(),v = read();
			update(1,1,n,x,v);
		}
	}
	return 0;
}
```

### [F:Substrings in a String](http://codeforces.com/contest/914/problem/F)

##### 题意：

​	给你一个字符串，然后若干次操作。

​	操作1:将某个字符修改

​	操作2:询问[L,R]中有多少个字串是S(新给定的)

##### 题解:

​	类似Shift-And算法。

​	给每个字符建立$bitset$，修改就直接修改$bitset$，然后如果是查询，考虑先把$ans$的[L,R]区间赋值成1，然后每次往左移动一位，和$bitset$&一下，最后统计有多少

```c++
//省略一堆头文件
#define N 100005
bitset<N> f[26],ans;
char s[N],ch[N];
int n,Q;
int main(){
	scanf("%s",s+1);
	n = strlen(s+1);
	for (int i=1;i<=n;i++) s[i] -= 'a',f[s[i]][i] = 1;
	Q = read();
	while(Q--){
		int op = read();
		if(op==1){
			int pos = read(),ch = gc();
			f[s[pos]][pos] = 0;
			s[pos] = ch-'a';
			f[s[pos]][pos] = 1;
		} else{
			int l = read(),r = read();
			scanf("%s",ch);
			int len = strlen(ch);
			if(r-l+1 < len){
				puts("0");
				continue;
			}
			ans.set();
			ans <<= (l-1);
			ans ^= (ans << (r-l+2-len));
			for (int i=0;i<len;i++)
				ans = (ans << 1) & f[ch[i] - 'a'];
			writeln(ans.count());
		}
	}
	return 0;
}
```

