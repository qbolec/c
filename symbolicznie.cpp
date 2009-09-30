#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>
using namespace std;
struct p_term;
typedef vector<p_term> wektor;
typedef vector<wektor> macierz;
struct term{
  virtual void output(ostream & o)const=0;
  virtual vector<vector<p_term> > normalize()const =0;
  virtual bool jest_zlozony()const{
    return true;
  }
  virtual bool jest_stala()const{
    return false;
  }
  virtual bool jest_zmienna()const{
    return false;
  }
  virtual p_term mul(double x)const =0 ;
  string to_str()const;
};

struct p_term{
  const term * t;
  const term * operator -> ()const{
    return t;
  }
  p_term(const term *t):t(t){}
  p_term(const double x);
};
bool operator ==(const p_term &a,const p_term &b){
  return a->to_str()==b->to_str();
}
bool operator <(const p_term &a,const p_term &b){
  return a->to_str()<b->to_str();
}
vector<p_term> skaluj(const wektor &a,const double f){
  vector<p_term> r;
  r.reserve(a.size());
  for(int i=0;i<(int)a.size();i++)
    r.push_back(a[i]->mul(f));
  return r;
}

ostream & operator << (ostream & o,const p_term t){
  t->output(o);
  return o;
}
string term::to_str()const{
  ostringstream A;
  A<<p_term(this);
  return A.str();
}

struct iloczyn:term{
  const p_term a,b;
  iloczyn(const p_term a,const p_term b):a(a),b(b){}
  virtual vector<vector<p_term> > normalize()const{
    vector<vector<p_term> > A=a->normalize();
    vector<vector<p_term> > B=b->normalize();
    vector<vector<p_term> > res;
    for(int i=0;i<(int)A.size();i++)
      for(int j=0;j<(int)B.size();j++){
        res.push_back(A[i]);
        res.back().insert(res.back().end(),B[j].begin(),B[j].end());
      }
    return res;
  }
  virtual p_term mul(double x)const{
    return new iloczyn(a->mul(x),b);
  }
  virtual void output(ostream & o)const{
    if(a->jest_zlozony())
      o << '(' << a << ')';
    else
      o << a;
//    o << '*';
    if(b->jest_zlozony())
      o << '(' << b << ')';
    else
      o << b;
  }
};
struct stala:term{
  const double x;
  stala(double x):x(x){}
  virtual vector<vector<p_term> > normalize()const{
    vector<p_term> s;
    s.push_back(this);
    vector<vector<p_term> > res;
    res.push_back(s);
    return res;
  }
  virtual bool jest_zlozony()const{
    return false;
  }
  virtual bool jest_stala()const{
    return true;
  }
  virtual p_term mul(double x)const{
    return new stala(this->x*x);
  }
  virtual void output(ostream & o)const{
    o << x ;
  }
};
p_term::p_term(const double x):t(new stala(x)){}
const p_term zero=new stala(0);
const p_term jeden=new stala(1);
const p_term minus_jeden=new stala(-1);
const p_term dwa=new stala(2);

struct zmienna:term{
  const string v;
  const double k;
  zmienna(const string v,const double k=1.0):v(v),k(k){}
  virtual vector<vector<p_term> > normalize()const{
    vector<p_term> s;
    s.push_back(this);
    vector<vector<p_term> > res;
    res.push_back(s);
    return res;
  }
  virtual bool jest_zmienna()const{
    return true;
  }
  virtual bool jest_zlozony()const{
    return false;
  }
  virtual p_term mul(double x)const{
    return new iloczyn(new stala(x),this);
  }
  virtual void output(ostream & o)const{
    o << v ;
    if(k!=1)
      o<< '^' << k ;
  }
};
struct suma:term{
  const p_term a,b;
  suma(const p_term a,const p_term b):a(a),b(b){}
  virtual vector<vector<p_term> > normalize()const{
    vector<vector<p_term> > A=a->normalize();
    vector<vector<p_term> > B=b->normalize();
    vector<vector<p_term> > res=A;
    res.insert(res.end(),B.begin(),B.end());
    return res;
  }

