/*
struct node
{
  node * child[256];
  long  value;
};

node * root;


void add23(node *& root,char * who,long value)
{
    if(root==0)root =malloc node;
    if(*who==0)
        root->value=value;
    else
        add23(root->child[*who],who+1,value);
}

int main()
{
    add23( root, "qbolec" , 1358885 );
    return 0;
}
*/
#define list_ struct list
struct list
{
    list_ * next;
    long value;
};

list_ * head=0;//head bedzie wskaznikiem do glowy listy ale na razie nie ma zadnej listy!

void add2list( long v )//dodawanie liczby do listy
{
    list_ * newelement= malloc(sizeof(list_));
    (*newelement).next=head;
    (*newelement).value=v;
    //a teraz new element bedzie g³ow¹
    head=newelement;
}
int existinlist( long v)
{
    list_ * suwak=head;
    while(suwak)
    {
        if( (*suwak).value==v )return 1;
        suwak=(*suwak).next;
    }
    return 0;
}
void deletefromlist( long v)
{
    if((*head).value==v)
    {//akurat pech bo to g³owe czeba skasowac:
        head=(*head).next;//i po k³opocie:)
    }
    else
    {
        list_ * poprzedni=head;
        list_ * ten=(*poprzedni).next;
        while(ten)
        {
            if( (*ten).value==v )
            {//znalezlismy
                (*poprzedni).next=(*ten).next;
                return;
            }
            poprzedni=ten;
            ten=(*ten).next;
        }
    }

}

