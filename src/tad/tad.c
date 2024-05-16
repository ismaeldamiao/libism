#include "tad.h"

#ifdef __cplusplus
#define TAD_MALLOC(typus) ((typus*)malloc(sizeof(typus)))
#else
#define TAD_MALLOC(typus) malloc(sizeof(typus))
#endif /* __cplusplus */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <limits.h>
#include <stdint.h>
#endif /* __STDC_VERSION__ */

#if defined(SIZE_MAX) && (SIZE_MAX == UINT_MAX)
#define SIZE_C(x) x ## U
#elif defined(SIZE_MAX) && (SIZE_MAX == ULONG_MAX)
#define SIZE_C(x) x ## UL
#elif defined(SIZE_MAX) && (SIZE_MAX == ULLONG_MAX)
#define SIZE_C(x) x ## ULL
#else
#define SIZE_C(x) ((size_t)(x))
#endif /* SIZE_MAX */

enum tad_status_enum tad_status;

struct index_catenatus_s {
   struct index_catenatus_s *sequentis;
   void* elementum;
};

struct index_catenatus_duplex_s {
   struct index_catenatus_duplex_s *prioris, *sequentis;
   void* elementum;
};

static void* tad_memcpy(void *dest, const void *src, size_t len){
   unsigned char *dest_;
   const unsigned char *src_;

   dest_ = (unsigned char*)dest;
   src_ = (const unsigned char*)src;

   for(;len;--len){
      *dest_ = *src_;
      ++dest_;
      ++src_;
   }

   return dest;
}

static void tad_free(void* e){ (void)e; return; }

/* -----------------------------------------------------------------------------
   Tipo: Pilha (en: stack; la: stiva)
----------------------------------------------------------------------------- */

/* A pilha eh implementada como uma lista encadeada. */
struct stiva_s {
   /* A pilha eh implementada como uma lista encadeada. 
      O ponteiro para a lista serve para diminuir a quantidade
      de operacoes necessarias para empilhar e desempilhar. */
   struct index_catenatus_s *index;
};

struct stiva_s* stiva_creare(void){
   struct stiva_s *s;
   void* malloc(size_t);

   s = TAD_MALLOC(struct stiva_s);
   if(s != NULL) s->index = NULL;

   return s;
}

void stiva_liberare(struct stiva_s *s, void(*free_)(void*)){
   void free(void*);

   if(s == NULL) return;
   if(free_ == NULL) free_ = tad_free;

   if(s->index != NULL){ /* Se houver pelo menos um elemento... */
      /* Remove todos os elementos da pilha um a um. */
      struct index_catenatus_s *index_;
      do {
         free_(s->index->elementum);
         index_ = s->index;
         s->index = index_->sequentis;
         free(index_);
      } while(s->index);
   }
   free(s);

   return;
}

void stiva_adicere(struct stiva_s *s, void* elementum, size_t len){
   struct index_catenatus_s *index_;
   void* malloc(size_t);

   if((s == NULL) || (elementum == NULL)) return;

   /* Novo noh da lista encadeada. */
   index_ = TAD_MALLOC(struct index_catenatus_s);
   /* Rotina para empilhar... */
   if(index_ != NULL){
      /* Incerssao no inicio da lista encadeada. */
      index_->sequentis = s->index;
      s->index = index_;

      if(len > SIZE_C(0)){
         void* malloc(size_t);
         s->index->elementum = tad_memcpy(malloc(len), elementum, len);
      }else
         s->index->elementum = elementum;
   }

   return;
}

void* stiva_removere(struct stiva_s *s, void* elementum, size_t dim){
   struct index_catenatus_s *index_;
   void free(void*), *e;

   if((s == NULL) || (s->index == NULL)) return NULL;

   e = s->index->elementum;

   /* Remocao no inicio da lista encadeada. */
   index_ = s->index;
   if(s->index->sequentis)
      s->index = s->index->sequentis;
   else
      s->index = NULL;
   free(index_);

   if((dim > SIZE_C(0)) && (elementum != NULL)){
      tad_memcpy(elementum, e, dim);
      free(e);
   }

   return e;
}