  virtual p_term mul(double x)const{
    return new suma(a->mul(x),b->mul(x));
  }
  virtual void output(ostream & o)const{
    o << a ;
    string B=b->to_str();
    if(B[0]=='-')
      o << B;
    else
      o << '+' << B;
  }
};
struct roznica:term{
  const p_term a,b;
  roznica(const p_term a,const p_term b):a(a),b(b){}
  virtual vector<vector<p_term> > normalize()const{
    vector<vector<p_term> > A=a->normalize();
    vector<vector<p_term> > B=b->mul(-1)->normalize();
    vector<vector<p_term> > res=A;
    res.insert(res.end(),B.begin(),B.end());
    return res;
  }
  virtual p_term mul(double x)const{
    return new roznica(a->mul(x),b->mul(x));
  }
  virtual void output(ostream & o)const{
    o << a ;
    if(b->jest_zlozony())
      o << "-(" << b << ')';
    else{
      string B=b->to_str();
      if(B[0]=='-')
        o << '+' << B.substr(1);
      else
        o << '-' <<  B;
    }
  }
};
p_term operator + (p_term a,p_term b){
  if(a->jest_stala()){
    if(((stala*)a.t)->x==0)
      return b;
    if(b->jest_stala())
      return new stala(((stala*)a.t)->x+((stala*)b.t)->x);
  }else if(b->jest_stala()){
    if(((stala*)b.t)->x==0)
      return a;
  }
  return new suma(a,b);
}
p_term operator - (p_term a,p_term b){
  if(a->jest_stala()){
    if(((stala*)a.t)->x==0)
      return b->mul(-1);
    if(b->jest_stala())
      return new stala(((stala*)a.t)->x-((stala*)b.t)->x);
  }else if(b->jest_stala()){
    if(((stala*)b.t)->x==0)
      return a;
  }
  return new roznica(a,b);
}
p_term operator * (const p_term a,const p_term b){
  if(a->jest_stala()){
    if(((stala*)a.t)->x==0)
      return a;
    if(((stala*)a.t)->x==1)
      return b;

    return b->mul(((stala*)a.t)->x);
  }else if(b->jest_stala()){
    if(((stala*)b.t)->x==0)
      return b;
    if(((stala*)b.t)->x==1)
      return a;
    return a->mul(((stala*)b.t)->x);
  }
  if(a->jest_zmienna() && b->jest_zmienna()){
    if(((zmienna*)a.t)->v==((zmienna*)b.t)->v)
      return new zmienna(((zmienna*)a.t)->v,((zmienna*)a.t)->k+((zmienna*)b.t)->k);
  }
  return new iloczyn(a,b);
}

vector<p_term> sumuj(const vector<p_term> &a,const vector<p_term> &b){
  vector<p_term> r;
  r.reserve(a.size());
  for(int i=0;i<(int)a.size();i++)
    r.push_back(a[i]+b[i]);
  return r;
}
vector<p_term> skaluj(const vector<p_term> &a,const p_term f){
  vector<p_term> r;
  r.reserve(a.size());
  for(int i=0;i<(int)a.size();i++)
    r.push_back(a[i]*f);
  return r;
}
p_term SIGMA(const vector<p_term> &a){
  p_term res=zero;
  for(int i=0;i<(int)a.size();i++)
    res=res+a[i];
  return res;
}
p_term PI(const vector<p_term> &a){
  p_term res=jeden;
  for(int i=0;i<(int)a.size();i++)
    res=res*a[i];
  return res;
}

