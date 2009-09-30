#include<cstdio>
#include<vector>
using namespace std;
int n;
vector<int> a;
vector<int> output;
int main(){
  scanf("%d",&n);
  a.resize(n);
  output.resize(n*2);
  int p=n*2;
  
  for(int i=0;i<n;i++)
    scanf("%d",&a[i]);
  for(int t=2*n;t--;){
    int l=0;
    while(a[l] && l<n)
      l++;
    if(l<n){
      for(int i=0;i<l;i++)
        a[i]--;
      a[l]=-666;  
      output[t]=l+1;      
    }else{
      do{
        p--;
      }while(output[p]<0 && p>t);      
      if(p>t){
        output[t]=-output[p];
        for(int i=output[p];i<n;i++)
          a[i]--;      
      }else{
        printf("NO\n");
        return 0;
      }
    }
    printf("%d\n",output[t]);      
  }
  return 0;
}