/* -----------------------------------------------------------------------------
   Tipo: Fila (en: queue; la: fila)
----------------------------------------------------------------------------- */

/* A fila eh implementada como una lista encadeada. */
struct fila_s {
   /* Para que as operacoes de incerssao e remocao sejam ambas O(1)
      ponteiros sao dados para o inicio e para o final da lista. */
   struct index_catenatus_s *primus, *ultimus;
};

struct fila_s* fila_creare(void){
   struct fila_s *f;
   void* malloc(size_t);

   f = TAD_MALLOC(struct fila_s);
   if(f != NULL) f->primus = f->ultimus = NULL;

   return f;
}

void fila_liberare(struct fila_s *f, void(*free_)(void*)){
   void free(void*);

   if(f == NULL) return;
   if(free_ == NULL) free_ = tad_free;

   if(f->primus != NULL){ /* Se houver pelo menos um elemento... */
      /* Remove todos os elementos da fila um a um. */
      struct index_catenatus_s *index_;
      do {
         free_(f->primus->elementum);
         index_ = f->primus;
         f->primus = index_->sequentis;
         free(index_);
      } while(f->primus);
   }
   free(f);

   return;
}

void fila_adicere(struct fila_s *f, void* elementum, size_t len){
   struct index_catenatus_s *index_;
   void* malloc(size_t);

   if((f == NULL) || (elementum == NULL)) return;

   /* Novo noh da lista encadeada. */
   index_ = TAD_MALLOC(struct index_catenatus_s);
   /* Rotina para enfileirar... */
   if(index_ != NULL){
      /* Incerssao no final da lista encadeada. */
      index_->sequentis = NULL;
      if(f->ultimus) /* Se houver pelo menos um elemento... */
         f->ultimus->sequentis = index_;
      else
         f->primus = index_;
      f->ultimus = index_;

      if(len > SIZE_C(0)){
         void* malloc(size_t);
         f->ultimus->elementum = tad_memcpy(malloc(len), elementum, len);
      }else
         f->ultimus->elementum = elementum;
   }

   return;
}

void* fila_removere(struct fila_s *f, void* elementum, size_t dim){
   struct index_catenatus_s *index_;
   void free(void*), *e;

   if((f == NULL) || (f->primus == NULL)) return NULL;

   e = f->primus->elementum;

   /* Remocao no inicio da lista encadeada. */
   index_ = f->primus;
   if(f->primus->sequentis)
      f->primus = f->primus->sequentis;
   else
      f->primus = f->ultimus = NULL;
   free(index_);

   if((dim > SIZE_C(0)) && (elementum != NULL)){
      tad_memcpy(elementum, e, dim);
      free(e);
   }

   return e;
}

/* -----------------------------------------------------------------------------
   Tipo: Lista (en: list; la: index)
----------------------------------------------------------------------------- */

/* A lista eh implementada como uma lista duplamente encadeada. */
struct index_s {
   struct index_catenatus_duplex_s *primus, *ultimus;
   size_t dimensionem;
};

struct index_s* index_creare(void){
   struct index_s *index;
   void* malloc(size_t);

   index = TAD_MALLOC(struct index_s);
   if(index != NULL){
      index->dimensionem = (size_t)0;
      index->primus = index->ultimus = NULL;
   }

   return index;
}

void index_liberare(struct index_s *index, void(*free_)(void*)){
   void free(void*);

   if(index == NULL) return;
   if(free_ == NULL) free_ = tad_free;

   if(index->primus != NULL){
      /* Remove todos os elementos da lista um a um. */
      struct index_catenatus_duplex_s *index_;
      do {
         free_(index->primus->elementum);
         index_ = index->primus;
         index->primus = index_->sequentis;
         free(index_);
      } while(index->primus);
   }
   free(index);

   return;
}

