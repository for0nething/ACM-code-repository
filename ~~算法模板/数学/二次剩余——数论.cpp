#define ull unsigned long long
#define ll long long
#define N 100005
namespace random_gen{
	ull r=0x1234567890ABCDEF;
	ull f(){
		r=r*0x234567890FEDBCA1+0xABCFED0987654123;
		return r=r>>29|r<<35;
	}
}
namespace numbertheory{
	ll mulmod(ll a,ll b,ll p){
		ll s=0;
		while(b){
			if(b&1) s=(s+a)%p;
			b>>=1;a=(a+a)%p;
		}
		return s;
	}
	ll powmod(ll a,ll b,ll p){
		ll s=1;
		while(b){
			if(b&1) s=mulmod(s,a,p);
			b>>=1;a=mulmod(a,a,p);
		}
		return s;
	}
	ll Legendre(ll a,ll p){
		return powmod(a,p-1>>1,p);
	}
	namespace fieldextension{
		ll d,p;
		struct num{
			ll x,y;
		};
		num operator*(num a,num b){
			return (num){(mulmod(a.x,b.x,p)+mulmod(mulmod(a.y,b.y,p),d,p))%p,(mulmod(a.x,b.y,p)+mulmod(a.y,b.x,p))%p};
		}
		num operator^(num a,ll b){
			num s=(num){1,0};
			while(b){
				if(b&1) s=s*a;
				b>>=1;a=a*a;
			}
			return s;
		}
	}
	ll quadratic_equation(ll n,ll p){
		if(!n) return 0;
		if(p==2) return 1;
		if(Legendre(n,p)==p-1) return -1;
		ll a,w;
		while(1){
			a=random_gen::f()%p;
			w=(mulmod(a,a,p)-n+p)%p;
			//printf("%lld %lld\n",a,w);
			if(Legendre(w,p)==p-1){
				fieldextension::d=w;
				fieldextension::p=p;
				return ((fieldextension::num){a,1}^p+1>>1).x;
			}
		}
	}
}
