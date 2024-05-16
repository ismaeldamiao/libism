# Typus Abstractus Dati `<tad.h>`

*Typus Abstractus Dati*, ou TAD,
é uma biblioteca para manipulação de tipos abstratos de dados.

## Visão geral

### Compatibilidade

Todos os nomes iniciados com `tad_`, `TAD_`,
`stiva_`, `fila_`, `index_` e `arbor_`
estão reservados para o futuro
uso da biblioteca TAD,
utilizá-los pode gerar um *comportamento indefinido*.

### Macros

A única macro definida em `<tad.h>` é `TAD_H`,
que serve para indicar a presença da biblioteca.

### Variáveis globais

Na biblioteca TAD
é definida a seguinte variável global.

```c
extern enum tad_status_enum tad_status;
```

Sua utilidade é informar eventuais erros durante a execução.

### Tipos de dados

Os seguintes tipos de dados devem ser suportados pela biblioteca
e são incompletos (opacos) na interface `<tad.h>`.

```c
typedef struct stiva_s   stiva_t;   // Pilha
typedef struct fila_s    fila_t;    // Fila
typedef struct index_s   index_t;   // Lista
typedef struct arbor_s   arbor_t;   // Arvore
```

Semântica:

* `stiva_t`
   é um tipo de dado utilizado para manipular pilhas de ponteiros.
* `fila_t`
   é um tipo de dado utilizado para manipular filas de ponteiros.
* `index_t`
   é um tipo de dado utilizado para manipular listas de ponteiros.
* `arbor_t`
   é um tipo de dado utilizado para manipular árvores com ponteiros nos nós.

### Terminologia

Os tipos abstratos de dados podem ser utilizados para armazenar vários
tipos de informação, para isso é amplamente utilizado
o ponteiro do tipo `void*`.
No contexto da TAD, o valor apontado por um ponteiro do tipo `void*`
será chamado de *dado*,
o *tamanho* do dado é a quantidade de bytes necessária para armazenar
o dado em uma variável.


## Pilhas

Define-se uma *pilha* como um conjunto mutável com duas operações, a saber,
uma para adicionar um elemento ao conjunto e uma para remover o último
elemento adicionado.

### A função `stiva_creare`

* Escopo:
   ```c
   stiva_t* stiva_creare(void)
   ```
* Funcionalidade:
   * Aloca memória para uma pilha e a inicializa vazia.
* Retorno:
   * A função `stiva_creare` retorna o ponteiro para a pilha.

### A rotina `stiva_adicere`