void index_adicere
(struct index_s *index, void* elementum, size_t i, size_t len){
   struct index_catenatus_duplex_s *index_;
   void* malloc(size_t);

   if((index == NULL) || (elementum == NULL)) return;

   /* Novo noh da lista duplamente encadeada. */
   index_ = TAD_MALLOC(struct index_catenatus_duplex_s);
   /* Rotina para adicionar ah lista... */
   if(index_ != NULL){
      if(i == SIZE_C(0)){
         /* Incerssao no inicio da lista duplamente encadeada. */
         index_->prioris = NULL;
         index_->sequentis = index->primus;
         if(index->primus) /* Se houver pelo menos um elemento. */
            index->primus->prioris = index_;
         else
            index->ultimus = index_;
         index->primus = index_;
      }else if (i >= index->dimensionem) {
         /* Incerssao no final da lista duplamente encadeada. */
         index_->prioris = index->ultimus;
         index_->sequentis = NULL;
         if(index->ultimus) /* Se houver pelo menos um elemento. */
            index->ultimus->sequentis = index_;
         else
            index->primus = index_;
         index->ultimus = index_;
      }else{
         struct index_catenatus_duplex_s *index__;
         size_t j;
         if(i <= (index->dimensionem / SIZE_C(2))){
            /* Incerssao na primeira metade da lista duplamente encadeada. */
            index__ = index->primus;
            for(j = SIZE_C(0);j < i; ++j)
               index__ = index__->sequentis;
         }else{
            /* Incerssao na segunda metade da lista duplamente encadeada. */
            index__ = index->ultimus;
            for(j = index->dimensionem - SIZE_C(1);j > i; --j)
               index__ = index__->prioris;
         }
         index_->sequentis = index__;
         index_->prioris = index__->prioris;
         index_->prioris->sequentis = index_;
         index__->prioris = index_;
      }
      ++(index->dimensionem);

      if(len > SIZE_C(0)){
         void* malloc(size_t);
         index_->elementum = tad_memcpy(malloc(len), elementum, len);
      }else
         index_->elementum = elementum;
   }

   return;
}

void* index_removere
(struct index_s *index, void* elementum, size_t dim, size_t i){
   void free(void*), *e;
   struct index_catenatus_duplex_s *index_;
   size_t j;

   if((index == NULL) || (index->primus == NULL) || (i >= index->dimensionem))
      return NULL;

   /* Rotina para 'caminhar' ateh o elemento que deve ser removido, index_. */
   if(i < (index->dimensionem / SIZE_C(2))){
      j = (size_t)0;
      /* Remocao na primeira metade da lista duplamente encadeade. */
      if(i != j){
         index_ = index->primus;
         for(; j <= i; ++j) index_ = index_->sequentis;
         index_->sequentis->prioris = index_->prioris;
         index_->prioris->sequentis = index_->sequentis;
      }else{ /* Quando quer-se remover o primeiro elemento... */
         index_ = index->primus;
         if(index->primus->sequentis){
            index->primus->sequentis->prioris = NULL;
            index->primus = index->primus->sequentis;
         }else
            index->primus = index->ultimus = NULL;
      }
   }else{
      j = index->dimensionem - SIZE_C(1);
      /* Remocao na segunda metade da lista duplamente encadeade. */
      if(i != j){
         index_ = index->ultimus;
         for(; j >= i; --j) index_ = index_->prioris;
         index_->sequentis->prioris = index_->prioris;
         index_->prioris->sequentis = index_->sequentis;
      }else{ /* Quando quer-se remover o ultimo elemento... */
         index_ = index->ultimus;
         if(index->ultimus->prioris){
            index->ultimus->prioris->sequentis = NULL;
            index->ultimus = index->ultimus->prioris;
         }else
            index->primus = index->ultimus = NULL;
      }
   }

   e = index_->elementum;
   free(index_);
   --(index->dimensionem);

   if((dim > SIZE_C(0)) && (elementum != NULL)){
      tad_memcpy(elementum, e, dim);
      free(e);
   }

   return e;
}

/* Mesma implementacao que index_removere, mas sem a remocao. */
void* index_accedere
(struct index_s *index, void* elementum, size_t dim, size_t i){
   struct index_catenatus_duplex_s *index_;
   size_t j;

   if((index == NULL) || (index->primus == NULL) || (i >= index->dimensionem))
      return NULL;

   if(i < (index->dimensionem / 2)){
      index_ = index->primus;
      for(j = SIZE_C(0); j < i; ++j) index_ = index_->sequentis;
   }else{
      index_ = index->ultimus;
      for(j = index->dimensionem - SIZE_C(1); j > i; --j)
         index_ = index_->prioris;
   }

   if((dim > SIZE_C(0)) && (elementum != NULL))
      tad_memcpy(elementum, index_->elementum, dim);

   return index_->elementum;
}

