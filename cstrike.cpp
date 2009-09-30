#include <fstream.h>
#include <stdlib.h>
struct user
{
   char nick[32];
   long gp;
   long frags;
   long deaths;
};
char statsfilename[100]="c:\\moje dokumenty\\my webs\\gg\\csstats.txt";
char statsexporter[100]="c:\\moje dokumenty\\my webs\\gg\\pasteme.txt";
//char statsfilename[100]="c:\\csstats.txt";
//char statsexporter[100]="c:\\pasteme.txt";

long cs=0;
user * users;
int compare(const void * a,const void * b)
{
  long f1= (((user *) a )->frags) *(((user *) b) -> gp);
  long f2= (((user *) b )->frags) *(((user *) a) -> gp);
  return f2-f1;
}

int equal(char * a,char * b)
{
  while(*a==*b)
  {
    if(*a==0)return 1;
    a++;
    b++;
  }
  return 0;
}
int getid(char * nick)
{
  for(long i=0;i<cs;i++)
  {
    if(equal(nick,users[i].nick)==1)return i;
  }
  return -1;
}
void writestat(ofstream & qout, char * nick, long gp,long frags, long deaths)
{
  long fpg=10*frags /gp;
  long dpg=10*deaths/gp;
    qout << "<tr>\n";
    qout <<  "  <td class=\"redlight\" align=\"center\">"  << nick  << "</td>\n";
    qout  << "  <td class=\"redlight\" align=\"center\">"  << gp    << "</td>\n";
    qout  << "  <td class=\"redlight\" align=\"center\">"  << frags << "</td>\n";
    qout  << "  <td class=\"redlight\" align=\"center\">"  << (fpg/10) << "." << (fpg%10)   << "</td>\n";
    qout  << "  <td class=\"redlight\" align=\"center\">"  << deaths<< "</td>\n";
    qout <<  "  <td class=\"redlight\" align=\"center\">"  << (dpg/10) << "." << (dpg%10)   << "</td>\n";
    qout << "</tr>\n";
}
void loaddata()
{
  ifstream qin ( statsfilename);
  qin >> cs;
  users= new user[cs+1];
  for(long i =0 ; i< cs; i++)
  {
    qin >> users[i].nick;
    qin >> users[i].gp;
    qin >> users[i].frags;
    qin >> users[i].deaths;
  }
  qsort( users,cs,sizeof(user),compare );
}
void savedata()
{
  qsort( users,cs,sizeof(user),compare );
  ofstream qout ( statsfilename);
  qout << cs << endl;
  for(long i =0 ; i< cs; i++)
  {
    qout << users[i].nick << endl;
    qout << users[i].gp << endl;
    qout << users[i].frags << endl;
    qout << users[i].deaths << endl;
  }
  
}
void writestats()
{
  qsort( users,cs,sizeof(user),compare );
  cout << ".:file pasteme.txt is written:.\n";
  ofstream qout (statsexporter );
  for(long i=0;i<cs;i++)
    writestat(qout, users[i].nick,users[i].gp,users[i].frags,users[i].deaths);
}
void addnewstats()
{
  cout << ".:how many players took part in this battle?:.\n";
  long c;
  cin >> c;
  for(long i=0;i<c;i++)
  {
    char nick[32];
lab: cout << ".:what was the nick of player "<< i << " ?:.\n";
    cin >> nick;
    int id= getid(nick);
    if(id==-1)
    {
      cout << ".:noone in database has got that nick:.\n";
      cout << ".:are you sure the spelling?:.\n";
      cout << ".:ADD NEW NICK TO DATABASE? Y/N:.\n";
      char ans;
      cin >> ans;
      if(ans=='N' || ans=='n')
      {
        cout << ".:so, type nick again:.\n";
        goto lab;
      }
      user * old=users;
      users = new user[cs+1];
      for(int j=0;j<cs;j++)
        users[j]=old[j];
      users[cs].nick=nick;
      users[cs].gp=0;
      users[cs].frags=0;
      users[cs].deaths=0;
      id=cs;
      cs++;
    }
    users[id].gp++;
    cout << ".:how many frags he got?:.\n";
    long x;
    cin >> x;
    users[id].frags+=x;
    cout << ".:how many times did he die?:.\n";
    cin >> x;
    users[id].deaths+=x;
  }
  savedata();
}
void showstats()
{
  qsort( users,cs,sizeof(user),compare );
  for (int i=0;i<cs;i++)
    cout << users[i].nick << "|" << users[i].gp << "|" << users[i].frags << "|" << users[i].deaths << endl;
  
}
int main()
{
   loaddata();
  while(1)
  {
     int x;
     cout << ".:how   can  I serve   You?:.\n";
     cout << ".:1:.write stats onto html.:.\n";
     cout << ".:2:.add new stats to rank.:.\n";
     cout << ".:3:.show me current stats.:.\n";
     cout << ".:4:.Shut Up!ShaatApp!Shut...\n";
     cin >> x;
     switch(x)
     {
       case(1):writestats();
         break;
       case(2):addnewstats();
         break;
       case(3):showstats();
         break;
       case(4):return 0;
         break;
     }
    savedata();
  }
}