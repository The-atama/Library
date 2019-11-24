template<class N>
struct segbeats{
	vector<N> x;
	int s;
	template<class T>
	segbeats(const vc<T>& a){
		int n=a.size();
		s=1;
		while(s<n)s*=2;
		x.resize(s*2);
		rep(i,n)
			x[s+i]=N(a[i]);
		gnr(i,1,s)
			upd(i);
	}
	void push(int i){
		x[i].push(x[i*2],x[i*2+1]);
	}
	void upd(int i){
		x[i]=N::merge(x[i*2],x[i*2+1]);
	}
	template<class F,class... Args>
	void chr(int l,int r,int i,int b,int e,F f,Args... args){
		if(e<=l||r<=b)
			return;
		if(b<=l&&r<=e&&(x[i].*f)(args...))
			return;
		push(i);
		int m=(l+r)/2;
		chr(l,m,i*2,b,e,f,args...);
		chr(m,r,i*2+1,b,e,f,args...);
		upd(i);
	}
	template<class F,class... Args>
	void ch(int b,int e,F f,Args... args){
		assert(b<e);
		chr(0,s,1,b,e,f,args...);
	}
	//use decltype((declval<N>().*F())()) for old-fashioned judges
	template<class F,class G,class H>
	auto getr(int l,int r,int i,int b,int e,F f,G g,H h){
		if(e<=l||r<=b)
			return h;
		if(b<=l&&r<=e)
			return (x[i].*f)();
		push(i);
		int m=(l+r)/2;
		return g(getr(l,m,i*2,b,e,f,g,h),getr(m,r,i*2+1,b,e,f,g,h));
	}
	template<class F,class G,class H>
	auto get(int b,int e,F f,G g,H h){
		assert(b<e);
		return getr(0,s,1,b,e,f,g,h);
	}
	//return minimum index
	template<class F,class...Args>
	pair<int,N> findr(int i,int l,int r,int b,int e,F f,Args&...args){
		if(e<=l||r<=b)return {e,N()};
		if(b<=l&&r<=e){
			if(!(x[i].*f)(args...))return {e,N()};
			if(r-l==1)return {l,x[i]};
		}
		push(i);
		int m=(l+r)/2;
		auto a=findr(i*2,l,m,b,e,f,args...);
		if(a.a<e)return a;
		return findr(i*2+1,m,r,b,e,f,args...);
	}
	template<class F,class...Args>
	pair<int,N> find(int b,int e,F f,Args&...args){
		assert(b<e);
		return findr(1,0,s,b,e,f,args...);
	}
	//NOT VERIFIED
	/*
	//return maximum index
	template<class F,class...Args>
	pair<int,N> findr(int i,int l,int r,int b,int e,F f,Args&&...args){
		if(e<=l||r<=b)return {b-1,N()};
		if(b<=l&&r<=e){
			if(!(x[i].*f)(args...))return {b-1,N()};
			if(r-l==1)return {l,x[i]};
		}
		push(i);
		int m=(l+r)/2;
		auto a=findr(i*2+1,m,r,b,e,f,forward<Args>(args)...);
		if(a.a>=b)return a;
		return findr(i*2,l,m,b,e,f,forward<Args>(args)...);
	}
	template<class F,class...Args>
	pair<int,N> find(int b,int e,F f,Args&&...args){
		assert(b<e);
		return findr(1,0,s,b,e,f,forward<Args>(args)...);
	}
	*/
};

//usage

struct N{
	int l1,l2,a,b,num,sum;
	N(int v=0):l1(-1),l2(0),a(!(v%2)),b(v%2),num(1),sum(v){}
	bool add(int v){
		l2+=v;
		if(v%2)swap(a,b);
		sum+=num*v;
		return true;
	}
	bool mod(){
		l1=(l2+(l1==-1?0:l1))%2;
		l2=0;
		sum=b;
		return true;
	}
	void push(N& x,N& y){
		if(l1!=-1){
			x.add(l1);
			x.mod();
			y.add(l1);
			y.mod();
			l1=-1;
		}
		x.add(l2);
		y.add(l2);
		l2=0;
	}
	static N merge(N x,N y){
		N res;
		res.a=x.a+y.a;
		res.b=x.b+y.b;
		res.num=x.num+y.num;
		res.sum=x.sum+y.sum;
		return res;
	}
	int gets(){
		return sum;
	}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
	
	int n,q;cin>>n>>q;
	vi a=readvi(n);
	segbeats<N> seg(a);
	rep(_,q){
		int t,l,r;cin>>t>>l>>r;
		l--;
		if(t==1){
			seg.ch(l,r,&N::mod);
		}else if(t==2){
			int x;cin>>x;
			seg.ch(l,r,&N::add,x);
		}else{
			print(seg.get(l,r,&N::gets,[](int x,int y){return x+y;},int(0)));
		}
	}
}

