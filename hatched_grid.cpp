#include<iostream>
using namespace std;
const int W=47;
const int H=43;
int sum=0;
int cnt[W+1][H+1];
int main(){
  cnt[1][1]=1;
  for(int h=1;h<=H;h++)
    cnt[1][h]=h*(h+1)/2 + h-1;
  for(int w=2;w<=W;w++)
    for(int h=1;h<=H;h++){
      cnt[w][h]=cnt[w-1][h];
      cnt[w][h]+=w*h*(h+1)/2;
      for(int x=1;x<=2*w && x<=2*h;x++)
        for(int y=1;x+y<=2*w && x+y<=2*h;y++){
          int f=(x+1)/2;
          int t=h-(y+1)/2;
          if(f<=t)
            cnt[w][h]+=t-f+1;
        }
      for(int x=1;x<=2*w && x<=2*h;x++)
        for(int y=1;x+y<=2*w-1 && x+y<=2*h;y++){
          int f=(x)/2;
          int t=h-1-(y)/2;
          if(f<=t)
            cnt[w][h]+=t-f+1;
        }
    }

  for(int w=1;w<=W;w++)
    for(int h=1;h<=H;h++){
      cout << w << " x " << h << " -> " << cnt[w][h] << endl;
      sum+=cnt[w][h];
    }

  cout << sum << endl;
  system("PAUSE");
  

}
