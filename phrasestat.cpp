#include <fstream.h>
ifstream fin("input.txt") ;
long stats[1024];
int main()
{
	int more=1;
	long spaces=0;
	while(more)
	{
		char filename[256];
		fin>> filename;
		ifstream qin(filename,ios::bin);
		cout << "Prociding..." << filename << flush << endl;
		for(long i=0;i<1000000;i++)
			qin.get();
		while(!qin.eof())
		{
			switch(qin.get())
			{
				case(' '):
					spaces++;
				break;
				case(0):
					stats[spaces]++;
					spaces=0;
				break;

				case(10):
					stats[spaces]++;
					spaces=0;
				break;
				case(13):
					stats[spaces]++;
					spaces=0;

				break;

			}
		}
		fin >> more;
	}
	for(int i=0;i<1024;i++)
	{
		if(stats[i])
		{
			cout << "Naliczono\t" << stats[i] << "\tzdan\t" << i << "\twyrazowych" << endl;
		}
	}
	return 0;
}
