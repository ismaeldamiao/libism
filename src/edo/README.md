# Equações Diferenciais Ordinárias

```C
#include <edo.h>
```

## Como usar

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

## Equações suportadas

### Caso geral

Seja o espaço de estados $\mathcal{V}$
um aberto do $\mathbb{R}^n$ ou do $\mathbb{C}^n$.
A dimenção finita $n$ do espaço vetorial deve ser informada à biblioteca
usando a variável `edo_dimensio` (por padrão igual a `1`).
Por padrão a biblioteca `edo` considera o corpo como sendo o dos reais
$\mathbb{R}$, entretanto é possível mudar para o corpo dos complexos
$\mathbb{C}$ da seguinte maneira.

```c
#include "edo.h"
#undef EDO_CORPUS /* 'double' por padrão */
#define EDO_CORPUS double _Complex /* Compilar com c99 ou mais recente. */
```

O sistema de estudo é dinâmico no sentido que para cada
estado inicial $x_0$ o estado evolui após um intervalo
de tempo $t$ até um estado final $\Phi(t, x_0)$
sob a hipótese de que essa evolução satisfaz a seguinte
equação diferencial ordinária

$$
\frac{d}{dt} \Phi(t, x_0) = f(t, x(t)),
\tag{1}
$$

sujeita à condição inicial $\Phi(t, x_0) = x_0$.
O estado do sistema é reprentado na biblioteca `edo`
por um ponteiro para `double` (ou `double _Complex`),
a função `EDO_ALLOCARE()` pode ser utilizada para alocar memória corretamente
para esse ponteiro.
Por exemplo, no modelo SIR o estado é descrito por três valores reais,
então para preparar o estado é possível utilizar o código abaixo.

```c
double *estado;

edo_dimensio = 3;
estado = EDO_ALLOCARE();
```

Já a função $f$ é representada na biblioteca `edo` por
uma função cujo o nome o usuário pode escolher mas que deve ser do tipo
`EDO_CORPUS (*)(size_t i, double t, EDO_CORPUS *x);`. Por exemplo,
se quer-se que o nome da função seja `f` então pode-se usar o prototipo abaixo.

```c
EDO_CORPUS f(size_t i, double t, EDO_CORPUS *x);
```

Essa função pode ser implementada da maneira usual em c ou pode ainda ser
implementada utilizando macro. Apenas o seu nome será informado à biblioteca.

Um método de integração numérica da equação diferencial ordinária
(1) é uma função
$\Phi^{\text{METODO}}_{h}:\mathcal{V}\rightarrow\mathcal{V}$
que aproxima a solução exata conforme $h$ se torna cada vez menor,
isto é,

$$
\lim_{h\to 0} \Phi^{\text{METODO}}_{h}(x_0) - \Phi(h, x_0) = 0.
$$

Por fim, antes de chamar algum método é necessário informar à biblioteca
o instante final usando a variável `edo_finalis`
(por padrão igual a `1.0`) e o tamanho do passo $h$ usando a
variável `edo_h` (por padrão igual a `0.1`).
Por exemplo, para utilizar o método de Runge-Kutta clássico de quarta
ordem usando a função `f`, passo $h = 0,01$ até o instante final
$t_f = 10$ no modelo SIR pode-se usar o código abaixo.

```c
double t, *estado;

edo_dimensio = 3;
estado = EDO_ALLOCARE();

edo_finalis = 10.0; /* Instante final */
edo_h = 0.01; /* Passo do integrador */

/* Definicão do estado inicial */
estado[1] = 0.1;
estado[2] = 0.0;
estado[0] = 1.0 - (estado[1] + estado[2]);
/* Chamada do integrador */
EDO_INTEGRATOR_RK4(t, estado, f);
```

Para usar outro método basta substituir o sufixo `RK4`
por qualquer um dos métodos
dentre os de Runge-Kutta, multipasso e previsor-corretor,
listados na sessão anterior.

### Sistemas simpléticos

Se $\mathcal{V}$ for um aberto do $\mathbb{R}^{2n}$ e algumas outras
condições particulares forem satisfeitas então podem ser utilizados os
integradores simpléticos.
Denote a função de evolução por
$\Phi(t, z_0) = (x(t), y(t))$, com $(x(0), y(0)) = \Phi(0, z_0)$.

A primeira categoria de integradores simpléticos
servem para resolver numericamente equações do tipo

$$
\frac{d}{dt}
\begin{bmatrix} x(t) \\ y(t) \end{bmatrix}
=
\begin{bmatrix} f(y(t)) \\ g(x(t)) \end{bmatrix}
$$

onde $f_i(y) = \frac{\partial}{\partial y_i}\mathcal{H_0}(y)$
e $g_i(x) = -\frac{\partial}{\partial x_i}\mathcal{H_1}(x)$.
A função
$\mathcal{H}(x, y) = \mathcal{H}_0(y) + \mathcal{H}_1(x)$
é chamada de hamiltoniano do sistema.
