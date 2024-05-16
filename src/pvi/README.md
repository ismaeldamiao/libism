# Problema Valoris Inicialis

*Problema Valoris Inicialis*, ou simplesmente PVI,
é uma biblioteca que
oferece diversas rotinas implementadas na forma de macros para
resolver numericamente o problema de valor inicial.

Última modificação: 08 de abril de 2024.

```C
#include "pvi.h"
```

## Integradores

Métodos de Runge-Kutta:
- [x] Euler: `EULER`
- [x] Euler melhorado: `RK2`
- [x] Runge-Kutta clássico de 4a ordem: `RK4`

Métodos de multipasso:
- [x] Adams-Bashforth de dois passos: `AB2`
- [x] Adams-Bashforth de três passos: `AB3`
- [x] Adams-Bashforth de quatro passos: `AB4`
- [x] Adams-Bashforth de cinco passos: `AB5`
- [ ] Adams-Bashforth de oito passos: `AB8`
- [x] Adams-Bashforth de dez passos: `AB10`

Métodos previsor-corretor:
- [x] Adams-Bashforth-Moulton de um passo: `ABM1`
- [x] Adams-Bashforth-Moulton de dois passos: `ABM2`
- [x] Adams-Bashforth-Moulton de três passos: `ABM3`
- [x] Adams-Bashforth-Moulton de quatro passos: `ABM4`
- [x] Adams-Bashforth-Moulton de cinco passos: `ABM5`
- [ ] Adams-Bashforth-Moulton de oito passos: `ABM8`
- [x] Adams-Bashforth-Moulton de dez passos: `ABM10`

Métodos simpléticos:
- [x] Euler semi-implícito: `EULER_S`
- [x] Störmer-Verlet: `VERLET`
- [x] Ruth de terceira ordem: `RUTH3`
- [x] Ruth de quarta ordem: `RUTH4`

## Instruções de uso

Statistica é uma implementação do cabeçalho especificado
em [05-pvi.md](../../spec/textual/05-pvi.md),
a especificação deve ser consultada para maiores detalhes.

## Teoria

O espaço de estados é um subconjunto aberto $\mathcal{V}\subseteq\mathbb{F}^d$,
onde $\mathbb{F}\in\{\mathbb{R}, \mathbb{C}\}$.
O inteiro $d$ é chamado de dimensão do espaço de estados.

O estado do sistema é dinâmico, isto é, ele evolui.
Assim se o sistema está inicialmente em um estado
$x_0\in\mathcal{V}$ então posteriormente
será encontrado em um estado $\Phi(t, x_0)\in\mathcal{V}$.
O parâmetro real $t$ é chamado de tempo e a função de evolução
satisfaz às relações $\Phi(0, x_0) = x_0$ e
$\Phi(t + s, x_0) = \Phi(t, \Phi(s, x_0))$.
Um campo vetorial $f:\mathbb{R}\times\mathcal{V}\rightarrow\mathbb{F}^d$
é uma lei de evolução se a seguinte equação diferencial ordinária é válida.

$$
\frac{d}{dt} \Phi(t, x_0) = f(t, \Phi(t, x_0)).
\tag{1}
$$

Um método de integração numérica de
(1) é uma função fornece uma solução aproximada $\Phi^{\text{METODO}}(h, x_0)$
para o PVI que é mais precisa conforme menor for $h$,i isto é,

$$
\lim_{h\to 0} ||\Phi^{\text{METODO}}(h, x_0) - \Phi(h, x_0)|| = 0.
$$

O espaço de estados é dito simplético se $d$ for par, denote $d = 2f$,
se ${\mathbb{F} = \mathbb{R}}$ e se alguma forma bilinear
antisimétrica e não degenerada $\omega$ for de particular relevância.
Um integrador é simplético se também for um simplectomorfismo.

## Como usar a biblioteca PVI

* Copie o arquivo `pvi.h` para o mesmo lugar que o seu código.
* Inclua o cabeçalho.
  ```c
  #include "pvi.h"
  ```
* Por padrão um estado é representado por escalares reais,
  se for necessário utilizar os complexos faça como abaixo.
  ```c
  #undef PVI_CORPUS
  #define PVI_CORPUS double _Complex // Compilar com c99 ou mais recente.
  ```
* Implemente sua lei de evolução, uma função do tipo, como abaixo.
  ```c
  #define f(i, t, x) /* .... */
  /* ou */
  static PVI_CORPUS f(size_t i, double t, PVI_CORPUS *x){ /* .... */ }
  ```
  O usuário é livre para usar o nome que quiser no lugar de `f`.
* Já na rotina, defina o tempo limite de integração 
  e o tamanho do passo $h$, como abaixo.
  ```c
  pvi_finalis = /* valor double */;
  pvi_h = /* valor double */;
  ```
* Defina também a dimensão $d$ do espaço de estados, como abaixo.
  ```c
  pvi_dimensio = /* valor size_t */;
  ```
  Note que a no caso simplético o valor informado DEVE ser o grau de liberdade,
  apesar do nome da variável.
* Declare ponteiros e aloque memória para representar o estado,
  como abaixo.
  ```c
  double *x /* ou outro nome */;
  /* ... */
  x = PVI_ALLOCARE(); /* Aloca memória conforme o valor de edo_dimensio */
  ```
* Defina o instante inicial e o estado inicial, como abaixo.
  ```c
  double t;
  /* ... */
  t = /* Instante inicial, em geral 0.0 */;
  x[0] = /* Valor inicial da componente 0 */;
  /* ... */
  x[pvi_dimensio-1] = /* Valor inicial da componente d-1 */;
  ```
* Chame o integrador, como abaixo.
  ```c
  PVI_INTEGRATOR_EULER(t, x, f);
  ```
  O sufixo `EULER` deve ser substituído pelo do método desejado,
  verifique as opções disponíveis na sessão "Integradores".

Mudanças no caso simplético:
* É necessário declarar dois ponteiros para representar o estado, bem como
  alocar memória para ambos.
* É necessário implementar duas funções para a lei de evolução, como abaixo.
  ```c
  #define f(i, y) /* ... */
  #define g(i, x) /* ... */
  /* ou */
  static double f(size_t i, double *y){ /* ... */ }
  static double g(size_t i, double *x){ /* ... */ }
  ```
* O valor de `pvi_dimensio` deve ser $d/2$ em vez de $d$.
* A chamada do integrador deve informar os nomes extras, como abaixo.
  ```c
  PVI_INTEGRATOR_EULER_S(t, x, y, f, g);
  ```

## Exemplos

## Contato e doações

Contribua para a manutenção dessa biblioteca
relatando falhas, fazendo sugestões ou fazendo uma doação.

Autor: [I.F.F. dos Santos](https://github.com/ismaeldamiao)

- Endereço eletrônico: [ismaellxd@gmail.com](mailto:ismaellxd@gmail.com)
- Instagram: [@ismael_damiao_al](https://www.instagram.com/ismael_damiao_al/)

Doações:

- PayPal: <https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D66EM3DGU35EE>.
- PIX: Use a chave PIX `ismaellxd@gmail.com` ou o [código QR](../../QR_PIX.svg).
