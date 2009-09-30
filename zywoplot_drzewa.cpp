#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
const int max_n=50000;
int n;
int odpowiedz[max_n];
int h[max_n+3];
const int INF=1000000000;
struct punkt{
  int l,h,r,inputid,kara,answer;
  punkt(int _l,int _h,int _r,int _inputid){
    h=_h;
    l=_l<?_r;
    r=_l>?_r;
    inputid=_inputid;
    if(h>r){
      kara=2*h-r-l;
    }else if(h<l){
      kara=l+r-2*h;
    }else{
      kara=r-l;
    }
    answer=INF;
  }
  punkt(){}
};
punkt punkty[max_n+3];
bool cmp_l(const punkt & a,const punkt &b){
  return a.l<b.l;
}
bool cmp_r(const punkt & a,const punkt &b){
  return a.r<b.r;
}
bool cmp_h(const punkt & a,const punkt &b){
  return a.h<b.h;
}
struct question{
  int x;
  int pid;
  int answer;
  int offset;
  question(int pid,int offset):pid(pid),answer(INF),offset(offset){x=punkty[pid].h;}
};
bool cmp_x(const question & a,const question & b){
  return a.x <b.x;
}
punkt tmp[max_n];


struct event{
  int x;
  bool dodac;
  int val;
  int inputid;
  event(int x,int inputid,bool dodac,int val):x(x),inputid(inputid),dodac(dodac),val(val){}
  event(){}
};
bool cmp_ev(const event & a,const event & b){
  if(a.x==b.x)return a.dodac<b.dodac;
  return a.x<b.x;
}
event events[max_n*2];
struct informacja{
  punkt * begin;
  punkt *end;
  vector<question> zainteresowani[3];
  informacja(punkt * begin=0,punkt * end=0):begin(begin),end(end){}
  void dowal(int pid,int yfactor,int offset){
    zainteresowani[1+yfactor/2].push_back(question(pid,offset));
  }
  void wyliczaj(){
    memcpy(tmp,begin,(char*)end-(char*)begin);
    int len=end-begin;
    for(int i=0;i<3;i++)
      sort(zainteresowani[i].begin(),zainteresowani[i].end(),cmp_x);
    //pytania o takie co maja x<=l
    sort(tmp,tmp+len,cmp_l);
    for(int i=0;i<3;i++)if(!zainteresowani[i].empty()){
      int li=len-1;
      int opt=INF;
      int opt2=INF;
      int opt3=INF;
      int how2=INF;
      int how=INF;
      int yfactor=(i-1)*2;
      for(int xi=zainteresowani[i].size();xi--;){
        while(li>=0 &&  zainteresowani[i][xi].x<=tmp[li].l){
          int pro=tmp[li].l+tmp[li].r+ yfactor*tmp[li].h -tmp[li].kara;
          if(pro<=opt){
            opt3=opt2;
            opt2=opt;
            how2=how;
            opt=pro;
            how=tmp[li].inputid;
          }else if(pro<=opt2){
            opt3=opt2;
            opt2=pro;
            how2=tmp[li].inputid;
          }else if(pro<=opt3){
            opt3=pro;
          }
         li--;
        }
        if(abs(how-punkty[zainteresowani[i][xi].pid].inputid)>1)
          zainteresowani[i][xi].answer<?=opt-2*zainteresowani[i][xi].x;
        else if(abs(how2-punkty[zainteresowani[i][xi].pid].inputid)>1)
          zainteresowani[i][xi].answer<?=opt2-2*zainteresowani[i][xi].x;
        else
          zainteresowani[i][xi].answer<?=opt3-2*zainteresowani[i][xi].x;
      }
    }
    //pytania o takie co maja r<=x
    sort(tmp,tmp+len,cmp_r);
    for(int i=0;i<3;i++)if(!zainteresowani[i].empty()){
      int ri=0;
      int opt=INF;
      int opt2=INF;
      int opt3=INF;
      int how2=INF;
      int how=INF;
      int yfactor=(i-1)*2;
      for(int xi=0;xi< zainteresowani[i].size();xi++ ){
        while(ri<len &&  tmp[ri].r<=zainteresowani[i][xi].x){
          int pro=  -tmp[ri].l-tmp[ri].r+ yfactor*tmp[ri].h -tmp[ri].kara;
          if(pro<=opt){
            opt3=opt2;
            opt2=opt;
            how2=how;
            opt=pro;
            how=tmp[ri].inputid;
          }else if(pro<=opt2){
            opt3=opt2;
            opt2=pro;
            how2=tmp[ri].inputid;
          }else if(pro<=opt3){
            opt3=pro;
          }
          ri++;
        }
        if(abs(how-punkty[zainteresowani[i][xi].pid].inputid)>1)
          zainteresowani[i][xi].answer<?=opt+2*zainteresowani[i][xi].x;
        else if(abs(how2-punkty[zainteresowani[i][xi].pid].inputid)>1)
          zainteresowani[i][xi].answer<?=opt2+2*zainteresowani[i][xi].x;
        else
          zainteresowani[i][xi].answer<?=opt3+2*zainteresowani[i][xi].x;
      }
    }
    //pytania o takie co maja l<=x<=r
    for(int i=0;i<3;i++)if(!zainteresowani[i].empty()){
      int yfactor=(i-1)*2;
      int evs=0;
      for(int j=0;j<len;j++)if(tmp[j].l<tmp[j].r && tmp[j].l<zainteresowani[i].back().x&&zainteresowani[i][0].x<tmp[j].r)
      {
        events[evs++]=event(tmp[j].l,tmp[j].inputid,true ,-tmp[j].l+tmp[j].r+yfactor*tmp[j].h -tmp[j].kara);
        events[evs++]=event(tmp[j].r,tmp[j].inputid,false,-tmp[j].l+tmp[j].r+yfactor*tmp[j].h -tmp[j].kara);
      }
      sort(events,events+evs,cmp_ev);
      int ei=0;
      set<pair<int,int> > opt;
      opt.insert(make_pair(INF,INF));
      for(int xi=0;xi<zainteresowani[i].size();xi++){
        while(ei<evs && (events[ei].x<zainteresowani[i][xi].x|| events[ei].x==zainteresowani[i][xi].x && !events[ei].dodac )){
          if(events[ei].dodac)
            opt.insert(make_pair(events[ei].val,events[ei].inputid));
          else
            opt.erase(make_pair(events[ei].val,events[ei].inputid));
          ei++;
        }
        for(set<pair<int,int> >::iterator it=opt.begin();it!=opt.end();++it)
          if(abs(it->second -punkty[zainteresowani[i][xi].pid].inputid)>1){
            zainteresowani[i][xi].answer<?=it->first;
            break;
          }
      }
    }
    for(int i=0;i<3;i++)
      for(int j=0;j<zainteresowani[i].size();j++)
        punkty[ zainteresowani[i][j].pid ].answer<?= zainteresowani[i][j].answer+zainteresowani[i][j].offset;
  }
};
informacja informacje[max_n*4];


