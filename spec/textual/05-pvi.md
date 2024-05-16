# Problema Valoris Inicialis

*Problema Valoris Inicialis*, ou simplesmente PVI,
é uma biblioteca que
oferece diversas rotinas implementadas na forma de macros para
resolver numericamente o problema de valor inicial.

## Visão geral

### Compatibilidade

Todos os nomes iniciados com `pvi_` e `PVI_`,
estão reservados para o futuro
uso da biblioteca PVI,
utilizá-los pode gerar um *comportamento indefinido*.

### Macros

A biblioteca `<pvi.h>` é essencialmente uma biblioteca de macros.
Entretanto a biblioteca também define a macro
`PVI_H`,
que serve para indicar a presença da biblioteca.

## Integradores para equações genéricas

Considerando o espaço $\mathcal{V}\subseteq\mathbb{F}^d$,
onde $\mathbb{F}\in\{\mathbb{R}, \mathbb{C}\}$,
o inteiro $d$ é chamado de dimensão do espaço de estados.
O problema que se pretente resolver numericamente é

$$
\frac{d}{dt} \Phi(t, x_0) = f(t, \Phi(t, x_0)),
\tag{1}
$$

onde a função de evolução associa a cada instante $t$ e cada condição
inicial $x_0$ uma evolução $\Phi(t, x_0)\in\mathcal{V}$.
Para os fins da biblioteca TAD se convencionam as seguintes representações:

* O corpo do espaço vetorial $\mathbb{F}^d$
   pode ser o dos reais ou o dos complexos.
   Por padrão a macro `PVI_CORPUS` expande para `double`
   para representar o corpo dos reais,
   todas as funções desta sessão devem continuar funcionando se
   `PVI_CORPUS` for redefinido para `_Complex double`.
* A variável `pvi_dimensio` deve armazenar a dimensão $d$ do espaço vetorial.
* $\Phi$ é representado em por
   uma array de tipo `double[d]` (ou `_Complex double[d]`) ou então por
   um ponteiro de tipo `double*` (ou `_Complex double*`) dinamicamente alocado
   como uma array de tamanho `d`.
* $f$ é representado por uma função de tipo
   `void(double,double[d])` (ou `void(double,_Complex double[d])`),
   que pode ser implementada como função em `C` ou como macro.
* A variável `pvi_finalis` deve armazenar o valor da variável independente $t$
   que será o limite superior de integração.
* A variável `pvi_h` deverá armazenar o parâmetro que controla os integradores,
   o comumente chamado "passo".

O uso das macros para os integradores deve suceder a correta
inicialização e uso das convenções e variáveis acima citados,
do contrário pode-se gerar um *comportamento indefinido*.

* Escopo:
   ```c
   #define PVI_INTEGRATOR_<nome de integrador>(t, X, f)
   ```
* Argumentos:
   * `t`: variável utilizada para a variável independente.
   * `X`: array utilizada para representar $\Phi(t, x_0)$.
   * `f`: função utilizada para representar a função $f$ na EDO.
* Funcionalidade:
   * Expande para uma implementação do integrador.


## Integradores simpléticos
