#ifndef STATISTICA_H
#define STATISTICA_H

#if !defined(__STDC__)
# error "This libary need a standard compliant compiler."
#endif /* __STDC__ */

#include <stddef.h>

double statistica_media(const double*,size_t);
double statistica_variance(const double*,size_t);
void statistica_mediavariance(const double*,size_t,double*,double*);

void* statistica_moda(const void**,size_t,int(*)(const void*,const void*));

#endif /* STATISTICA_H */
