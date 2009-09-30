#include <iostream.h>
class machine
{
  public:
    virtual void setupforword(char * word)
            {
			return;
            }
    
    virtual long searchthetext(char * text)
            {
              return 0;
            }
    
};
/*
robin carp performs a heurestic test with hashing
 */
class robincarp: public machine
{
  private:
    static const long modullo=111  ;
    long bigchange;
    long properrest;
    long len;
    char * savedword;    
  public:
    void setupforword(char * word)
    {
      for(len=0;word[len];len++);
      bigchange=1;
      for(long i=1;i<len;i++)
        bigchange=(bigchange<<8)%modullo;
      properrest=0;
      for(long i=0;i<len;i++)
        properrest= ((properrest<<8)+word[i])%modullo;
      savedword=new char[len];
      for(long i=0;i<len;i++)
        savedword[i]=word[i];
    }
    long searchthetext(char * text)
    {
      long qrentrest=0;
      for(long i=0;i<len;i++)
        qrentrest= ((qrentrest<<8)+text[i])%modullo;
      
      for(long position=0;text[position+len-1];position++)
      {
        if(qrentrest==properrest)
        {
          long p;
          for(p=0;p<len;p++)
            if(savedword[p]!=text[position+p])break;
          if(p==len)return position;
        }
        qrentrest=((qrentrest-bigchange*text[position])<<8)+text[position+len];
        while(qrentrest>=modullo)
        {
          qrentrest-=modullo;
        }
        while(qrentrest<0)
        {
          qrentrest+=modullo;
        }
      }
	  return -1;
    }
 
};
long performsearch(machine * m,char * word,char * text)
{
  m->setupforword(word);
  return m->searchthetext(text);
}
int main()
{
  robincarp r;
  cout << performsearch( &r ,"DUPCIA","heh sam jestes DUPCIA");
}

