/*
 implements :
 finding ranges of given size (matching it close)
 reservating given range
 freeing given range
 */
struct sizetreeelement
{
   positiontreeelement * bind;
   long reserved;//amount of reserved space
   long free;    //amount of free space
   sizetreeelement * f;
   sizetreeelement * b;
   sizetreeelement * s;
   char isb;

};
struct positiontreeelement
{
   sizetreeelement * bind;
   char * ptr;   //pointer to start of this whole think
   positiontreeelement * b;
   positiontreeelement * s;
   positiontreeelement * f;
   positiontreeelement * b1;
   positiontreeelement * s1;
   char isb;
};

positiontreeelement * positiontree;
sizetreeelement * sizetree;
char * ramstein;


//this will set the area for ramstein
void allocateramstain( long bytes )
{
  ramstein= new char [bytes];
  positiontree= new positiontreeelement;
  positiontree->b=0;
  positiontree->s=0;
  positiontree->f=0;
  sizetree= new sizetreeelement;
  sizetree->b=0;
  sizetree->s=0;
  sizetree->f=0;
  positiontree->bind=sizetree;
  sizetree->bind=positiontree;
  sizetree->reserved=0;
  sizetree->free=bytes;
  sizetree->ptr=ramstein;
}


sizetreeelement * findcontainerfor( long bytes)
{
  sizetreeelement * lastgood=0;
  sizetreeelement * place=sizetree;
  while(1)
  {
    if( place->free<bytes )
    {
       if( place->b==0)return lastgood;
       place=place->b;
    }
    else
    {
       lastgood=place;
       if( place->s==0)return lastplace;
       place=place->s;
    }
  }
}




//===============================[ P U B L I C ]



//this will give you a pointer to requested size of free memory and will lock it
void * locknew( long bytes )
{
  //first step : finding aproprate place (finding the vertex most not smaller than x)
  sizetreeelement * container= findcontainerfor( bytes);
  if(!container)return 0;

  //second step : subdivide free place into to pairs
  //1.Creating new poles...
  sizetreeelement * newsize=new sizetreeelement;
  positiontreeelement * newposition=new positiontreeelement;
  //2.Seting Them Up
  newsize->bind=newposition;
  newposition->bind=newsize;
  newsize->free=container->free-bytes;
  newsize->reserved=bytes;
  container->free=0;
  newposition->ptr=container->bind->ptr+container->reserved;
  newposition->b1=container->bind->b1;
  newposition->s1=container->bind;
  container->bind->b1=newposition;
  //3.Cuting container out off the tree becouse its outdated
  //3.1.Test if it is posible to easy remove
  if( container->b==0)
  {
     if( container->isb )
     {
       container->f->b=container->s;
       container->s->isb=1;
       container->s->f=container->f;
     }
     else
     {
       container->f->s=container->s;
       container->s->isb=0;
       container->s->f=container->f;
     }
     goto stepfor;
  }
  else
    if( container->s==0)
    {
       if( container->isb )
       {
         container->f->b=container->b;
         container->b->isb=1;
         container->b->f=container->f;
       }
       else
       {
         container->f->s=container->b;
         container->b->isb=0;
         container->b->f=container->f;
       }
       goto stepfor;
    } 
  
  
  //4.Inserting Both Elements To Both Trees
  stepfor

}
//this will automaticly check the lenght of given string and freeup unused memory
void clipstring( void * str )
{

}
//this will freeup the memory
void freemem( void * ptr )
{

}
//this will enlarge the amount of memory connected with given ptr - if posible it won't be blited
void enlarge( void * ptr, long newsize )
{

}