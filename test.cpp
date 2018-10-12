#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;

int prime[maxn],pcnt;
bool notp[maxn];


bool isprime(LL x){
	for(LL i=2;i*i<=x;i++)
		if(x%i==0)
			return false;
	return true;
}
void sieve(){
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			prime[++pcnt]=i;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<maxn;j++){
			notp[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
LL pw(LL x,LL k,LL p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}
LL inv(LL x,LL p){
	return pw(x,p-2,p);
}
int k=0;
LL M,m[1111],w[111];

LL CM;
LL mo;


LL C(LL x){
	LL ans=0;
	ans=x*CM%mo*inv(M%mo,mo)%mo;
	for(int i=1;i<=k;i++){
		LL xi=x%m[i];
		ans-=xi*((w[i]%mo+mo))%mo*inv(m[i],mo)%mo;
		ans+=mo;
		ans%=mo;
	}
	return ans%mo;	
}
LL sumw=0;
bool check(LL x){
	LL Cx=C(x);

	if(x<M/2){
		if(Cx<CM/2 || Cx>CM+sumw)
			return true;
		return false;
	}else{	
		if(Cx<CM/2 || Cx>CM+sumw)
			return false;
		return true;
	}
}

int main(){
	sieve();
	M=1;
	sumw=0;
	for(int i=1;M<INT_MAX;i++){
		M*=prime[i];
		m[++k]=prime[i];
		printf("m[%d]=%d\n",i,prime[i]);
	}

	LL sum=accumulate(m+1,m+1+k,0);
	CM=sum+1;
	while(!isprime(CM))
		CM++;
	
	cout<<"CM is "<<CM<<endl;
	for(int i=1;i<=k;i++){
		LL Mi=M/m[i];
		w[i]=CM*inv(Mi,m[i])%m[i];
		if(m[i]-w[i]<w[i])
			w[i]-=m[i];
		sumw+=abs(w[i]);
		printf("w[%d]=%lld\n",i,w[i]);
	}
	mo=CM+sumw*2+1;
	while(!isprime(mo))
		mo++;
	cout<<"mo is "<<mo<<endl;
	cerr<<sumw<<endl;
	cerr<<M<<endl;
	for(LL i=M-1;i>=M-100;i--)
		cout<<i<<" : "<<C(i)<<endl;

	for(int i=1;i<=100;i++)
		cout<<i<<" : "<<C(i)<<endl;
	LL first=0,last=0;
	for(LL i=1;i<M;i+=1){
		if(!check(i)){
			first=i;
			cerr<<"first break on "<<i<<endl;
			break;
		}
		if(i%10000==1)
			cerr<<"pass test "<<i<<endl;
	}
//	return 0;
	for(LL i=M-1;i>0;i-=1){
		if(!check(i)){
			last=i;
			cerr<<"last break on "<<i<<endl;
			break;
		}
		if(i%10000==(M-1)%1000000)
			cerr<<"pass test "<<i<<endl;
	}
	cout<<M<<endl;
	cout<<CM<<" "<<mo<<endl;
	cout<<first<<" "<<last-M<<endl;

	return 0;
}
