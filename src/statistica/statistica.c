#include "statistica.h"

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#include <math.h>
#else
#define NAN (0.0 / 0.0)
#define INFINITY (1.0 / 0.0)
#define isnan(x) ((x) != (x))
#define isinf(x) ((!isnan(x)) && isnan((x) - (x)))
#endif /* ISO C99 */

#if ( \
   defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
   !defined(__STDC_NO_THREADS__))
#include <threads.h>
/*
https://stackoverflow.com/a/68364922
https://open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3631.pdf
https://stackoverflow.com/a/41146002
*/
#endif /* ISO C11 */

double statistica_media(const double *sample, size_t size){
   size_t i, j;
   double sum;

   if(!sample || (size == ((size_t)0))) return NAN;

   sum = 0.0;
   /* See:
      https://stackoverflow.com/a/1934266
      https://stackoverflow.com/a/68050984 */
   for(i = 0; i < size;){
      j = i + 1;
      sum += (sample[i] - sum) / (double)j;
      i = j;
   }

   return sum;
}

double statistica_variance(const double *sample, size_t size){
   size_t i, j;
   double sum, sum2;

   if(!sample || (size == ((size_t)0))) return NAN;

   sum = sum2 = 0.0;
   for(i = 0; i < size;){
      j = i + 1;
      sum += (sample[i] - sum) / (double)j;
      sum2 += (sample[i]*sample[i] - sum2) / (double)j;
      i = j;
   }

   return (sum2 - sum*sum);
}

void statistica_mediavariance
(const double *sample, size_t size, double *media, double *variance){
   size_t i, j;
   double sum, sum2;

   if((sample == NULL) || (size == ((size_t)0))){
      *media = NAN;
      *variance = NAN;
      return;
   }

   sum = sum2 = 0.0;
   for(i = 0; i < size;){
      j = i + 1;
      sum += (sample[i] - sum) / (double)j;
      sum2 += (sample[i]*sample[i] - sum2) / (double)j;
      i = j;
   }

   *media = sum;
   *variance = sum2 - sum*sum;

   return;
}
