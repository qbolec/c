#include<cstdio>

template<class T>
struct List{
  virtual T Head()=0;
  virtual List<T> * Tail()=0;
};
template<class T>
struct Nil:List<T>{
  T Head(){throw;}
  List<T>* Tail(){throw;}
};
template<class T>
struct Cons:List<T>{
  T head;
  List<T> * tail;
  Cons(T head,List<T> * tail):head(head),tail(tail){}
  T Head(){return head;}
  List<T>* Tail(){return tail;}
};

int main(){
  List<int> * t=new Cons<int>(1 ,new Nil<int>());
  List<int> * loop=new Cons<int>(1 ,loop);
}