typedef pair<double,vector<p_term> > jednomian;
typedef pair<p_term,double> jednomian_wymnozony;
jednomian opt_mul(vector<p_term> &a){
  jednomian b;
  b.first=1.0;
  vector<p_term> d;
  for(int i=0;i<(int)a.size();i++)
    if(a[i]->jest_stala())
      b.first*= ((stala*)a[i].t)->x;
    else
      d.push_back(a[i]);
  sort(d.begin(),d.end());

  if(b.first==0){
    b.second.push_back(zero);
    return b;
  }

  for(int i=0;i<(int)d.size();){
    if(d[i]->jest_zmienna()){
      int cnt=1;
      const string v=((zmienna*)d[i].t)->v;
      double k=((zmienna*)d[i].t)->k;
      for(int j=i+1;j<(int)d.size()&& d[j]->jest_zmienna() && v==((zmienna*)d[j].t)->v;j++){
        cnt++;
        k+=((zmienna*)d[j].t)->k;
      }
      if(k!=0)
        b.second.push_back(new zmienna(v,k));
      i+=cnt;
    }else{//jesli nie jest zmienna, ani stala, ...to co tu robi??
      cout << "WTF:" << d[i] << endl;
      b.second.push_back(d[i]);
      i++;
    }
  }
  if(b.second.empty())
    b.second.push_back(jeden);

//  cout << "zwracam:" << endl;
//  for(int i=0;i<(int)b.second.size();i++)
//    cout << b.second[i] << endl;
//  cout << endl;
    
  return b;
}
vector<p_term> opt_sum(vector<jednomian_wymnozony> &a){
  sort(a.begin(),a.end());
  vector<p_term> b;
  for(int i=0;i<(int)a.size();){
    double cnt=a[i].second;
    int j;
    for(j=i+1;j<(int)a.size()&& a[i].first==a[j].first;j++)
      cnt+=a[j].second;
    if(cnt)
      b.push_back(cnt==1?a[i].first:a[i].first->mul(cnt));
    i=j;
  }
  return b;
}
p_term renormalize(p_term t){
  vector<vector<p_term> > tn=t->normalize();
  vector<jednomian_wymnozony> a;
  for(int i=0;i<(int)tn.size();i++){
    jednomian xyz=opt_mul(tn[i]);
    a.push_back( jednomian_wymnozony(PI(xyz.second),xyz.first) );
  }
  return SIGMA(opt_sum(a));
}
ostream & operator << (ostream & o,const vector<vector<p_term> > &A){
  if(A.empty())return o;
  cout << "\\begin{tabular}{";
  for(int i=0;i<(int)A[0].size();i++)
    cout << "r";
  cout << "}" << endl;

  for(int r=0;r<(int)A.size();r++){
    for(int c=0;c<(int)A[r].size();c++)
      cout << '$' << renormalize(A[r][c])  << '$' <<  (c==(int)A[r].size()-1?"\\\\": "&");
    cout << endl;
  }
  cout << "\\end{tabular}" << endl;
  return o;
}
macierz operator * (const macierz &A,const macierz &B){
  macierz C;
  for(int r=0;r<(int)A.size();r++){
    wektor row;
    for(int c=0;c<(int)B[0].size();c++){
      p_term x=zero;
      for(int i=0;i<(int)A[r].size();i++)
        x=x+A[r][i]*B[i][c];
      row.push_back(x);
    }
    C.push_back(row);
  }
  return C;
}
p_term det(const macierz & A){
  p_term det=zero;
  vector<int> p;
  for(int i=0;i<(int)A.size();i++)
    p.push_back(i);
  do{
    int znak=1;
    for(int i=p.size();i--;)
      for(int j=i;j--;)
        if(p[j]>p[i])
          znak*=-1;
    p_term iloczyn=jeden;
    for(int i=p.size();i--;)
      iloczyn=iloczyn*A[i][p[i]];
    if(znak==1)
      det=det+iloczyn;
    else
      det=det-iloczyn;
  }while(next_permutation(p.begin(),p.end()));
  return det;
}
wektor operator * (const macierz &A,wektor &v ){
  wektor r;
  for(int i=0;i<(int)A.size();i++){
    p_term sum=zero;
    for(int j=0;j<(int)v.size();j++)
      sum=sum+ A[i][j]*v[j];
    r.push_back(sum);
  }
  return r;
}
p_term eigenvalues_equation(const macierz &A,p_term zmienna){
  macierz B=A;
  for(int i=B.size();i--;)
    B[i][i]=B[i][i]-zmienna;
  return det(B);
}
p_term fixpoint(p_term t){
  p_term x=renormalize(t);
  while(!(x==t)){
    t=x;
    x=renormalize(t);
  }
  return x;
}
int main(){
  /*
  p_term a=new zmienna("a");
  p_term k=new stala(2);//zmienna("k");
  p_term e=new stala(exp(1));
  p_term jeden=new stala(1);
  
  cout << renormalize(
  (a-1)*(a-1)*(4-(2-a)*(2-a))-2*(2-a)-(2-a)*(2-a)
  )<<endl;
  */
  
  p_term x=new zmienna("x");
  p_term A=x;
  p_term B=zero;
  p_term O=x;
  for(int i=1;i<15;i++){
    cout << endl << "POZIOM: " << i << endl << endl;
    char viname[10];
    sprintf(viname,"v[%d]",i);

    if(i%2==1){
      //A+a>1.5(O+a*0.5)
      //a>O6-A4
      p_term a=6*O-4*A+1;
      cout << "a["<< i << "] = " << renormalize( a ) << endl;
      O=O+0.5*a;
      p_term vi=new zmienna(viname);
      A=A+ vi;
      B=B+ x+a-vi;
    }else{
      //B+a>1.5(O+a*0.5)
      //a>O6-B4
      p_term a=6*O-4*B+1;
      cout << "a["<< i << "] = " << renormalize(a) << endl;
      O=O+0.5*a;
      p_term vi=new zmienna(viname);
      B=B+ vi;
      A=A+ x+a-vi;
    }
    A=renormalize(A);
    B=renormalize(B);
    O=renormalize(O);
    cout << "OPT := " << renormalize(O) <<endl;
    cout << "1.5O:= " << renormalize(1.5*O) <<endl;
    cout << "  A := " << renormalize(A) << endl;
    cout << "  B := " << renormalize(B) << endl;
    cout << endl;
    cout << "A-1.5OPT := " << renormalize(A-1.5*O) << endl;
    cout << "B-1.5OPT := " << renormalize(B-1.5*O) << endl;
    cout << endl;
    cout << " A+B := " << renormalize(A+B) << endl;
    cout << "3OPT := " << renormalize(3*O) << endl;
    cout << "A+B-3OPT := " << renormalize(A+B-3*O) << endl;
    
  }
  
  
  system("PAUSE");

}
/*

  vector<vector<p_term> > A;
  p_term gamma=new zmienna("g");
  const int k=2;
  for(int i=0;i<k;i++){
    vector<p_term> row;
    row.reserve(k+2);
    for(int j=0;j<i;j++)
      row.push_back(zero);
    for(int j=i;j<k;j++)
      row.push_back(gamma);
    row.push_back(minus_jeden);
    row.push_back(zero);
    for(int j=0;j<i;j++)
      row=sumuj(row,skaluj(A[j],gamma));
    A.push_back(row);
  }
  vector<p_term> dwa_r_plus_dwa_row(k+2,zero);
  dwa_r_plus_dwa_row[k]=jeden;
  dwa_r_plus_dwa_row[k+1]=jeden;
  A.push_back(dwa_r_plus_dwa_row);
  vector<p_term> minus_dwa_row(k+2,zero);
  minus_dwa_row[k+1]=jeden;
  A.push_back(minus_dwa_row);
  cout << "macierz A:" <<endl;
  cout << A <<endl;
  
  cout << "sumy w wierszach:" << endl;
  
  for(int r=0;r<k;r++){
    p_term s=zero;
    for(int c=0;c<k;c++)
      s=s+A[r][c];
    cout << renormalize(s) << endl;
  }

  cout << "eigen_values:" << endl;
  cout << eigenvalues_equation(A,new zmienna("x")) << " = 0 " << endl;


  vector<vector<p_term> > R;
  for(int r=1;r<k;r++){
    vector<p_term> row(A[0].size(),zero);
    row[r]=jeden;
    row[r-1]=minus_jeden;
    R.push_back(row);
  }
  cout << "Roznice w obrebie rundy:" << endl;
  cout << R * A << endl;
  
  p_term alfa=new zmienna("a");
  p_term poczatkowe_beta= new zmienna("b");//dwa*(alfa-jeden);
  vector<p_term> p;
  for(int i=0;i<k;i++)
    p.push_back(poczatkowe_beta);
  p.push_back(dwa+dwa);
  p.push_back(dwa);
  
  macierz pi;
  
  for(int i=0;i<4;i++){
    pi.push_back(p);
    p=A*p;
  }
  cout << "PI:" << endl;

  cout << pi <<endl;
  

  system("PAUSE");
}

*/
