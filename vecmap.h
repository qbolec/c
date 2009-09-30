template<typename keyT,typename valT>
struct vecmap{//only insert and search, no : delete
	struct ass{
		keyT key;
		valT val;
	};
	ass * assigments;
	int realSize;
	int find(int from,int to,const keyT &k)const{
		while(from<to){
			int c=(from+to)>>1;
			if(assigments[c].key==k)
				return c;
			if(assigments[c].key<k)
				from=c+1;
			else
				to=c;
		}
		return -from-1;
	}
	bool isset(const keyT &k)const{
		return (find(0,realSize,k)>=0);
	}
	valT& getValue(const keyT &k)const{
		return assigments[find(0,realSize,k)].val;
	}
	void setValue(const keyT &k,const valT &v){
		int f=find(0,realSize,k);
		if(f>=0){
			assigments[f].val=v;
		}else{
			int pos=-f-1;
			if(!realSize){
				assigments=new ass[4];
				realSize=1;
				assigments[0].key=k;
				assigments[0].val=v;
			}else if(realSize>=4 && !(realSize&(realSize-1)) ){
				ass *n_assigments=new ass[realSize*2];
				memcpy(n_assigments,assigments,sizeof(ass)*pos);
				n_assigments[pos].key=k;
				n_assigments[pos].val=v;
				memcpy(n_assigments+pos+1,assigments+pos,sizeof(ass)*(realSize-pos));
				delete[] assigments;
				assigments=n_assigments;
				realSize++;
			}else{
				memmove(assigments+pos+1,assigments+pos,sizeof(ass)*(realSize-pos));
				assigments[pos].key=k;
				assigments[pos].val=v;
				realSize++;
			}
		}
	}
	vecmap():assigments(0),realSize(0){}
	~vecmap(){
		if(realSize){
			delete[] assigments;
		}
	}
};
