unsigned long MemorySize=0;
unsigned long MapSize=0;
char * RAM;
unsigned char * MAP;
char SPACE[256]={
 8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,4,3,3,2,2,2,2
,3,2,2,2,2,2,2,2,4,3,2,2,2,2,2,2,3,2,2,2,2,2,2,2,6,5,4,4,3,3,3,3,3,2,2,2,2,2,2,2
,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1,4,3,2,2,2,1,1,1
,3,2,1,1,2,1,1,1,7,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,4,3,2,2,2,2,2,2,3,2,2,2,2,2,2,2
,5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,6,5,4,4,3,3,3,3
,3,2,2,2,2,2,2,2,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1
,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,0};

unsigned char BM[9]={0,1,3,7,15,31,63,127,255};
unsigned long lastalloc=0;
/*char getspace(unsigned char c)
{
	char max=0;
	char current=0;

	for(char t=1;t;t<<=1)
	{
		if(c&t)
		{
			if(current>max)max=current;
			current=0;
		}
		else
			current++;
	}
	if(current>max)max=current;
	return max;
}*/

void qalloc(unsigned long Mem)
{
	MemorySize=Mem;
	MapSize=Mem/32;
	RAM= new char[MemorySize];
	MAP= new unsigned char[MapSize];
	for(unsigned long i=0;i<MapSize;i++)
		MAP[i]=0;
/*	unsigned char c=0;
        for(long i=0;i<256;i++)
        {
        	SPACE[c]=getspace(c);
        	cout << "," <<(int) SPACE[c];
        	c++;
        }
*/
}
long getbit(unsigned char & cc, unsigned char bm)
{
	long current=0;
        while(bm&cc)
        {
        	bm<<=1;
        	current++;
        }
        cc|=bm;
        return current;
}
char * qnew(long size)
{
	if(size&3)size=(size>>2)+1;
	else size=size>>2;
	for(unsigned long b=lastalloc;b<MapSize;b++)
		if( SPACE[MAP[b]]>=size )
		{
			unsigned long addr=b*32 + 4*getbit( MAP[b],BM[size]);
			lastalloc=b;
			return RAM+addr;
		}

	lastalloc=0;
	return 0;
}
void qdel(char * ptr,long size)
{
	if(size&3)size=(size>>2)+1;
	else size=size>>2;
	unsigned long addr=ptr-RAM;
	unsigned long b= addr>>5;
	MAP[b]-= (BM[size]<<(addr&31));
        lastalloc=b;
}