void index_ambulator(struct index_s *index, void (*fac_aliquid)(void*)){
   struct index_catenatus_duplex_s *index_;

   if((index == NULL) || (fac_aliquid == NULL)) return;
   if(index->primus == NULL) return;

   index_ = index->primus;

   tad_status = tad_successus;
   do {
      fac_aliquid(index_->elementum);
      if(tad_status == tad_finitum_est) break;
      index_ = index_->sequentis;
   } while(index_);

   return;
}

size_t index_dimensionem(const index_t *index){
   if(index == NULL) return SIZE_C(0);
   return index->dimensionem;
}

void index_qsort(index_t *index, int(*cmp)(const void*,const void*)){
   void *tmp;
   struct index_catenatus_duplex_s *index_, *inicio, *final, *menor, *maior;

   if((index == NULL) || (index->dimensionem < (size_t)2)) return;

   inicio = index->primus;
   final = index->ultimus;

   while(!((inicio == final) || (inicio == final->sequentis))){

      if(cmp(inicio->elementum, final->elementum) > 0){
         maior = inicio;
         menor = final;
      }else{
         maior = final;
         menor = inicio;
      }

      index_ = inicio->sequentis;
      while(index_ != final){
         if(cmp(index_->elementum, menor->elementum) < 0)
            menor = index_;
         if(cmp(index_->elementum, maior->elementum) > 0)
            maior = index_;
         index_ = index_->sequentis;
      }

      tmp = inicio->elementum;
      inicio->elementum = menor->elementum;
      menor->elementum = tmp;
      if(maior == inicio) maior = menor;

      tmp = final->elementum;
      final->elementum = maior->elementum;
      maior->elementum = tmp;

      inicio = inicio->sequentis;
      final = final->prioris;
   }

   return;
}

/* -----------------------------------------------------------------------------
   Tipo: Arvore (en: tree; la: arbor)
----------------------------------------------------------------------------- */

/* A arvore eh implementada com duas listas duplamente encadeadas,
   uma para caminhar entre os leveis e uma para caminhar entre os irmaos.  */
struct arbor_s {
   struct arbor_s *parentem, *primus_filius, *fratrem_prior, *fratrem_proximum;
   void* elementum;
};

struct arbor_s* arbor_creare(void){
   struct arbor_s *radix;
   void* malloc(size_t);

   radix = TAD_MALLOC(struct arbor_s);
   if(radix != NULL){
      radix->parentem = radix->primus_filius = NULL;
      radix->fratrem_prior = radix->fratrem_proximum = NULL;
      radix->elementum = NULL;
   }

   return radix;
}

void arbor_liberare(struct arbor_s *arbor, void(*free_)(void*)){
   void free(void*);

   if((arbor == NULL) || (arbor->elementum == NULL)) return;
   if(free_ == NULL) free_ = tad_free;

   /* Corta a arvore do tronco, caso trate-se de uma sub-arvore. */
   if(arbor->parentem){
      if(arbor->fratrem_prior)
         arbor->fratrem_prior->fratrem_proximum = arbor->fratrem_proximum;
      else
         arbor->parentem->fratrem_prior = NULL;
      arbor->parentem = NULL;
   }

   /* Remove os elementos da arvore um a um (ver arbor_ambulator). */
   do {
      if(arbor->primus_filius) arbor = arbor->primus_filius;
      else if(arbor->fratrem_proximum) arbor = arbor->fratrem_proximum;
      else if(arbor->fratrem_prior){
         free_(arbor->elementum);
         arbor = arbor->fratrem_prior;
         free(arbor->fratrem_proximum);
         arbor->fratrem_proximum = NULL;
      }else if(arbor->parentem){
         free_(arbor->elementum);
         arbor = arbor->parentem;
         free(arbor->primus_filius);
         arbor->primus_filius = NULL;
      }else{
         free_(arbor->elementum);
         free(arbor);
         arbor = NULL;
      }
   } while(arbor);

   return;
}

