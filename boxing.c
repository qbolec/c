#include <stdio.h>
struct box{
	int w;
	int h;
};
struct box boxes[4];
int smallesth,smallestw,smallest=0xEFFFFFF;
int perm[24][4]={
{0,1,2,3},
{0,1,3,2},
{0,2,1,3},
{0,2,3,1},
{0,3,1,2},
{0,3,2,1},
{1,0,2,3},
{1,0,3,2},
{1,2,0,3},
{1,2,3,0},
{1,3,0,2},
{1,3,2,0},
{2,0,1,3},
{2,0,3,1},
{2,1,0,3},
{2,1,3,0},
{2,3,0,1},
{2,3,1,0},
{3,0,1,2},
{3,0,2,1},
{3,1,0,2},
{3,1,2,0},
{3,2,0,1},
{3,2,1,0},
};
int gray[16]={
3,2,3,1,3,2,3,0,3,2,3,1,3,2,3,0
};
int max(int a,int b){
	return (a>b)?a:b;
}
int max3(int a,int b,int c){
	return max(max(a,b),c);
}
int max4(int a,int b,int c,int d){
	return max(max3(a,b,c),d);
}
void rotate(int id){
	int swp=boxes[id].w;
	boxes[id].w=boxes[id].h;
	boxes[id].h=swp;
}
void check(int w,int h){
		int s;
		if((s=w*h)<smallest){
			smallest=s;
			smallestw=w;
			smallesth=h;
		}
}
#define A boxes[perm[p][0]]
#define B boxes[perm[p][1]]
#define C boxes[perm[p][2]]
#define D boxes[perm[p][3]]
int main(){
	int w,h,i,g,p;
	for(i=0;i<4;i++)
		scanf("%d %d", &boxes[i].w,&boxes[i].h);
	for(g=0;g<16;rotate(gray[g++])){
		w=boxes[0].w+boxes[1].w+boxes[2].w+boxes[3].w;
		h=max4(boxes[0].h,boxes[1].h,boxes[2].h,boxes[3].h);
		check(w,h);
		for(p=0;p<24;p++){
			w=max(A.w,   B.w+C.w+D.w);
			h=A.h+max3(B.h,C.h,D.h);
			check(w,h);
			w=B.w+ max(C.w+D.w,A.w);
			h=max(B.h,A.h+max(C.h,D.h));
			check(w,h);
			w=max(A.w,C.w)+max(B.w,D.w);
			h=max(A.h+C.h , B.h+D.h);
			check(w,h);
			w=max(A.w,D.w)+B.w+C.w;
			h=max3(A.h+D.h,B.h,C.h);
			check(w,h);
            w=max(A.w+B.w,D.w+C.w);
            h=max(A.h+D.h,B.h+C.h);
            if((A.w+C.w>w)&&(A.h+C.h>h))continue;
            if((B.w+D.w>w)&&(B.h+D.h>h))continue;
            check(w,h);
		}
	}
	printf("Minimal pool: %d for dimensions: %d x %d",smallest,smallestw,smallesth);
	return 0;
}
