//niech wierzcholki beda indexowane od 0 do n-1

double waga(i,j,k)
{
//to do:
//wyznacz wage trojkata o bokach i->j->k (c-c-w)
}
long n;
double maxval[1000/*n*/][1000/*n*/];
//przechowuje maxymaln¹ wartoœæ triangulacji
//dla wielok¹ta który zawiera wszystkie wierzcho³ki
//od x do y id¹c c-c-w
//maxval[0][n-1]=> optymalna triangulacja

//maxval[x][y] (niech 0<=x< w <y < n)
//wyznaczmy tak:
//if y<x+2 then maxval[x][y]=0
//if y=x+2 then maxval[x][y]=waga(x,x+1,x+2)
//if y>x+2 then
//  max=0
//  for split=x+1 to y-1
//    compare max ? maxval[x][split]+maxval[split][y]+waga(y,x,split)
//
double getmaxval(long x,long y)
{
   if(maxval[x][y])return maxval[x][y];
   if(y<x+2)
   {
   	return 0;
   }
   if(y==x+2)
   {
   	maxval[x][y]=waga(x,x+1,x+2);
   	return maxval[x][y];
   }
   if(y>x+2)
   {
   	long max=0;
   	//long min=2000000000;
   	for(long split=x+1;split<y;split++)
   	{
   		long tmp=getmaxval(x,split)+getmaxval(split,y)+waga(y,x,split);
   		if(tmp>max)
   		//if(tmp<min)
   		{
   			max=tmp;
   			//min=tmp;
   		}
   	}
   	maxval[x][y]=max;
   	return maxval[x][y];
   }
}
double getmaxtriangulation()
{
    return getmaxval(0,n-1);
}
