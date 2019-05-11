#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <bitset>
#include <utility>
#include <complex>
#include <assert.h>
#include <limits.h>
#include <iomanip>
//#include <unordered_map>
//#include <unordered_set>
//#include <bits/stdc++.h>
using namespace std;


#define rank rankk
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xo(a,b) ((b)&1?(a):0)
#define fi first
#define se second
#define tm tmp
//#define LL ll
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
typedef pair<ll,int> pli;
typedef pair<int,ll>pil;
typedef pair<ll,ll> pll;


const int INF=0x3f3f3f3f;
//const ll INFF=1200000000000000000ll;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
//const ll INFF=1e14+5;
const int MAX=2e5+5;
const int MOD=1e9+7;
//int MOD;
//const double pi=acos(-1.0);
//#define double long double
//#define ls T[k].l
//#define rs T[k].r
//const long double eps=1e-13;
//const double pi=acos(-1);
//#define double long double
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//#define double long double
template<class T> inline
void read(T& num) {
    bool start=false,neg=false;
    char c;
    num=0;
    while((c=getchar())!=EOF) {
        if(c=='-') start=neg=true;
        else if(c>='0' && c<='9') {
            start=true;
            num=num*10+c-'0';
        } else if(start) break;
    }
    if(neg) num=-num;
}
inline int powMM(int a,int b,int M){
    int ret=1;
    a%=M;
    while (b){
        if (b&1) ret=1LL*ret*a%M;
        b>>=1;
        a=1LL*a*a%M;
    }
    return ret;
}
namespace{
//inline int add(int x,int y){x%=MOD;y%=MOD;return (1LL*x+y)%MOD;}
inline int add(int x,int y){x+=y;if(x>=MOD)x-=MOD;return x;}
inline void addi(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
//inline void addi(int &x,int y){y%=MOD;x+=y;if(x>=MOD)x-=MOD;}
//inline int mul(int x,int y){return 1LL*x*y%MOD;}
inline int mul(int x,int y){ll re=1LL*x*y;if(re>=MOD)re%=MOD;return re;}
//inline void addi(int &x,int y){x%=MOD;y%=MOD;(x+=y)%=MOD;}
//inline void muli(int &x,int y){x%=MOD;y%=MOD;x=1LL*x*y%MOD;if(x<0)x+=MOD;}
inline void muli(int &x,int y){x=1LL*x*y%MOD;}
inline int sub(int x,int y){int res=x-y;if(res<0)res+=MOD;return res;}
inline void subi(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int half(int x){return x&1?(x+MOD)>>1:x>>1;}
//inline void mod(int &x){if(x<0){x%=MOD;x=(x+MOD)%MOD;}}

//ll mul(ll a , ll b,ll Q){
//    return (a * b - (ll) ((long double)a * b / Q) * Q) % Q;
//}
}
//#define debug
//clock_t t1 = clock();
//fprintf(stderr, "%ld ms\n", clock() - t1);

int t;
const double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}
struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {}
    void input() {
        scanf("%lf%lf",&x,&y);
    }
    bool operator < (const Point& R) const {
        if (dcmp(x - R.x) == 0)
            return dcmp(y - R.y) < 0;
        return dcmp(x - R.x) < 0;
    }
    bool operator == (const Point& R) const {
        return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
    }
    Point operator + (const Point& R) const {
        return Point(x + R.x , y + R.y);
    }
    Point operator - (const Point& R) const {
        return Point(x - R.x , y - R.y);
    }
    Point operator * (const double& R) const {
        return Point(x * R , y * R);
    }
    Point operator / (const double& R) const {
        return Point(x / R , y / R);
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    double angle() {
        return atan2(y , x);
    }
};
// 两个向量的夹角，不分正负[0,pi)
double Angle(Point A , Point B) {
    return acos((A % B) / A.len() / B.len());
}
// 逆时针旋转
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}
struct Circle{
    Point O;
    double r;
    Circle(){}
    Circle(Point _O,double _r){
        O=_O,r=_r;
    }
    Point point(double arc){//某个角度的点
        return Point(O.x+cos(arc)*r,O.y+sin(arc)*r);
    }
    void input(){
        O.input(),scanf("%lf",&r);
    }

