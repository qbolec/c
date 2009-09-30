struct avl3
{
	avl3 * b;
	avl3 * s;
	avl3 * f;
	char isb;
	long h;
	long v;
	long i;
	long balance;
};
void zm(void * ptr,long size)
{
	char * a=ptr;
	while(size--)*a++=0;
}
void siorbajlewy(avl3 * q)
{
/*
	q
    / \
   A   B
  / \
 x   y

    |
    V

     A
    / \
   x   q
      / \
     y   B

 */

	avl3 * A=q->s;
	avl3 * B=q->b;
	avl3 * x=q->b->b;
	avl3 * y=q->b->s; 
	if(y)y->f=q;
	if(y)y->isb=0;
	q->s=y;
}
AVLinsert( avl3 * d3, long v)
{
	if(d3->v==v)
	{
		d3->instances++;
		return;
	}
	if(d3->v<v)
	{
		if( d3->b==0 )
		{
			d3->b=new avl3;
			d3->b->b=d3->b->s=0;
			d3->b->f=d3;
			d3->b->isb=1;
			d3->b->v=v;
			d3->b->i=1;
			d3->b->h=0;
			d3->b->balance=0;
		}
		else
		{
			AVLinsert( d3->b , v);
		}
	}
	else
	{
		if( d3->s==0 )
		{
			d3->s=new avl3;
			d3->s->b=d3->s->s=0;
			d3->s->f=d3;
			d3->s->isb=1;
			d3->s->v=v;
			d3->s->i=1;
			d3->s->h=0;
			d3->s->balance=0;
		}
		else
		{
			AVLinsert( d3->s , v);
		}

	}
	d3->h=0;
	d3->balance=0;
	if(d3->b)
	{
		d3->h=d3->b->h+1;
		d3->balance=d3->b->h;
	}
	if(d3->s)
	{
		if(d3->s->h+1>d3->h)
			d3->h=d3->s->h+1;
		d3->balance-=d3->s->h;
	}
	if(d3->balance>1)
	{
		if(d3->b->balance>0)
		{
			siorbajprawy(d3);
		}
		else
		{
			siorbajlewy(d3->b);
			siorbajprawy(d3);
		}
		return;//donnafatal
	}
	if(d3->balance<-1)
	{
		if(d3->s->balance<0)
		{
			siorbajlewy(d3);
		}
		else
		{
			siorbajprawy(d3->s);
			siorbajlewy(d3);
		}
	}
}



