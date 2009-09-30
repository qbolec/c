template<class dana>
void qsort(dana * first,dana * afterLast){
  dana * end=afterLast,*j;
  while(1){
    if(afterLast-first<6){
      for(dana * i=first+1;i<afterLast;i++){
        dana x=*i;
        for(j=i-1;*j>=x;j--)
          j[1]=j[0];
        j[1]=x;
      }
      first=afterLast;
      if(first==end)
        return;
      while(*afterLast++>=first[-1]);
      dana tmp=first[-1];
      first[-1]=afterLast[-1];
      afterLast[-1]=tmp;
    }else{
      dana x=afterLast[-1];
      dana * left=first;
      dana * right=afterLast-2;
      while(1){
        while(*left<x)left++;
        while(right>=first && *right>=x)right--;
        if(left>=right)break;
        dana tmp=*left;
        *left++=*right;
        *right=tmp;
      }
      if(left==first){
        dana * write=afterLast-1;
        for(dana * p=afterLast-1;p>=first;p--)
          if(*p>x)
            *write--=*p;
        while(first<=write)
          *first++=x;
      }else{
        dana * biggest=first;
        for(dana * p=first+1;p<left;p++)
          if(*p>*biggest)
            biggest=p;
        dana tmp=*biggest;
        *biggest=afterLast[-1];
        afterLast[-1]=tmp;
        afterLast=left;
      }
    }
  }
}
#include<iostream.h>
int main(){
  int mojeLiczby[12]={1,4,5,3,2,11,12,11,10,2,7,5};
  qsort(mojeLiczby,mojeLiczby+12);
  for(int i=0;i<12;i++)
    cout << mojeLiczby[i] << ' ';
  return 0;
}
