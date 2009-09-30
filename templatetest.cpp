template<class T,int MAXSIZE ,int cmp(const T&a, const T&b) >
  class kopiec{
    T tab[MAXSIZE];
    public : kopiec(){
    }
  };
  
  
struct zad{
  int p,q,r;
};  
int cmpP(const zad &a,const zad &b){
  return a.p-b.p;
}
int cmpQ(const zad &a,const zad &b){
  return b.q-a.q;
}
typedef kopiec<zad,1000,cmpQ>kopiecQ;
typedef kopiec<zad,1000,cmpP>kopiecP;
int main(){
  kopiecQ kq;
  kopiecP kp;
  return 0;
}