void arbor_adicere(struct arbor_s *arbor, void* elementum, size_t len){

   if((arbor == NULL) || (elementum == NULL)) return;

   /* Rotina para 'caminhar' ateh a arvore onde o elemento serah adicionado. */
   if(arbor->elementum != NULL){ /* Caso jah haja informacao na raiz. */
      void*malloc(size_t);

      if(arbor->primus_filius){
         /* Cria mais um filho. */
         arbor = arbor->primus_filius;
         while(arbor->fratrem_proximum) arbor = arbor->fratrem_proximum;
         arbor->fratrem_proximum = TAD_MALLOC(struct arbor_s);
         if(arbor->fratrem_proximum == NULL) return;
         arbor->fratrem_proximum->fratrem_prior = arbor;
         arbor->fratrem_proximum->parentem = arbor->parentem;
         arbor->fratrem_proximum->fratrem_proximum = NULL;
         arbor->fratrem_proximum->primus_filius = NULL;
         arbor = arbor->fratrem_proximum;
      }else{
         /* Cria o primeiro filho. */
         arbor->primus_filius = TAD_MALLOC(struct arbor_s);
         if(arbor->primus_filius == NULL) return;
         arbor->primus_filius->parentem = arbor;
         arbor->primus_filius->primus_filius = NULL;
         arbor->primus_filius->fratrem_prior = NULL;
         arbor->primus_filius->fratrem_proximum = NULL;
         arbor = arbor->primus_filius;
      }
   }

   if(len > SIZE_C(0)){
      void* malloc(size_t);
      arbor->elementum = tad_memcpy(malloc(len), elementum, len);
   }else
      arbor->elementum = elementum;

   return;
}

void arbor_inserere(struct arbor_s *truncus, struct arbor_s *surculus){

   if((truncus == NULL) || (surculus == NULL))
      return;
   if((truncus->elementum == NULL) || (surculus->elementum == NULL))
      return;

   /* Rotina para fazer o enxerto de surculus em truncus. */
   if(truncus->primus_filius){
      struct arbor_s *arbor_;
      arbor_ = truncus->primus_filius;
      while(arbor_->fratrem_proximum) arbor_ = arbor_->fratrem_proximum;
      arbor_->fratrem_proximum = surculus;
      surculus->fratrem_prior = arbor_;
   }else
      truncus->primus_filius = surculus;
   surculus->parentem = truncus;

   return;
}

void* arbor_accedere(arbor_t *arbor, void* elementum, size_t len){
   if((arbor == NULL) || (arbor->elementum == NULL)) return NULL;

   if((len > SIZE_C(0)) && (elementum != NULL))
      tad_memcpy(elementum, arbor->elementum, len);

   return arbor->elementum;
}

void arbor_ambulator(struct arbor_s *arbor, void (*fac_aliquid)(arbor_t*)){

   if((arbor == NULL) || (fac_aliquid == NULL)) return;
   if(arbor->elementum == NULL) return;

   tad_status = tad_successus;
   do {
      fac_aliquid(arbor);
      if(tad_status == tad_finitum_est) break;
      if(arbor->primus_filius) arbor = arbor->primus_filius;
      else if(arbor->fratrem_proximum) arbor = arbor->fratrem_proximum;
      else for(;;){
         arbor = arbor->parentem;
         if(!arbor) break;
         if(arbor->fratrem_proximum){
            arbor = arbor->fratrem_proximum;
            break;
         }
      }
   } while(arbor);

   return;
}

index_t* arbor_filius(arbor_t* arbor){
   index_t *index;

   if((arbor == NULL) || (arbor->primus_filius == NULL)) return NULL;

   index = index_creare();
   if(index == NULL) return NULL;

   arbor = arbor->primus_filius;

   do {
      index_adicere(index, arbor, index->dimensionem, SIZE_C(0));
   } while((arbor = arbor->fratrem_proximum));

   return index;
}
