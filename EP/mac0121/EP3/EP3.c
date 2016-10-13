#include "cvector.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef char bool;
const bool true = 1;
const bool false = 0;

int compare (const void * a, const void * b)
{
	  return ( *(int*)a - *(int*)b );
}

void ordenateOdd(cvector list, int sz)
{
	bool changed;
	int i;
	int k;
	do {
		changed = false;
		for(i = 0; i < sz - 1; i++)
		{
			if(i < sz - 2 && atCVector(list, i) > atCVector(list, i + 2)) 
			{
				threeRotate(list, i);
				changed = true;
			}
			else if(atCVector(list, i) > atCVector(list, i + 1))
			{
				for(k = 0; k < (sz + 1)/2; k++) 
				{
					threeRotate(list, i + 2*k);
					printf("Rotating %d\n", i + 2*k);
				}
				for(k -= 2; k >= 0; k--) threeRotate(list, i + 2*k);
				changed = true;
			}
		}
	} while(changed);
}

void ordenateEven(cvector list, int sz)
{
	int i;
	int* ordered = malloc(sz*sizeof(int));
	for(i = 0; i < sz; i++) ordered[i] = atCVector(list, i);
	qsort(ordered, sz, sizeof(int), compare);
	
}

int main()
{
	int sz;
	int i;
	cvector list;
	scanf("%d", &sz);

	list = newCVector(sz);

	for (i = 0; i < sz; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		setCVector(list, i, tmp);
	}

	if(sz % 2) ordenateOdd(list, sz);

	for(i = 0; i < sz; i++)
	{
		printf("%d ", atCVector(list, i));
	}
	printf("\n");
	return 0;
}
