#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
int k,p,q,m;
typedef long long int64;

scanf("%d",&k);
while (k--) {
scanf("%d %d %d",&p,&q,&m);
if (p>q) swap(p,q);
int r=1;
for(int i=0;i<p;i++){
  if((i+q)%p){
    int s=(i+q)/p+1;
    r=(int64)r*s%m;
  }
}
printf("%d\n",r);
}

return 0;
}
