#include<vector>
#include<cstdio>
using namespace std;
struct T{int a,b,c;};
int main(){
  vector<int> v;
  for(int i=0;i<1000;i++){
    v.push_back(i);
    printf("%d %d %d\n",((T*)&v)->a,((T*)&v)->b-((T*)&v)->a,((T*)&v)->c-((T*)&v)->a);
  }
}
