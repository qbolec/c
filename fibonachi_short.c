unsigned long long n,a,b=1,c;  
main(i,m){scanf("%llu%d",&n,&m);for(i=64;i--;){c=(b*(b+2*a))%m;a=(a*(b*2+m-a))%m;b=(c+m-a)%m;if((n>>i)&1){c=(a+b)%m;a=b;b=c;}}return !printf("%llu",a);}
