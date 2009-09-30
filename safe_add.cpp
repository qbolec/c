/*
  requires: minimal<= x,y <= maximal , maximal>0 , minimal <=0 
  returns : x+y if  minimal<= x+y <= maximal 
  otherwise: throws "Overflow"
*/

template<typename T>
T safe_add (T & x, T & y,const T & minimal,const T & maximal) throw(const char *) {
  if(x>0){
    if( maximal-x < y)
      throw "Overflow";
  }else if(y>0){
     if( maximal-y < x)
      throw "Overflow";
  }else{
    if( minimal-y > x)
      throw "Underflow";
  }  
  return x+y;
}

/*
  requires: minimal<= x,y <= maximal , maximal>0 , minimal <=0 
  returns : x-y if  minimal<= x-y <= maximal 
  otherwise: throws "Overflow"
*/

template<typename T>
T safe_subtract (T & x, T & y,const T & minimal,const T & maximal) throw(const char *) {
  if(y<0){
    if( x> maximal+y)
      throw "Overflow";    
  }else if(x<0){
    if( x< minimal+y)
      throw "Underflow";    
  }else{
    if( x< minimal+y)
      throw "Underflow";        
  }    
  return x-y;
}

template<typename T> T minimal_signed(){return ((T)1)<<((sizeof(T)*8)-1);}
template<typename T> T maximal_signed(){return ~ minimal_signed<T>();}
template<typename T> T minimal_unsigned(){return (T)0;}
template<typename T> T maximal_unsigned(){return ~minimal_unsigned<T>();}
template<typename T>
T safe_add_signed(T & x, T & y){return safe_add(x,y,minimal_signed<T>(),maximal_signed<T>());}
template<typename T>
T safe_add_unsigned(T & x, T & y){return safe_add(x,y,minimal_unsigned<T>(),maximal_unsigned<T>());}
template<typename T>
T safe_subtract_signed(T & x, T & y){return safe_subtract(x,y,minimal_signed<T>(),maximal_signed<T>());}
template<typename T>
T safe_subtract_unsigned(T & x, T & y){return safe_subtract(x,y,minimal_unsigned<T>(),maximal_unsigned<T>());}


#include<cstdio>
using namespace std;
int main(){
  int x;
  int y;
  scanf("%d %d",&x,&y);
  try{
    printf("%d\n",safe_subtract(x,y,7,28));
  }catch(const char * err){
    printf("Error: %s\n",err);
  }
}
