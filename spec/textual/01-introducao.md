# Introdução

## Visão geral

`LibIsm` é uma biblioteca para a linguagem de programação C,
as utilidades aí encontradas propõem ser uma solução para
problemas mais ou menos comuns com os quais
o autor **Ism**ael e seus colegas de trabalho que utilizam C se depararam.

## Motivação

A primeira motivação para `LibIsm` é a necessidade de soluções para
problemas de física e matemática
que podem exigir computação de auto desempenho.

A segunda motivação para `LibIsm` é a necessidade de que as soluções
que primeiro motivaram sua criação sejam fáceis de
utilizar e de compartilhar juntamente
com cada código que utilize a biblioteca.

## Filosofia

O estilo da interface de `LibIsm`
é desenhado com o objetivo de facilitar ao máximo
o seu uso para aqueles que estão apenas razoavelmente familiarizados com a
linguagem de programação C.

Uma implementação de `LibIsm` deve ser desenhada com o objetivo de
facilitar ao máximo a sua integração com outros códigos.
A fim de que tal requerimento não seja subjetivo demais se estabelece que:

* Para cada cebeçalho com componentes externos
   deve haver um arquivo fonte de mesmo nome cujo sua compilação é
   suficiente.

Esse requerimento não impede que hajam mais um código fonte para cada cabeçalho,
bastando que a interação do usuário com apenas um no momento de compilar
seja suficiente.
Por exemplo, a biblioteca `<gna.h>` possui funções externas e a implementação
de todas elas deve ser encontrada em um arquivo `gna.c`,
na maioria das distribuições Linux tal arquivo pode ser compilado simplesmente
com o comando `cc -c gna.c` para depois ser linkado apropriadamente,
entretanto muitas pessoas podem preferir incluí-lo diretamente no código
de maneira parecida a:

```c
/* ... */
#include "gna.h"

int main(void){
   /* ... */
}

#include "gna.c"
```
