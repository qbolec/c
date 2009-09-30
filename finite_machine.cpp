class machine{
private :
	unsigned char state;
	unsigned char *move[256];
	unsigned char len;
public:
	int operator !(){
		return (state==len)?0:1;
	}
	int operator << (unsigned char hay){
		if(len==(state=move[hay][state]))return 1;
		else return 0;
	}
	unsigned char * operator << (unsigned char * haystack){
		while((!*this)&&(*haystack))
			*this<< *haystack++;
		return (!*this)?haystack-len:0;
	}
	void reset(){
		state=0;
	}
	machine(unsigned char * needle){
		state=0;
		for(len=0;needle[len];len++);
		for(int i=0;i<256;i++)
			move[i]=new unsigned char[len+1];
        unsigned char * kmp=new unsigned char[len];
        kmp[0]=0;
        for(int j,i=1;i<len;i++){
        	for(j=i-1;j&&(needle[kmp[j]]!=needle[i]);j=kmp[j]-1);
        	kmp[i]=j?kmp[j]+1:0;
        }
        for(int a=0;a<256;a++)
        	move[a][0]=(needle[0]==a)?1:0;
        for(int i=1;i<len;i++)
        	for(int a=0;a<256;a++)
        		move[a][i]=(needle[i]==a)?i+1:move[a][kmp[i-1]];
       	for(int a=0;a<256;a++)
       		move[a][len]=move[a][kmp[len-1]];
       	delete kmp;
	}
	~machine(){
		for(int i=0;i<256;i++)
			delete move[i];
    }
};
//SAMPLE USAGE:
#include <iostream.h>
int main(int argc,char * args[]){
	if(argc==2){
		int found=0;
		machine fm((unsigned char*)args[1]);
		while(!cin.eof()){
			if(fm<<cin.get())
				found++;
		}
		cout << "found :" << found << " occurences of " << args[1] << endl;
	}else{
		cout << "syntax is :" << args[0] << " needle" <<endl;
	}
	return 0;
}

