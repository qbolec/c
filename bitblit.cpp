//assumes you've got normalblt( src ,srcx,srcy, srcw,srch, dest,destx,desty)
fastblit( src , srcw,srch, dest,destw,desth)
{
	normalblt(src,0,0,srcw,srch,dest,0,0);
	//prebliting first column
	long doneh=srch;
	while(doneh<srch)
	{
		todoh=desth-doneh;
		long fragmenth= (todow<donew)?todoh:doneh;
		fragmenth-=fragmenth%srch;
		if(!fragmenth)fragmenth=todoh;
		normalblt(src,0,0,srcw,srch,dest,0,doneh);
		doneh+=fragmenth;

	}
	long donew=srcw;
	//the rest
	while(donew<srcw)
	{
		todow=destw-donew;
		long fragmentw= (todow<donew)?todow:donew;
		fragmentw-=fragmentw%srcw;
		if(!fragmentw)fragmentw=todow;
		normalblt(dest,0,0,fragmentw,desth,dest,donew,desth);
		donew+=fragmentw;
	}
}
