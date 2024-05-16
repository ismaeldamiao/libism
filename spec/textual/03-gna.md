# Generator Numerorum Aleatoriorum `<gna.h>`

*Generator Numerorum Aleatoriorum*, ou simplesmente GNA,
é uma biblioteca que oferece diversas funções
para geração de números pseudo aleatórios.

## Visão geral

### Compatibilidade

Todos os nomes iniciados com `gna_` e `GNA_`,
estão reservados para o futuro
uso da biblioteca GNA,
utilizá-los pode gerar um *comportamento indefinido*.

### Macros

A única macro definida em `<gna.h>` é `GNA_H`,
que serve para indicar a presença da biblioteca.

## Geradores de números pseudo-aleatórios

### A função `gna_std`

* Escopo:
   ```c
   double gna_std(int *w)
   ```
* Parâmetros:
   * `w`: ponteiro para uma variável aleatória.
* Funcionalidade:
   * Gera pseudo-números aleatórios utilizando a biblioteca padrão do `C`,
      um valor inteiro é gerado no intervalo `[0, RAND_MAX]`
      e um valor de ponto flutuante é gerado no intervalo `[0, 1)`.
   * O gerador pode ser inicializado de duas maneiras,
      em ambos os casos usando `*w` como semente:
      1) Executando a função pela primeira vez.
      2) Fazendo `*w < 0`.
* Retorno:
   * A função `gna_std` retorna o valor de ponto flutuante gerado.
   * `*w` recebe o valor inteiro gerado.

### A função `gna_lcg`

* Escopo:
   ```c
   double gna_lcg(unsigned int *)
   ```
* Parâmetros:
   * `w`: ponteiro para uma variável aleatória.
* Funcionalidade:
   * Gera pseudo-números aleatórios utilizando um gerador linear congruente,
      um valor inteiro é gerado no intervalo `[0, UINT_MAX]`
      e um valor de ponto flutuante é gerado no intervalo `[0, 1)`.
* Retorno:
   * A função `gna_lcg` retorna o valor de ponto flutuante gerado.
   * `*w` recebe o valor inteiro gerado.

### A função `gna_mt19937`

* Escopo:
   ```c
   double gna_mt19937(unsigned long int *w)
   ```
* Parâmetros:
   * `w`: ponteiro para uma variável aleatória.
* Funcionalidade:
   * Gera pseudo-números aleatórios utilizando um gerador de Mersenne Twister,
      um valor inteiro é gerado no intervalo `[0, ULONG_MAX]`
      e um valor de ponto flutuante é gerado no intervalo `[0, 1)`.
* Retorno:
   * A função `gna_mt19937` retorna o valor de ponto flutuante gerado.
   * `*w` recebe o valor inteiro gerado.
