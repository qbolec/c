#include<iostream.h>
/*
symbol π is 165 or 185
symbol Ê is 134 or 230
symbol Í is 169 or 234
symbol Ò is 228 or 241
symbol ≥ is 136 or 179
symbol Û is 162 or 243
symbol ú is 152 or 156
symbol ü is 171 or 159
symbol ø is 190 or 191
symbol • is 164 or 165
symbol ∆ is 143 or 198
symbol   is 168 or 202
symbol £ is 157 or 163
symbol — is 227 or 209
symbol å is 151 or 140
symbol ” is 224 or 211
symbol è is 141 or 143
symbol Ø is 189 or 175
*/
class converter{
private:
	unsigned char convAB[256];
	unsigned char convBA[256];
public:
	int standard(unsigned char ou){
		if(ou==165)return 1;
		else if(ou==185) return 2;
		return 0;
	}
	unsigned char * convert(unsigned char * text,int from,int to){
		if(to==from)
			return text;
		if(from==1 && to==2)
			for(int i=0;text[i];i++)
				text[i]=convAB[text[i]];
		else if(from==2 && to==1)
			for(int i=0;text[i];i++)
				text[i]=convBA[text[i]];
		else
			return 0;
		return text;
	}
	converter(){
		for(int i=0;i<256;i++)
			convAB[i]=i;
		convAB[165]=185;
		convAB[134]=230;
		convAB[169]=234;
		convAB[228]=241;
		convAB[136]=179;
		convAB[162]=243;
		convAB[171]=156;
		convAB[190]=191;
		convAB[164]=165;
		convAB[143]=198;
		convAB[168]=202;
		convAB[157]=163;
		convAB[227]=209;
		convAB[151]=140;
		convAB[224]=211;
		convAB[141]=143;
		convAB[189]=175;
		convAB[169]=234;
		convAB[169]=234;
		convAB[169]=234;
		for(int i=0;i<256;i++)
			convBA[convAB[i]]=i;
	}
};
int main(){
	converter pgconv;
	int EXESTD=pgconv.standard('π');
	cout << "prosze wpisac literke ktora w polskim alfabecie jest miedzy a i b" << endl;
	cout << "proszÍ wpisaÊ literkÍ ktÛra w polskim alfabecie nazywa siÍ 'π'" << endl;
	int CINSTD=pgconv.standard(cin.get());
	char w[]="DziÍkujÍ";
	cout << w << " tzn " << pgconv.convert((unsigned char *)w,EXESTD,CINSTD);
	return 0;
}