    double cdis(Point a,Point b){//两点在弧上的距离
        a=a-O;b=b-O;
        double z=Angle(a,b);
        return r*z;
    }
    double getarc(Point a){
        a=a-O;
        double re=acos(a.x/r);
        if(a.y<0)re=2*pi-re;
        return re;
    }
};
int getTangents(Point P, Circle C, vector<Point>& sol) {
    Point u = C.O - P;
    double dist = u.len();
    if(dist < C.r) return 0;
    if(dcmp(dist - C.r) == 0) {
        sol.push_back(Rotate(u, pi / 2));
        return 1;
    } else {
        double ang = asin(C.r / dist);
        sol.push_back(Rotate(u, +ang));
        sol.push_back(Rotate(u, -ang));
        return 2;
    }
}
// 返回点在直线上的投影
Point GetLineProjection(Point P , Point A , Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}
Point X,Y;

vector<Point>qie[5];
vector<Point>pts[5];
vector<double>ac[5];
Circle cir;
Point liml,limr;
double l,r,mid;
int main(){
    read(t);
    while(t--){
        X.input();Y.input();
        cir.input();
        qie[0].clear();qie[1].clear();
        pts[0].clear();pts[1].clear();
        ac[0].clear();ac[1].clear();
        int qcnt1=getTangents(X,cir,qie[0]);
        int qcnt2=getTangents(Y,cir,qie[1]);
        for(Point p:qie[0])
            pts[0].pb(GetLineProjection(cir.O,X,X+p));
        for(Point p:qie[1])
            pts[1].pb(GetLineProjection(cir.O,Y,Y+p));
        double ans=INFF;
        //切+弧
        for(Point p1:pts[0])
            for(Point p2:pts[1]){
                ans=min((X-p1).len()+(Y-p2).len()+cir.cdis(p1,p2),ans );
            }

        //两段距离
        if(qcnt1==1&&qcnt2==1){//两个点
            if(dcmp(pts[1][0].x-pts[0][0].x)==0&&dcmp(pts[1][0].y-pts[0][0].y)==0)
                ans=min(cir.cdis(pts[0][0],pts[1][0]),ans);
        }
        else if(qcnt1==1||qcnt2==1){//一段弧 一个点
//            cout<<"ok"<<endl;
            if(qcnt2==1){
                swap(pts[0],pts[1]);//可能有误
                swap(X,Y);
            }
            if(((pts[1][1]-cir.O)^(pts[1][0]-cir.O))>0)swap(pts[1][1],pts[1][0]);//0到1 逆时针
            if(((pts[1][1]-pts[0][0])^(pts[1][0]-pts[0][0]))>=0.0 )//在弧上
                ans=min(ans,(pts[0][0]-X).len()+(pts[0][0]-Y).len() );
        }
        else{//两段弧
            if(((pts[1][1]-cir.O)^(pts[1][0]-cir.O))>0)swap(pts[1][1],pts[1][0]);
            if(((pts[0][1]-cir.O)^(pts[0][0]-cir.O))>0)swap(pts[0][1],pts[0][0]);

            Point A1=pts[0][0]-cir.O,A2=pts[0][1]-cir.O;
            Point B1=pts[1][0]-cir.O,B2=pts[1][1]-cir.O;

            if((A1^B1)<0){
                swap(pts[0][0],pts[1][0]);swap(pts[0][1],pts[1][1]);
                swap(A1,B1);swap(A2,B2);
            }

            liml=pts[1][0];

            /*
            if((A2^B2)>=0)limr=A2;
            else limr=B2;
                */
            if((A2^B2)>=0)limr=pts[0][1];
            else limr=pts[1][1];
//            if(1)
            if(dcmp(A2^B1)<=0)
            {
            int z=cir.r*cir.r;
            double alim=acos((B1%(limr-cir.O))/z);
            int cnt=100;
            l=0;r=alim;
//            cout<<"nope!!"<<endl;
            while(cnt--){
                double leng=(r-l)/3.0;
                double arc1=l+leng,arc2=r-leng;
//                cout<<"leng="<<leng<<endl;
                Point tem1=Rotate(liml-cir.O,arc1);
                Point tem2=Rotate(limr-cir.O,-arc1);
                tem1=tem1+cir.O;tem2=tem2+cir.O;
                double ans1=(tem1-X).len()+(tem1-Y).len();
                double ans2=(tem2-X).len()+(tem2-Y).len();
                if(dcmp(ans1-ans2)<=0){
                    ans=min(ans,ans1);
                    limr=tem2;
                }
                else{
                    ans=min(ans,ans2);
                    liml=tem1;
                }

            }
            }

        }
        //公共部分的距离和

        printf("%.3f\n",ans);
    }
    return 0;
}

/*
5
-5 0 5 0 0 0 3
-1 0 1 0 0 0 1

-1 0 1 0 0 -1 1
*/
