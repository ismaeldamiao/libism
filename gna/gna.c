#include <stdlib.h>
#include <limits.h>

#if defined(USE_STATIC)
static
#endif
double gna_std(int *word)
{
   static int start = 1;
#define random_int (*(word))
   if((random_int < 0) || start){
      srand((unsigned)random_int);
      start = 0;
   }
   random_int = rand();
   return ((double)random_int / (double)RAND_MAX);
#undef random_int
}

/* C89 implementation of LCG */

#if defined(USE_STATIC)
static
#endif
double gna_lcg(unsigned int *word)

#if (UINT_MAX == 0xffff)
/* Word size 16-bit
   Parameters from:
   https://www.cs.rice.edu/~johnmc/comp528/lecture-notes/Lecture21.pdf
   Period: */
#  define multiplier 0x6255U
#  define inclement 0x3619U
#  define modulus 0xffffU
#elif (UINT_MAX == 0xffffffff)
/* Word size 32-bit
   Parameters from: Suggestion in the ISO/IEC 9899
   Period: */
#  define multiplier 0x41c64e6dU
#  define inclement 0x00003039U
#  define modulus 0x80000000U
#elif (UINT_MAX == 0xffffffffffff)
/* Word size 48-bit
   Parameters from: https://nuclear.llnl.gov/CNP/rng/rngman/node5.html
   Period: 2^48 */
#  define multiplier 0x2875a2e7b175U
#  define inclement 0x000000b504efU
#  define modulus 0xffffffffffffU
#elif (UINT_MAX == 0xffffffffffffffff)
/* Word size 64-bit
   Parameters from: https://nuclear.llnl.gov/CNP/rng/rngman/node4.html
   Period: 2^64 */
#  define multiplier 0x27bb2ee687b0b0fdU
#  define inclement 0x00000000b504f32dU
#  define modulus 0xffffffffffffffffU
#endif /* UINT_MAX */

{

#define random_int (*(word))
   random_int = (multiplier * random_int + inclement) % modulus;
   return ((double)random_int) / ((double)modulus);
#undef random_int

}

#undef multiplier
#undef inclement
#undef modulus

/* C89 implementation of Mersenne Twister */

#if defined(USE_STATIC)
static
#endif
double gna_mt19937(unsigned long int *word)

#if (ULONG_MAX == 0xffffffff)
/* Word size 32-bit
   Parameters from: https://en.wikipedia.org/wiki/Mersenne_Twister */
# define W2                 30

# define UPPER_MASK         0x80000000UL /* most significant w-r bits */
# define LOWER_MASK         0x7fffffffUL /* least significant r bits */

# define N                  624
# define M                  397
# define MATRIX_A           0x9908b0dfUL
# define TEMPERING_MASK_D   0xffffffffUL
# define TEMPERING_MASK_B   0x9d2c5680UL
# define TEMPERING_MASK_C   0xefc60000UL
# define TEMPERING_U        11
# define TEMPERING_S        7
# define TEMPERING_T        15
# define TEMPERING_L        18
# define INITIALIZATION_F   0x6c078965UL
#elif (ULONG_MAX == 0xffffffffffffffff)
/* Word size 64-bit
   Parameters from: T. Nishimura, "Tables of 64-bit Mersenne Twisters" */
# define W2                62

# define UPPER_MASK        0xffffffff80000000UL /* most significant w-r bits */
# define LOWER_MASK        0x000000007fffffffUL /* least significant r bits */

# define N                 312
# define M                 156
# define MATRIX_A          0xb5026f5aa96619e9UL
# define TEMPERING_MASK_D  0xffffffffffffffffUL
# define TEMPERING_MASK_B  0xd66b5ef5b4da0000UL
# define TEMPERING_MASK_C  0xfded6be000000000UL
# define TEMPERING_U       29
# define TEMPERING_S       17
# define TEMPERING_T       37
# define TEMPERING_L       41
# define INITIALIZATION_F  0x5851f42d4c957f2dUL
#endif

#define random_int   (*(word))
#define DEFAULT_SEED 1999UL

/* This function combines the top bit of x with the bottom r bits of y. */
#define COMBINE_BITS(x, y) (((x) & UPPER_MASK) | ((y) & LOWER_MASK))

{
   int i;
   static unsigned long int mt[N]; /* the array for the state vector */
   static int mti = N+1; /* mti==N+1 means mt[N] is not initialized */

   /* The following routine generate N words at one time */
   if(mti >= N){

      /* If mti == N+1 then the function is called by the first time and the
         array mt[] need to be initialized.
         The value pointed by 'word' in the firt call
         is the seed of generator, if this value is 0 then set it to 1999. */
      if(mti == N+1){ /* initializing the array with NONZERO seed */
         if(!random_int) random_int = DEFAULT_SEED;
         mt[0] = random_int;
         for(mti = 1; mti < N; ++mti)
         mt[mti] = INITIALIZATION_F * (mt[mti-1] ^ (mt[mti-1] >> W2)) + mti;
      }

      /* With the array mt[] already initialized, generate the words. */
      for(i = 0; i < N; ++i){
         random_int = COMBINE_BITS(mt[i], mt[(i+1) % N]);
         mt[i] = mt[(i+M) % N] ^
         (!(random_int % 2) ?
         ((random_int >> 1) ^ MATRIX_A) : (random_int >> 1));
      }
      mti = 0;
   }

   /* Extract tempered value of mt[mti]. */
   random_int = mt[mti];

#if (TEMPERING_MASK_D == ULONG_MAX)
   random_int ^= (random_int >> TEMPERING_U);
#else
   random_int ^= (random_int >> TEMPERING_U) & TEMPERING_MASK_D;
#endif
   random_int ^= (random_int << TEMPERING_S) & TEMPERING_MASK_B;
   random_int ^= (random_int << TEMPERING_T) & TEMPERING_MASK_C;
   random_int ^= (random_int >> TEMPERING_L);
   ++mti;

   return ((double)random_int) / ((double)ULONG_MAX);
}

#undef W2

#undef UPPER_MASK
#undef LOWER_MASK

#undef N
#undef M
#undef MATRIX_A
#undef TEMPERING_MASK_D
#undef TEMPERING_MASK_B
#undef TEMPERING_MASK_C
#undef TEMPERING_U
#undef TEMPERING_S
#undef TEMPERING_T
#undef TEMPERING_L
#undef INITIALIZATION_F

#undef random_int
#undef DEFAULT_SEED
#undef COMBINE_BITS
