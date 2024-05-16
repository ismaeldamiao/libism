/* -----------------------------------------------------------------------------
   Typus Abstractus Dati (TAD)
   Componente para manipulacao de tipos abstratos de dados

   Ultima modificacao: 05 de maio de 2024.
----------------------------------------------------------------------------- */
#ifndef TAD_H
#define TAD_H 0

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __STDC__
# error "Essa interface necessita de um compilador compativel com o C padrao."
#endif /* __STDC__ */

#include <stddef.h>

enum tad_status_enum {
   tad_successus,
   tad_sine_memoria,
   tad_finitum_est
};

extern enum tad_status_enum tad_status;

/* ------------------------------------
   Tipo: Pilha (en: stack; la: stiva)
------------------------------------ */

typedef struct stiva_s stiva_t;

stiva_t* stiva_creare(void);
void     stiva_liberare(stiva_t*,void(*)(void*));

void     stiva_adicere(stiva_t*,void*,size_t);
void*    stiva_removere(stiva_t*,void*,size_t);

/* ------------------------------------
   Tipo: Fila (en: queue; la: fila)
------------------------------------ */

typedef struct fila_s fila_t;

fila_t* fila_creare(void);
void    fila_liberare(fila_t*,void(*)(void*));

void    fila_adicere(fila_t*,void*,size_t);
void*   fila_removere(fila_t*,void*,size_t);

/* ------------------------------------
   Tipo: Lista (en: list; la: index)
------------------------------------ */

typedef struct index_s index_t;

index_t* index_creare(void);
void     index_liberare(index_t*,void(*)(void*));

void     index_adicere(index_t*,void*,size_t,size_t);
void*    index_removere(index_t*,void*,size_t,size_t);

void*    index_accedere(index_t*,void*,size_t,size_t);
void     index_ambulator(index_t*,void(*)(void*));
size_t   index_dimensionem(const index_t*);
/* TODO:Renomear index_qsort. */
void     index_qsort(index_t*,int(*)(const void*,const void*));

/* ------------------------------------
   Tipo: Arvore (en: tree; la: arbor)
------------------------------------ */

typedef struct arbor_s arbor_t;

arbor_t* arbor_creare(void);
void     arbor_liberare(arbor_t*,void(*)(void*));

void     arbor_adicere(arbor_t*,void*,size_t);
void     arbor_inserere(arbor_t*,arbor_t*);

void*    arbor_accedere(arbor_t*,void*,size_t);
void     arbor_ambulator(arbor_t*,void(*)(arbor_t*));
index_t* arbor_filius(arbor_t*);

#ifdef __cplusplus
}
#endif

#endif /* TAD_H */
