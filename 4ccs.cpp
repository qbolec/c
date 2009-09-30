#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
using namespace std;
int main(int argc,char * args[]){
  char * magic;
  char * ext="";
  int magiclen=4;

  if(argc==3){
    magic=args[1];
    ext=args[2];
    magiclen=strlen(magic);
  }else if(argc==2){
    FILE * f=fopen(args[1],"rb");
    if(f){
      magic=new char[4];
      if(4==fread(magic,1,4,f)){
        int l=strlen(args[1]);
        for(int i=l;i--;)
          if(args[1][i]=='.'){
            ext=new char[l-i];
            strcpy(ext,args[1]+i+1);
          }
        printf("extension: %s, header: (%c%c%c%c)\n",ext,magic[0],magic[1],magic[2],magic[3]);
      }else{
        printf("can't read 4 bytes from\n",args[1]);
        return -1;
      }
    }else{
      printf("can't open %s\n",args[1]);
      return -1;
    }
  }else{
    printf("%s \"prefix of content header\" extension\nor\n%s \"name of proper file\"",args[0],args[0]);
    return -1;
  }

  if(*ext=='.')ext++;
  char * header=new char[magiclen];
  char newname[FILENAME_MAX];

  _finddata_t res;
  long h=_findfirst ("*.chk", &res);
  if(h!=-1){
    do{
      if(res.size>=magiclen){
//        printf("file %s\n",res.name);
        FILE * f=fopen(res.name,"rb");
        if(f){
          for(int i=0;i+magiclen<=res.size;i+=512){
         //   printf("\roffset %d",i);
            fseek(f,i,SEEK_SET);
            if(magiclen==fread(header,1,magiclen,f)){
              if(!memcmp(header,magic,magiclen)){
                strcpy(newname,res.name);
                for(int j=strlen(newname);j--;)
                  if(newname[j]=='.'){
                    strcpy(newname+j+1,ext);
                    break;
                  }
                fseek(f,i,SEEK_SET);
                FILE * newfile=fopen(newname,"wb");
                if(newfile){
                  char * buffer=new char[res.size-i];
                  if(res.size-i!=fread(buffer,1,res.size-i,f))
                    printf("can't read content in file %s at offset %d\n",res.name,i);
                  else
                    if(res.size-i!=fwrite(buffer,1,res.size-i,newfile))
                      printf("can't write to %s\n",newname);
                    else
                      printf("generated file %s from old file %s at offset %d\n",newname,res.name,i);
                  delete buffer;
                  fclose(newfile);
                }else
                  printf("could not open %s for writing",newname);
                break;
              }
            }else{
              printf("can't read %d bytes from %s\n",magiclen,res.name);
              break;
            }
          }
          fclose(f);
        }else
          printf("failed to open %s\n",res.name);
      }
    }while(!_findnext(h,&res));
    _findclose(h);
  }
  return 0;
}
