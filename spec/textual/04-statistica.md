# Statistica `<statistica.h>`

*Statistica*
é uma biblioteca que oferece diversas funções
para a análise de dados.

## Visão geral

### Compatibilidade

Todos os nomes iniciados com `statistica_` e `STATISTICA_`,
estão reservados para o futuro
uso da biblioteca Statistica,
utilizá-los pode gerar um *comportamento indefinido*.

### Macros

A única macro definida em `<statistica.h>` é `STATISTICA_H`,
que serve para indicar a presença da biblioteca.

## Medidas de Tendência Central

### A função `statistica_media`

* Escopo:
   ```c
   double statistica_media(const double* v, size_t t)
   ```
* Parâmetros:
   * `v`: ponteiro para o início de uma array de tamanho `t`.
   * `t`: quantidade de amostras (tamanho da array).
* Funcionalidade:
   * Calcula a média dos valores na array.
* Retorno:
   * A função `statistica_media` retorna a média.

### A função `statistica_mediana`

* Escopo:
   ```c
   double statistica_mediana(const double *v, size_t t)
   ```
* Parâmetros:
   * `v`: ponteiro para o início de uma array de tamanho `t`.
   * `t`: quantidade de amostras (tamanho da array).
* Funcionalidade:
   * Calcula a mediana dos valores na array.
* Retorno:
   * A função `statistica_mediana` retorna a mediana.

### A função `statistica_moda`

* Escopo:
   ```c
   void* statistica_moda(const void **v, size_t t, int(*cmp)(void*,void*))
   ```
* Parâmetros:
   * `v`: ponteiro para o início de uma array de tamanho `t`.
   * `t`: quantidade de amostras (tamanho da array).
   * `cmp`: compara dois elementos de tipo `void*`,
      quando essa função retorna `0` diz-se que eles são iguais.
* Funcionalidade:
   * Verifica qual o elemento de maior frequência entre as amostras.
* Retorno:
   * A função `statistica_moda` retorna um ponteiro
      para o elemento de maior frequência.

## Medidas de dispersão

### A função `statistica_variance`

* Escopo:
   ```c
   double statistica_variance(const double *v, size_t t)
   ```
* Parâmetros:
   * `v`: ponteiro para o início de uma array de tamanho `t`.
   * `t`: quantidade de amostras (tamanho da array).
* Funcionalidade:
   * Calcula a variância dos valores na array.
* Retorno:
   * A função `statistica_variance` retorna a variância.

## Análize de distribuição

### A função `statistica_frequencia`

* Escopo:
   ```c
   statistica_frequencia(const void **v, size_t t, int(*cmp)(void*,void*))
   ```
* Parâmetros:
   * 
* Funcionalidade:
   * 
* Retorno:
   * 

### A função `statistica_fdp`

* Escopo:
   ```c
   double** statistica_fdp(double *v, size_t t, double bin)
   ```
* Parâmetros:
   * 
* Funcionalidade:
   * 
* Retorno:
   * 

## Análize de regressão

### A função `statistica_regressaolinear`

* Escopo:
   ```c
   /* ... */
   ```
* Parâmetros:
   * 
* Funcionalidade:
   * 
* Retorno:
   * 

### A função `statistica_regressaologistica`

* Escopo:
   ```c
   /* ... */
   ```
* Parâmetros:
   * 
* Funcionalidade:
   * 
* Retorno:
   * 