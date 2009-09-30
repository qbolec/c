#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
//#include <time.h>
#define ILE 10000000

int tab[ILE];

typedef struct
  {
    int *lo;
    int *hi;
  } stackstr;

#define SWAP(a, b) {int c=*b;*b=*a;*a=c;}
#define MIN_QSORT 4
#define STACK_SIZE	(8 * sizeof(unsigned long int))
#define PUSH(low, high)	((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define	POP(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))
#define	STACK_NOT_EMPTY	(stack < top)
#define min(x, y) ((x) < (y) ? (x) : (y))

void vs_qs(int *tab, int size)
{
	int pivot;

	if(size==0) return;
	if(size > MIN_QSORT)
	{
	    stackstr stack[STACK_SIZE];
		stackstr *top = stack+1;
		int *lo = tab;
		int *hi = tab + size - 1;

		while(STACK_NOT_EMPTY)
		{
			int *left, *right;
			int *mid = lo + ((hi-lo)>>1);

			if(*mid<*lo) SWAP(mid, lo);
			if(*mid>*hi)
			{
				SWAP(mid, hi);
				if(*mid<*lo) SWAP(mid, lo);
			}
			left=lo+1;
			right=hi-1;
			pivot=*mid;

			do{
				while(*left<pivot)left++;
				while(*right>pivot)right--;
				if(left<right)
				{
					SWAP(left, right);
					left++;
					right--;
				}
				else if(left==right)
				{
					left++;
					right++;
					break;
				}
			} while(left<=right);

			if((right-lo)<=MIN_QSORT)
			{
				if((hi-left)<=MIN_QSORT)
				POP(lo, hi);
				else lo=left;
			}
			else if((hi-left)<=MIN_QSORT)
				hi = right;
			else if((right-lo)>(hi-left))
			{
				PUSH(lo, right);
				lo=left;
			}
			else
			{
				PUSH(left, hi);
				hi=right;
			}
		}
	}

	/* dla reszty - insertsort */
	{
		int *end = tab + size - 1;
		int *tmp = tab;
		int *hm = min(end, tab + MIN_QSORT);
		int *run;

		for(run=tmp+1; run<= hm; run++)
			if(*run<*tmp) tmp=run;

		if(tmp!=tab)
			SWAP(tmp, tab);

		run=tab+1;
		while(++run<=end)
		{
			tmp=run-1;
			while(*run<*tmp)tmp--;
			tmp++;
			if(tmp!=run)
			{
				int *x;
				x=run+1;
				while(--x>=run)
				{
					int c=*x;
					int *hi, *lo;
					for(hi=lo=x; --lo>=tmp;hi=lo) *hi=*lo;
					*hi=c;
				}
			}
		}
	}
}
int main (void)
{
    struct timeval s1, s2;
    struct timezone a;
    int *w;
    for (w = tab + ILE - 1; w > tab; w--) {
        *w = rand ();
    }
    gettimeofday (&s1, &a);
    vs_qs (tab, ILE);
    gettimeofday (&s2, &a);
    printf ("czas %ld mikrosekund\n", s2.tv_usec - s1.tv_usec + (s2.tv_sec - s1.tv_sec) * 1000000);
    return 0;
}
