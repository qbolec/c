#include<vector>
#include<cstdio>
using namespace std;
vector< vector<int> > trojki[200*200*3+1];
int main(){
  int n;
  scanf("%d",&n);
  for(int a=1;a<=n;a++)
    for(int b=a;b<=n;b++)
      for(int c=b;c<=n;c++){
        vector<int> s;
        s.push_back(a);
        s.push_back(b);
        s.push_back(c);
        trojki[a*a+b*b+c*c].push_back(s);
      }
  for(int s=3;s<=n*n*3;s++)
    if(trojki[s].size()>1){
      for(int i=0;i<trojki[s].size();i++)
        for(int j=i+1;j<trojki[s].size();j++)
          printf("%d = %d*%d + %d*%d + %d*%d = %d*%d + %d*%d + %d*%d\n",s,
            trojki[s][i][0],trojki[s][i][0],
            trojki[s][i][1],trojki[s][i][1],
            trojki[s][i][2],trojki[s][i][2],
            trojki[s][j][0],trojki[s][j][0],
            trojki[s][j][1],trojki[s][j][1],
            trojki[s][j][2],trojki[s][j][2]
          );
    } 
}
