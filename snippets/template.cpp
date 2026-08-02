#include <bits/stdc++.h>
using namespace std;
static const int MOD = 998244353;
template<class T> constexpr T INF=numeric_limits<T>::max()/32*15+208;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
constexpr int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},dx8[8]={1,1,0,-1,-1,-1,0,1},dy8[8]={0,1,1,1,0,-1,-1,-1};
template<class T> T ifloor(T x,T y){return x/y-(x%y?(x<0)^(y<0):0);}
template<class T> T iceil(T x,T y){return x/y+(x%y?(x>=0)^(y<0):0);}
template<class T> bool chmax(T&a,T b){return a<b?(a=b,1):0;}
template<class T> bool chmin(T&a,T b){return a>b?(a=b,1):0;}

extern "C" int fileno(FILE *); extern "C" int isatty(int);
template<class T,class=void> struct has_fio_r:false_type{};
template<class T> struct has_fio_r<T,void_t<decltype(declval<T&>().begin()),decltype(declval<T&>().end())>>:true_type{};
template<class T,class=void> struct has_fio_v:false_type{};
template<class T> struct has_fio_v<T,void_t<decltype(declval<const T&>().value())>>:true_type{};
template<class T,class=void> struct has_fio_a:false_type{};
template<class T> struct has_fio_a<T,void_t<decltype(declval<T&>().assign(declval<const string&>()))>>:true_type{};
template<class T,class=void> struct has_fio_s:false_type{};
template<class T> struct has_fio_s<T,void_t<decltype(declval<const T&>().to_string())>>:true_type{};
template<bool B,class U=int> using en_if_t=enable_if_t<B,U>;
template<class T> constexpr bool is_rng_v=has_fio_r<T>::value&&!is_same_v<decay_t<T>,string>;
template<class T> constexpr bool has_val_v=!is_integral_v<T>&&!is_rng_v<T>&&!is_same_v<decay_t<T>,string>&&has_fio_v<T>::value;
template<class T> constexpr bool has_asn_v=!is_integral_v<T>&&!is_rng_v<T>&&!is_same_v<decay_t<T>,string>&&!has_fio_v<T>::value&&has_fio_a<T>::value;
template<class T> constexpr bool has_str_v=!is_integral_v<T>&&!is_rng_v<T>&&!is_same_v<decay_t<T>,string>&&!has_fio_v<T>::value&&has_fio_s<T>::value;
struct FastIOTb{char n[40000]{};constexpr FastIOTb(){for(int i=0;i<10000;++i){int x=i;for(int j=3;j>=0;--j)n[i*4+j]=char('0'+x%10),x/=10;}}};
struct Scanner{
    static constexpr int B=1<<17,O=64; char b[B+1]; int I=0,S=0; bool o=isatty(fileno(stdin)); string nt;
    inline void ld(){int l=S-I;memmove(b,b+I,l);S=l+(o?(fgets(b+l,B+1-l,stdin)?(int)strlen(b+l):0):(int)fread(b+l,1,B-l,stdin));I=0;b[S]=0;}
    inline void nd(){if(I+(o?1:O)>S) ld();} inline void bk(){for(nd();b[I]&&b[I]<=' ';++I)nd();} inline char skip(){bk(); return b[I++];}
    template<class T,en_if_t<is_integral_v<T>,int> = 0> void read(T&x){using V=conditional_t<is_same_v<T,bool>,uint,T>;using U=make_unsigned_t<V>;
        char c=skip();bool g=0;if constexpr(is_signed_v<T>)if(c=='-')g=1,nd(),c=b[I++];U y=0;
        while(c>='0')y=U(y*10+(c&15)),nd(),c=b[I++];
        if constexpr(is_signed_v<T>){if(g&&y){x=-static_cast<T>(y-1);--x;return;}}x=static_cast<T>(y);}
    void read(double&x){read(nt);const char*f=nt.data(),*l=f+nt.size();auto r=from_chars(f,l,x);if(r.ec!=errc{}||r.ptr!=l)__builtin_trap();}
    template<class T,en_if_t<has_val_v<T>,int> = 0> void read(T&x){ll v; read(v); x=T(v);}
    template<class T,en_if_t<has_asn_v<T>,int> = 0> void read(T&x){string s;read(s);if(!x.assign(s))__builtin_trap();}
    template<class H,class N,class... T> void read(H&h,N&n,T&...t){read(h); read(n,t...);} template<class T,class U> void read(pair<T,U>&p){read(p.first,p.second);}
    template<class T,en_if_t<is_rng_v<T>,int> = 0> void read(T&a){for(auto&x:a) read(x);} void read(char &c){c=skip();}
    void read(string &s){s.clear();bk();for(;;){int l=I;while(I<S&&b[I]>' ')++I;s.append(b+l,I-l);if(I<S){++I;break;}ld();if(!S) break;}}
} din; template<class T> Scanner& operator>>(Scanner&in,T&x){ in.read(x); return in; }
struct Printer{
    static constexpr int B=1<<17,O=64,P=15;char b[B];int I=0;bool o=isatty(fileno(stdout));string nb;inline static constexpr FastIOTb Tb{};
    ~Printer(){flush();} inline void flush(){if(I) fwrite(b,1,I,stdout),I=0; }
    inline void pc(char c){if(I>B-O) flush(); b[I++]=c; if(o&&c=='\n') flush(); }
    inline void pr(const char*s,size_t n){while(n){if(I==B)flush();size_t k=min(n,(size_t)(B-I));memcpy(b+I,s,k);I+=(int)k;s+=k;n-=k;}}
    void print(bool x){pc(char('0'+x));}void print(char c){pc(c);}void print(const char* s){pr(s,strlen(s));}void print(const string&s){pr(s.data(),s.size());}
    inline char* wt(char*q,uint x){if(x>=1000)return memcpy(q,Tb.n+(x<<2),4),(q+4);if(x>=100)return memcpy(q,Tb.n+(x<<2)+1,3),(q+3);
        if(x>=10){uint y=(x*205)>>11;*q++=char('0'+y);*q++=char('0'+x-y*10);return q;}*q=char('0'+x);return q+1;}
    inline void w4(char*q,uint x){memcpy(q,Tb.n+(x<<2),4);}inline void w8(char*q,uint x){uint y=x/10000;w4(q,y);w4(q+4,x-y*10000);}
    inline char* w32(char*q,uint x){if(x>=100000000){uint y=x/100000000,z=x-y*100000000;q=wt(q,y);w8(q,z);return q+8;}
        if(x>=10000){uint y=x/10000,z=x-y*10000;q=wt(q,y);w4(q,z);return q+4;}return wt(q,x);}
    inline char* w64(char*q,ull x){if(x<=0xffffffffULL)return w32(q,(uint)x);ull y=x/100000000;uint z=(uint)(x-y*100000000);
        if(y<=0xffffffffULL){q=w32(q,(uint)y);w8(q,z);return q+8;}uint t=(uint)(y/100000000),m=(uint)(y-(ull)t*100000000);q=w32(q,t);w8(q,m);w8(q+8,z);return q+16;}
    template<class T,en_if_t<is_integral_v<T>&& !is_same_v<T,bool>,int> = 0> void print(T x){ if(I>B-100) flush(); using U=make_unsigned_t<T>; U y;
        if constexpr(is_signed_v<T>){ if(x<0) b[I++]='-',y=U(0)-(U)x; else y=(U)x; } else y=x;
        if(!y){b[I++]='0';return;}char*q;
        if constexpr(sizeof(U)<=4)q=w32(b+I,(uint)y);else if constexpr(sizeof(U)<=8)q=w64(b+I,(ull)y);
        else{char W[3*sizeof(U)];int p=sizeof(W);while(y>=10000)p-=4,memcpy(W+p,Tb.n+(y%10000)*4,4),y/=10000;q=wt(b+I,(uint)y);memcpy(q,W+p,sizeof(W)-p);q+=sizeof(W)-p;}I=(int)(q-b);
    }
    void print_fixed(double x,int p=P){if(p<0)__builtin_trap();size_t z=(size_t)p+512;if(nb.size()<z)nb.resize(z);for(;;){char*f=nb.data(),*l=f+nb.size();auto r=to_chars(f,l,x,chars_format::fixed,p);
        if(r.ec==errc{})return pr(f,r.ptr-f);
        if(r.ec!=errc::value_too_large){__builtin_trap();}z=nb.size()*2;if(z<=nb.size())__builtin_trap();nb.resize(z);}}
    void print(double x){print_fixed(x);}
    template<class T,en_if_t<has_val_v<T>,int> = 0> void print(const T&x){ print(x.value()); }
    template<class T,en_if_t<has_str_v<T>,int> = 0> void print(const T&x){ print(x.to_string()); }
    template<class T,en_if_t<is_rng_v<T>,int> = 0> void print(const T&a){ bool f=0; for(auto&&x:a){ if(f) pc(' '); f=1; print(x); } }
    void puts(){ pc('\n'); } template<class T> void puts(const T&x){ print(x); pc('\n'); }
    template<class H,class... T> void puts(const H&h,const T&...t){ print(h); ((pc(' '),print(t)),...); pc('\n'); }
    void puts_fixed(double x,int p=P){print_fixed(x,p);pc('\n');}
} dout; template<class T> Printer& operator<<(Printer&out,const T&x){ out.print(x); return out; }

int main(){
    return 0;
}
