#include <fstream.h>
void trimcomments(char * f,char * t)
{
	long insidecomment;
	ifstream qin(f);
	ofstream qout(t);
	char last[3];
	char endofline[3]="\10\13";
	char endofcomment[3]="*/";
	char * waitfor;
	qin.get(last[1]);
	while(!qin.eof())
	{
		last[0]=last[1];
		qin.get(last[1]);
		if(insidecomment && (strcmp(last,waitfor)==0))
		{
			insidecomment=0;
			last[0]=last[1];
			qin.get(last[1]);
			continue;
		}
		if((!insidecomment) && (strcmp(last,"//")==0))
		{
			insidecomment=1;
			waitfor=endofline;
			last[0]=last[1];
			qin.get(last[1]);
			continue;
		}
		if((!insidecomment) && (strcmp(last,"/*")==0))
		{
			insidecomment=1;
			waitfor=endofcomment;
			last[0]=last[1];
			qin.get(last[1]);
			continue;
		}
		if(!insidecomment)
		{
			qout.put(last[0]);
		}
	}
}
int main(int argc,char * args[])
{
	cout << "Triming " << args[1] << " to " <<  args[2] << endl;
	trimcomments( args[1],args[2]);
	return 0;
}
