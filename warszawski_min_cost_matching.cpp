#TO JEST MAX COST MATCHING:D
const int S=5000;
int n,w[S][S];
int m[2*S];
int lab[2*S],s[S],lam,sla[S],q[S],qb,qe,ba[S];

void km3() {
  int f,of;
  REP(i,2*n) lab[i]=0, m[i]=-1;
  REP(i,n) REP(j,n) lab[i] >?= w[i][j];
  REP(faza,n) {
    REP(i,n) s[i]=0, sla[i]=1000000000; qb=qe=0;
    REP(i,n) if (m[i]==-1) s[ q[qe++]=i ]=1;
    f=-1;
    for(;;) {
	    while (qb!=qe) {
	      int v=q[qb++];
	      REP(i,n) if (sla[i] > lab[v]+lab[i+n]-w[v][i]) {
	        sla[i]=lab[v]+lab[i+n]-w[v][i]; ba[i]=v;
	        if (sla[i]==0) {
		        if (m[i+n]==-1) { f=i; goto kon; }
		        else if (!s[m[i+n]]) s[ q[qe++]=m[i+n] ]=1;
	        }
	      }
	    }
	    lam=1000000000; REP(i,n)if(sla[i]) lam<?=sla[i];
      REP(i,n) if (s[i]) lab[i]-=lam;
      REP(i,n) if (sla[i]==0) lab[i+n]+=lam; else sla[i]-=lam;
	    REP(i,n) if (sla[i]==0) {
	      if (m[i+n]==-1) { f=i; goto kon; }
	      else if (!s[m[i+n]]) s[ q[qe++]=m[i+n] ]=1;
	    }
    }
kon:
    while (f!=-1) { m[f+n]=ba[f]; of=m[ba[f]]; m[ba[f]]=f; f=of; }
   }
}