* Escopo:
   ```c
   void stiva_adicere(stiva_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma pilha previamente criada.
   * `e`: ponteiro para o dado que se quer armazenar na pilha.
   * `t`: tamanho do dado, caso se queira fazer uma cópia dele.
* Funcionalidade:
   * Se `t == 0` então `stiva_adicere`
      adiciona à pilha um ponteiro para o dado.
   * Se `t > 0` então `stiva_adicere`
      adiciona à pilha um ponteiro para uma cópia do dado.
* Observações:
   * A complexidade da implementação não deve ser superior a $\mathcal{O}(1)$.
   * Utilizar `t > 0` com `t` diferente do tamanho do dado apontado por `e`
      pode gerar um *comportamento indefinido*.

### A função `stiva_removere`

* Escopo:
   ```c
   void* stiva_removere(stiva_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma pilha previamente criada.
   * `e`: ponteiro para uma variável capaz de armazenar o dado que se quer obter.
   * `t`: tamanho do dado que se quer obter.
* Funcionalidade:
   * Remove o último elemento adicionado à pilha
      (o último a entrar é o primeiro a sair).
   * Quando `t > 0` a variável apontada por `e` recebe uma cópia do dado
      apontado pelo último ponteiro adicionado à pilha.
* Retorno:
   * A função `stiva_removere` retorna o último ponteiro adicionado à pilha.
   * Se`p == NULL` ou se a pilha está vazia então a função retorna `NULL`.
* Observações:
   * A complexidade da implementação não deve ser superior a $\mathcal{O}(1)$.
   * Em geral, quando se usa `t == 0`,
      pode ser necessário liberar a memória retornada antes de
      terminar o programa.
   * Em geral, usa-se `t > 0` para remover um elemento sempre que se utilizou
      `t > 0` para adicionar um elemento, utilizando o mesmo valor de `t` em
      ambos os casos, utilizar um valor diferente para `t` pode gerar um
      *comportamento indefinido*.

### A rotina `stiva_liberare`

* Escopo:
   ```c
   void stiva_liberare(stiva_t *p, void(*free_)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma pilha previamente criada.
* Funcionalidade:
   * Libera a memória alocada para a pilha apontada por `p`
      e chama a função `free_` usando cada elemento da pilha como argumento.
* Observações:
   * Uma possível implementação é apresentada abaixo.
      ```c
      void stiva_liberare(stiva_t *p, void(*free_)(void*)){
         void* e;

         if(p == NULL) return;

         if(free_ != NULL){
            for(;;){
               e = stiva_removere(p, NULL, (size_t)0);
               if(e != NULL) free_(e);
               else break;
            }
         }else{
            for(;;){
               e = stiva_removere(p, NULL, (size_t)0);
               if(e == NULL) break;
            }
         }
         free(p);

         return;
      }
      ```

## Filas

Define-se uma *fila* como um conjunto mutável com duas operações, a saber,
uma para adicionar um elemento ao conjunto e uma para remover o mais antigo
elemento adicionado que ainda não tenha sido removido.

### A função `fila_creare`

* Escopo:
   ```c
   fila_t* fila_creare(void)
   ```
* Funcionalidade:
   * Aloca memória para uma fila e a inicializa vazia.
* Retorno:
   * A função `fila_creare` retorna o ponteiro para a fila.

### A rotina `fila_adicere`

* Escopo:
   ```c
   void fila_adicere(fila_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma fila previamente criada.
   * `e`: ponteiro para o dado que se quer armazenar na pilha.
   * `t`: tamanho do dado, caso se queira fazer uma cópia dele.
* Funcionalidade:
   * Se `t == 0` então `fila_adicere`
      adiciona à fila um ponteiro para o dado.
   * Se `t > 0` então `fila_adicere`
      adiciona à fila um ponteiro para uma cópia do dado.
* Observações:
   * A complexidade da implementação não deve ser superior a $\mathcal{O}(1)$.
   * Utilizar `t > 0` com `t` diferente do tamanho do dado apontado por `e`
      pode gerar um *comportamento indefinido*.

### A função `fila_removere`

* Escopo:
   ```c
   void* fila_removere(fila_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma fila previamente criada.
   * `e`: ponteiro para uma variável capaz de armazenar o dado que se quer obter.
   * `t`: tamanho do dado que se quer obter.
* Funcionalidade:
   * Remove o mais antigo elemento adicionado à fila
      (o primeiro a entrar é o primeiro a sair).
   * Quando `t > 0` a variável apontada por `e` recebe uma cópia do dado
      apontado pelo último ponteiro adicionado à fila.
* Retorno:
   * A função `fila_removere` retorna o mais antigo ponteiro adicionado à pilha.
   * Se`p == NULL` ou se a fila está vazia então a função retorna `NULL`.
* Observações:
   * A complexidade da implementação não deve ser superior a $\mathcal{O}(1)$.
   * Em geral, quando se usa `t == 0`
      pode ser necessário liberar a memória retornada antes de
      terminar o programa.
   * Em geral, usa-se `t > 0` para remover um elemento sempre que se utilizou
      `t > 0` para adicionar um elemento, utilizando o mesmo valor de `t` em
      ambos os casos, utilizar um valor diferente para `t` pode gerar um
      *comportamento indefinido*.

### A rotina `fila_liberare`

* Escopo:
   ```c
   void fila_liberare(fila_t *p, void(*free_)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma pilha previamente criada.
* Funcionalidade:
   * Libera a memória alocada para a fila apontada por `p`
      e chama a função `free_` usando cada elemento da fila como argumento.
* Observações:
   * Uma possível implementação é apresentada abaixo.
      ```c
      void fila_liberare(fila_t *p, void(*free_)(void*)){
         void* e;

         if(p == NULL) return;

         if(free_ != NULL){
            for(;;){
               e = fila_removere(p, NULL, (size_t)0);
               if(e != NULL) free_(e);
               else break;
            }
         }else{
            for(;;){
               e = fila_removere(p, NULL, (size_t)0);
               if(e == NULL) break;
            }
         }
         free(p);

         return;
      }
      ```

## Listas

Define-se uma *lista* como um conjunto enumerado mutável com duas operações,
a saber, uma para adicionar um elemento numa posição qualquer da lista
e uma para remover um elemento d'uma posição qualquer da lista.

### A função `index_creare`

* Escopo:
   ```c
   index_t* index_creare(void)
   ```
* Funcionalidade:
   * Aloca memória para uma lista e a inicializa vazia.
* Retorno:
   * A função `index_creare` retorna o ponteiro para a lista.

### A rotina `index_adicere`

* Escopo:
   ```c
   void index_adicere(index_t *p, void* e, size_t t, size_t i)
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
   * `e`: ponteiro para o dado que se quer armazenar na pilha.
   * `t`: tamanho do dado, caso se queira fazer uma cópia dele.
   * `i`: posição na fila onde se quer colocar o novo endereço.
* Funcionalidade:
   * Se `t == 0` então `fila_adicere`
      adiciona à fila um ponteiro para o dado.
   * Se `t > 0` então `fila_adicere`
      adiciona à fila um ponteiro para uma cópia do dado.

   * Se `t == 0` então `index_adicere` adiciona à lista
      um ponteiro para o dado.
   * Se `t > 0` então `index_adicere` adiciona à lista
      um ponteiro para uma cópia do dado.
   * Em qualquer caso o índice do novo elemento será `i`.
      Entretanto se `i` for maior do que o tamanho da lista,
      então o elemento `e` será adicionado ao final da lista.
* Observações:
   * Utilizar `t > 0` com `t` diferente do tamanho do dado apontado por `e`
      pode gerar um *comportamento indefinido*.

### A função `index_removere`

* Escopo:
   ```c
   void* index_removere(index_t *p, void* e, size_t t, size_t i)
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
   * `e`: ponteiro para uma variável capaz de armazenar o dado que se quer obter.
   * `t`: tamanho do dado que se quer obter.
   * `i`: posição na fila de onde se quer remover o endereço.
* Funcionalidade:
   * Remove o i-ésimo elemento da lista.
   * Quando `t > 0` a variável apontada por `e` recebe uma cópia do dado
      apontado pelo i-ésimo elemento da lista.
* Retorno:
   * A função `index_removere` retorna o i-ésimo ponteiro da lista.
   * Se`p == NULL` ou se a lista está vazia ou se `i` for maior que o tamanho
      da lista então a função retorna `NULL`.
* Observações:
   * Em geral, usa-se `t > 0` para remover um elemento sempre que se utilizou
      `t > 0` para adicionar um elemento, utilizando o mesmo valor de `t` em
      ambos os casos, utilizar um valor diferente para `t` pode gerar um
      *comportamento indefinido*.

### A função `index_accedere`

* Escopo:
   ```c
   void* index_accedere(index_t *p, void* e, size_t t, size_t i)
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
   * `e`: ponteiro para uma variável capaz de armazenar o dado que se quer obter.
   * `t`: tamanho do dado que se quer obter.
   * `i`: posição na fila de onde se quer remover o endereço.
* Funcionalidade:
   * Acessa o i-ésimo elemento da lista sem removê-lo.
   * Quando `t > 0` a variável apontada por `e` recebe uma cópia do dado
      apontado pelo i-ésimo elemento da lista.
* Retorno:
   * A função `index_accedere` retorna o i-ésimo ponteiro da lista.
   * Se`p == NULL` ou se a lista está vazia ou se `i` for maior que o tamanho
      da lista então a função retorna `NULL`.

### A função `index_ambulator`

* Escopo:
   ```c
   void index_ambulator(index_t *p, void(*f)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
   * `f`: ponteiro para uma função dos elementos da lista.
* Funcionalidade:
   * Executar a função `f` utilizando cada elemento da lista como argumento,
      sempre na mesma ordem da lista.
   * A função `index_ambulator` é encerrada se a variável
      `tad_status` for alterada para `tad_finitum_est`.

### A função `index_dimensionem`

* Escopo:
   ```c
   size_t index_dimensionem(index_t *p)
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
* Funcionalidade:
   * Obter a quantidade de elementos na lista.
* Retorno:
   * Se `p != NULL` então a função `index_dimensionem` retorna a quantidade
      de elementos na lista.
   * Se `p == NULL` então a função `index_dimensionem` retorna `0`.

### A função `index_qsort`

* Escopo:
   ```c
   void index_qsort(index_t *p, int(*cmp)(const void*,const void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
   * `cmp`: ponteiro para uma função de comparação.
* Funcionalidade:
   * Ordenar a lista apontada por `p` utilizando a função `cmp` para comparar
      os elementos da lista segundo os mesmos critérios da função padrão `qsort`.

### A rotina `index_liberare`

* Escopo:
   ```c
   void index_liberare(index_t *p, void(*free_)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma lista previamente criada.
* Funcionalidade:
   * Libera a memória alocada para a lista apontada por `p`
      e chama a função `free_` usando cada elemento da fila como argumento.
* Observações:
   * Uma possível implementação é apresentada abaixo.
      ```c
      void index_liberare(index_t *p, void(*free_)(void*)){
         void* e;

         if(p == NULL) return;

         if(free_ != NULL){
            for(;;){
               e = index_removere(p, NULL, (size_t)0, (size_t)0);
               if(e != NULL) free_(e);
               else break;
            }
         }else{
            for(;;){
               e = index_removere(p, NULL, (size_t)0, (size_t)0);
               if(e == NULL) break;
            }
         }
         free(p);

         return;
      }
      ```

## Árvores

### A função `arbor_creare`

* Escopo:
   ```c
   arbor_t* arbor_creare(void)
   ```
* Funcionalidade:
   * Aloca memória para uma árvore e a inicializa sem nós.
* Retorno:
   * A função `arbor_creare` retorna um ponteiro para a árvore.

### A rotina `arbor_adicere`

* Escopo:
   ```c
   void arbor_adicere(arbor_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma árvore previamente criada
   * `e`: ponteiro para o dado que se quer armazenar na árvore.
   * `t`: tamanho do dado, caso se queira fazer uma cópia dele.
* Funcionalidade:
   * Se `t == 0` então `arbor_adicere`
      adiciona à árvore um ponteiro para o dado.
   * Se `t > 0` então `arbor_adicere`
      adiciona à árvore um ponteiro para uma cópia do dado.
   * Em qualquer caso, se a árvore ainda não possuir nós então
      o ponteiro será adicionado na raiz,
      mas se a árvore já possuir nós então o ponteiro será adicionado
      em um nó filho da raiz.
* Observações:
   * Utilizar `t > 0` com `t` diferente do tamanho do dado apontado por `e`
      pode gerar um *comportamento indefinido*.

### A rotina `arbor_inserere`

* Escopo:
   ```c
   void arbor_inserere(arbor_t *tronco, arbor_t *enxerto)
   ```
* Parâmetros:
   * `tronco`: ponteiro para uma árvore previamente criada.
   * `enxerto`: ponteiro para uma árvore previamente criada.
* Funcionalidade:
   * Realiza a enxertia do `enxerto` no `tronco`, isto é,
      a raiz da árvore apontada por `enxerto` é transformada em um filho
      do nó raiz da árvore apontada por `tronco`.

### A função `arbor_accedere`

* Escopo:
   ```c
   void* arbor_accedere(arbor_t *p, void* e, size_t t)
   ```
* Parâmetros:
   * `p`: ponteiro para uma árvore previamente criada.
   * `e`: ponteiro para uma variável capaz de armazenar o dado que se quer obter.
   * `t`: tamanho do dado que se quer obter.
* Funcionalidade:
   * Acessa o ponteiro para dado na raiz da árvore.
   * Quando `t > 0` a variável apontada por `e` recebe uma cópia do dado
      apontado pelo ponteiro na raiz da árvore.
* Retorno:
   * A função `arbor_accedere` retorna o ponteiro na raiz da árvore.
   * Se`p == NULL` ou se a árvore não possuir nós
      então a função retorna `NULL`.

### A rotina `arbor_ambulator`

* Escopo:
   ```c
   void arbor_ambulator(index_t *p, void(*f)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma árvore previamente criada.
   * `f`: ponteiro para uma função dos ponteiros nos nós da árvore.
* Funcionalidade:
   * Executar a função `f` utilizando cada ponteiro para dado
      em cada nó da árvore como argumento.
   * A função `arbor_ambulator` é encerrada se a variável
      `tad_status` for alterada para `tad_finitum_est`.

### A função `arbor_filius`

* Escopo:
   ```c
   index_t* arbor_filius(arbor_t *p)
   ```
* Parâmetros:
   * `p`: ponteiro para uma árvore previamente criada.
* Funcionalidade:
   * Obter uma lista com ponteiros para todas as sub-árvores cujo a raiz
      é um nó filho da raiz da árvore apontada por `p`.
* Retorno:
   * A função `arbor_filium` retorna a lista
      de ponteiros para as sub-árvores da árvore apontada por `p`.

### A rotina `arbor_liberare`

* Escopo:
   ```c
   void arbor_liberare(arbor_t *p, void(*free_)(void*))
   ```
* Parâmetros:
   * `p`: ponteiro para uma árvore previamente criada.
* Funcionalidade:
   * Libera a memória alocada para a árvore apontada por `p`
      e chama a função `free_` usando cada ponteiro para dado
      em cada nó da árvore como argumento.
