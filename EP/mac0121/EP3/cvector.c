#include "cvector.h"
#include <stdlib.h>

cvector newCVector(int sz)
{
    cvector ret = (cvector) malloc(sizeof(struct cvector_s));
    if(!ret) return ret;
    ret->data = (int*) malloc(sizeof(int)*sz);
    ret->sz = 0;
    if(!ret->data) return ret;
    ret->sz = sz;
    return ret;
}

void delCVector(cvector cv)
{
    if(!cv) return;
    free(cv->data);
    free(cv);
    cv = 0;
}

int atCVector(cvector cv, int i)
{
    if(i < 0 || !cv) return 0;
    return cv->data[i%cv->sz];
}

void setCVector(cvector cv, int i, int v)
{
    if(i < 0 || !cv) return;
    cv->data[i%cv->sz] = v;
}

void threeRotate(cvector cv, int i)
{
    int i0 = i;
    int i2 = i + 2;
    int tmp;
    if(i < 0 || !cv) return;
    tmp = atCVector(cv, i0);
    setCVector(cv, i0, atCVector(cv, i2));
    setCVector(cv, i2, tmp);
}
