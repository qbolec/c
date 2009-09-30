#include <iostream.h>


struct q3
{
	q3 * f;
	char isb;
	q3 * b;
	q3 * s;
	long v;
	long i;
};

q3 * bigroot;//set this to the root pointer whenever do anything

void nullify(void * ptr,int size)
{
	char * p=(char *)ptr;
	while(size--) *p++=0;
}
void moveup( q3 * q)
{
/*
     B
    / \
   A   C
  s b s b

 */


	while(q->f!=0)
	{
		if(q->isb)
		{
/*
     C
    / \
   B   Cb
  / \
 A   Cs

 */
			q3 * A=q->f->s;
			q3 * B=q->f;
			q3 * C=q;
			q3 * Cs=q->s;
			q3 * Cb=q->b;
			C->f=B->f;
			C->isb=B->isb;
			if(C->isb==1)C->f->b=C;
			if(C->isb==0)C->f->s=C;
			if(Cs)Cs->f=B;
			if(Cs)Cs->isb=1;
			if(A)A->f=B;
			if(A)A->isb=0;
			B->f=C;
			B->isb=0;
			B->s=A;
			B->b=Cs;
			C->s=B;
			q=C; //dla pewnosci
		}
		else
		{

/*
     A
    / \
   As  B
      / \
     Ab  C 

 */
			q3 * A=q;
			q3 * B=q->f;
			q3 * C=q->f->b;
			q3 * As=q->s;
			q3 * Ab=q->b;
			A->f=B->f;
			A->isb=B->isb;
			if(A->isb==1)A->f->b=A;
			if(A->isb==0)A->f->s=A;
			if(Ab)Ab->f=B;
			if(Ab)Ab->isb=0;
			if(C)C->f=B;
			if(C)C->isb=1;
			B->f=A;
			B->isb=1;
			B->s=Ab;
			B->b=C;
			A->b=B;
			q=A;//dla pewnosci

		}
	}

	bigroot=q;
}
void insertq3( q3 * root, long v)
{
	if(root->v==v)
	{
		root->i++;
		moveup(root);
		return ;
	}
	if(root->v<v)
	{
		if(!root->b)
		{
			root->b= new q3;
			root->b->f=root;
			root->b->v=v;
			root->b->i=1;
			root->b->isb=1;
			root->b->b=root->b->s=0;
			moveup(root->b);
			return;
		}
		else
		{
			insertq3(root->b,v);
			return;
		}
	}
	else
	{
		if(!root->s)
		{
			root->s= new q3;
			root->s->f=root;
			root->s->v=v;
			root->s->i=1;
			root->s->isb=0;
			root->s->b=root->s->s=0;
			moveup(root->s);
			return;
		}
		else
		{
			insertq3(root->s,v);
			return;
		}
	}
}
int ispresentq3(q3 * root,long v)
{
	if(root->v==v)
	{
		moveup(root);
		if(root->i)return 1;
		else return 0;
	}
	if(root->v<v)
	{
		if(root->b)return ispresentq3(root->b,v);
		else return 0;
	}
	else
	{
		if(root->s)return ispresentq3(root->s,v);
		else return 0;
	}
}
void removeq3(q3 * root,long v)
{
	if(ispresentq3(root,v));
	bigroot->i--;
}
void testq3(q3 * root,long l)
{
	for(long i=0;i<l;i++)cout << " ";
	cout << "Value:" << root->v << endl;
	if(root->s) testq3(root->s,l+1);
	if(root->b) testq3(root->b,l+1);

}
int main()
{
	bigroot=new q3;
	nullify(bigroot,sizeof(q3));
	for(long i=0;i<64;i+=2)
	{
		insertq3(bigroot,i);
	}


	for(long i=0;i<64;i++)
	{
		if( (i & 1) == ispresentq3(bigroot,i))
		{
		 	cout << "FAILURE ";
			cout << "ID " << i << "VALUE " << (i&1) << endl;
			return 0;
		}
		
	}


	cout << "All ok!!";
	return 0;
}

