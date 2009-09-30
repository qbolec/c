#include<stdio.h>
FILE* input=fopen("BARREL.IN","r");
FILE* output=fopen("BARREL.OUT","w");
struct BOX{
	float L;
	float D;
	float h;
};
BOX box[1000];
float S,H,V;
int N;
float volume(float h){
	float wq=h*S;
	for(int i=0;i<N;i++){
		float q;
		if(h>=box[i].h){
			if(h+box[i].L-box[i].h<=H){
				q=box[i].h*box[i].L*box[i].L;
			}else{
				q=(box[i].L+h-H)*box[i].L*box[i].L;
			}
		}else
			q=h*box[i].L*box[i].L;
		wq-=q;
	}
	return wq;
}
float search(float from,float to){
	float centre=(from+to)/2;
	if((to-from)<0.000001)
		return centre;
	if(V>volume(centre))
		return search(centre,to);
	else
		return search(from,centre);
}
int main(){
	fscanf(input,"%f %f %f %d",&S,&H,&V,&N);
	for(int i=0;i<N;i++)
		fscanf(input,"%f %f",&box[i].L,&box[i].D);
	for(int i=0;i<N;i++)
		if(box[i].D>1){
			box[i].h=box[i].L;
		}else{
			box[i].h=box[i].L*box[i].D;
			if(box[i].h<0)
				box[i].h=0;
		}
	fprintf(output,"%f\n",search(0,H));
	fclose(input);
	fclose(output);
	return 0;
}