void buduj_po_h(punkt * begin,punkt * end,int idx=1){
  if(begin>=end)return;
  informacje[idx]=informacja(begin,end);
  if(begin+1<end){
    punkt * middle= begin+(end-begin)/2;
    buduj_po_h(begin,middle,idx*2);
    buduj_po_h(middle,end,idx*2+1);
  }
}
void zainteresuj_sie(int pid,int l,int r,int yfactor,int offset,int idx=1){
  informacja& info=informacje[idx];
  if(r<info.begin->h || info.end[-1].h<l)
    return;
  if(l<=info.begin->h && info.end[-1].h<=r){
//    printf("(%d,%d,%d) interesuje sie przedzialem %d %d, yfactor %d offset %d\n",punkty[pid].l,punkty[pid].h,punkty[pid].r,info.begin->h,info.end[-1].h,yfactor,offset);
    info.dowal(pid,yfactor,offset);
    return;
  }
  assert(info.end-info.begin>1);
  punkt * middle= info.begin+(info.end-info.begin)/2;
  if(l<=middle->h)
    zainteresuj_sie(pid,l,r,yfactor,offset,idx*2);
  if(middle->h<=r)
    zainteresuj_sie(pid,l,r,yfactor,offset,idx*2+1);
}
int sumakar=0;
int kara(int ile,int gdzie){
  return (gdzie>0?abs(h[gdzie]-ile):0)+(gdzie+1<n?abs(h[gdzie+2]-ile):0);
}
void zamien(int a,int b){
  if(a<0 || a>=n || b<0 || b>=n)return;
  if(a==b)return;
  int w=(a+1==b)?
    (sumakar-punkty[a].kara-punkty[b].kara+kara(punkty[b].h,a)+kara(punkty[a].h,b)+2*abs(punkty[a].h-punkty[b].h)):
    (sumakar-punkty[a].kara-punkty[b].kara+kara(punkty[b].h,a)+kara(punkty[a].h,b));
  odpowiedz[a]<?=w;
  odpowiedz[b]<?=w;
//  printf("zamiana %d z %d daje %d\n",a,b,w);
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    scanf("%d",h+i);
  h[0]=h[1];
  h[n+1]=h[n];
  for(int i=2;i<=n;i++)
    sumakar+=abs(h[i]-h[i-1]);
  for(int i=1;i<=n;i++)
    punkty[i-1]=punkt(h[i-1],h[i],h[i+1],i-1);

  for(int i=0;i<n;i++)
    odpowiedz[i]=sumakar;
  for(int i=0;i<n;i++){
    zamien(i-1,i);
    zamien(i,i+1);
    zamien(0,i);
    zamien(i,n-1);
  }
 
  sort(punkty+1,punkty+n-1,cmp_h);
  buduj_po_h(punkty+1,punkty+n-1);
  for(int i=1;i+1<n;i++){
    zainteresuj_sie(i,punkty[i].l,punkty[i].r,0,-punkty[i].l+punkty[i].r);
    zainteresuj_sie(i,-INF,punkty[i].l,-2,punkty[i].l+punkty[i].r);
    zainteresuj_sie(i,punkty[i].r,INF,2,-punkty[i].l-punkty[i].r);
  }
  
  for(int i=0;i<max_n*4;i++)
    if(informacje[i].begin!=NULL)
      informacje[i].wyliczaj();
  

  for(int i=1;i+1<n;i++){
  //  printf("odpowiedz %d = %d -%d\n",punkty[i].inputid,punkty[i].answer,punkty[i].kara);
    odpowiedz[punkty[i].inputid]<?=punkty[i].answer-punkty[i].kara+sumakar;
  }
  for(int i=0;i<n;i++)
    printf("%d\n",odpowiedz[i]);
}
