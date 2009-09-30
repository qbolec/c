#include <iostream.h>
struct box{
	int w;
	int h;
};
box boxes[4];
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
  //0000
3,//0001
2,//0011
3,//0010
1,//0110
3,//0111
2,//0101
3,//0100
0,//1100
3,//1101
2,//1111
3,//1110
1,//1010
3,//1011
2,//1001
3,//1000
0
};
inline int max(int a,int b){
	return (a>b)?a:b;
}
inline int max(int a,int b,int c){
	return max(max(a,b),c);
}
inline int max(int a,int b,int c,int d){
	return max(max(a,b,c),d);
}
inline void rotate(box &b){
	int swp=b.w;
	b.w=b.h;
	b.h=swp;
}
inline void check(int w,int h){
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
	int w,h;
	for(int i=0;i<4;i++)
		cin >> boxes[i].w >> boxes[i].h;
	for(int g=0;g<16;rotate(boxes[gray[g++]])){
		//Case 1: wszystkie obok siebie [permutacja nie ma tu znaczenia]
		w=boxes[0].w+boxes[1].w+boxes[2].w+boxes[3].w;
		h=max(boxes[0].h,boxes[1].h,boxes[2].h,boxes[3].h);
		check(w,h);
		for(int p=0;p<24;p++){
			//Case 2: Jeden na spodzie reszta na nim
			w=max(A.w,   B.w+C.w+D.w);
			h=A.h+max(B.h,C.h,D.h);
			check(w,h);
			//Case 3: A B jako podstawa, C,D leza na A
			w=B.w+ max(C.w+D.w,A.w);
			h=max(B.h,A.h+max(C.h,D.h));
			check(w,h);
			//Case 4: A B jako podstawa, C lezy na A, D lezy na B
			w=max(A.w,C.w)+max(B.w,D.w);
			h=max(A.h+C.h , B.h+D.h);
			check(w,h);
			//Case 5: A B C jako podstawa , D lezy na A
			w=max(A.w,D.w)+B.w+C.w;
			h=max(A.h+D.h,B.h,C.h);
			check(w,h);
			//Case 6: taki dziwny uklad ala sfastyka
            w=max(A.w+B.w,D.w+C.w);
            h=max(A.h+D.h,B.h+C.h);
            if((A.w+C.w>w)&&(A.h+C.h>h))continue;
            if((B.w+D.w>w)&&(B.h+D.h>h))continue;
            check(w,h);
		}
	}
	cout << "Minimal pool:" << smallest << " for dimensions: " << smallestw << 'x' << smallesth<<endl;
	return 0;
}
