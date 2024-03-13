/* *****************************************************************************
   Macro library to implement various methods to solve
   ordinary differential equations.

   Last modified: March 12, 2024
   *****************************************************************************
   E-mail: ismlxd@gmail.com
   Site: https://ismdamiao.github.io/
   *****************************************************************************
   Copyright (C) 2024 I.F.F. dos Santos

   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the “Software”), to 
   deal in the Software without restriction, including without limitation the 
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
   sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
   IN THE SOFTWARE.
***************************************************************************** */
#ifndef EDO_H
#define EDO_H 1

#if !defined(__STDC__)
# error "Utilize um compilador compativel com o ISO C."
#endif /* __STDC__ */

#include <stddef.h>
#include <stdlib.h>

#define EDO_CORPUS double
#define EDO_FAC_ALIQUID()
#define EDO_ALLOCARE() (EDO_CORPUS*)malloc(edo_dimensio*sizeof(EDO_CORPUS))

static size_t edo_dimensio = (size_t)1;
static double edo_h = 0.1, edo_finalis = 1.0;

/* ------------------------------------
   Metodos de Runge-Kutta
----------------------------------- */

#define EDO_INTEGRATOR_EULER(t, X, X_punctum) \
{\
   size_t edo_index;\
   EDO_CORPUS *edo_inclinatio = NULL;\
\
   edo_inclinatio = EDO_ALLOCARE();\
\
   while(t < edo_finalis){\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (X)[edo_index] += edo_inclinatio[edo_index] * edo_h;\
      t += edo_h;\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio);\
}


#define EDO_INTEGRATOR_RK2(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_h2;\
   EDO_CORPUS \
      *edo_inclinatio[2] = { NULL, NULL },\
      *edo_Xaux = NULL;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
\
   edo_h2 = 0.5 * edo_h;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
         edo_Xaux[edo_index] = \
            (X)[edo_index] + edo_inclinatio[0][edo_index] * edo_h;\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += edo_h2 * \
            (edo_inclinatio[0][edo_index] + edo_inclinatio[1][edo_index]);\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_RK4(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_h2, edo_h6;\
   EDO_CORPUS \
      *edo_inclinatio[4] = { NULL, NULL, NULL, NULL },\
      *edo_Xaux[2] = {NULL, NULL};\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_Xaux[0] = EDO_ALLOCARE();\
   edo_Xaux[1] = EDO_ALLOCARE();\
\
   edo_h2 = 0.5 * edo_h;\
   edo_h6 = edo_h / 6.0;\
\
   while(t < edo_finalis){\
      double edo__t_aux;\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
         edo_Xaux[0][edo_index] = \
            (X)[edo_index] + edo_inclinatio[0][edo_index] * edo_h2;\
      }\
      edo__t_aux = t + edo_h2;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[1][edo_index] = \
            X_punctum(edo_index, edo__t_aux, edo_Xaux[0]);\
         edo_Xaux[1][edo_index] = \
            (X)[edo_index] + edo_inclinatio[1][edo_index] * edo_h2;\
      }\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[2][edo_index] = \
            X_punctum(edo_index, edo__t_aux, edo_Xaux[1]);\
         edo_Xaux[0][edo_index] = \
            (X)[edo_index] + edo_inclinatio[2][edo_index] * edo_h;\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, edo_Xaux[0]);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += edo_h6 * (\
            edo_inclinatio[0][edo_index] + edo_inclinatio[3][edo_index] +\
            2.0 * (edo_inclinatio[1][edo_index] + edo_inclinatio[2][edo_index])\
          );\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_Xaux[0]);\
   free(edo_Xaux[1]);\
}



/* ------------------------------------
   Metodos de multipasso
----------------------------------- */

/* https://en.wikiversity.org/wiki/Adams-Bashforth_and_Adams-Moulton_methods */
#define EDO_INTEGRATOR_AB2(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[2], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[2] = { NULL, NULL };\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
\
   edo_hh[0] = - 0.5 * edo_h;\
   edo_hh[1] = 1.5 * edo_h;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
\
   edo_finalis1 = edo_finalis;\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK2(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
}

/* https://en.wikiversity.org/wiki/Adams-Bashforth_and_Adams-Moulton_methods */
#define EDO_INTEGRATOR_AB3(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[3], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[3] = { NULL, NULL, NULL };\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
\
   edo_hh[0] = edo_h * 5.0 / 12.0;\
   edo_hh[1] = edo_h * (-4.0 / 3.0);\
   edo_hh[2] = edo_h * 23.0 / 12.0;\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
}

#define EDO_INTEGRATOR_AB4(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[4], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[4] = { NULL, NULL, NULL, NULL };\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
\
   edo_hh[0] = edo_h * (-9.0 / 24.0);\
   edo_hh[1] = edo_h * (37.0 / 24.0);\
   edo_hh[2] = edo_h * (-59.0 / 24.0);\
   edo_hh[3] = edo_h * (55.0 / 24.0);\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
}

#define EDO_INTEGRATOR_AB5(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[5], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[5] = { NULL, NULL, NULL, NULL, NULL };\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_inclinatio[4] = EDO_ALLOCARE();\
\
   edo_hh[0] = edo_h * 251.0 / 720.0;\
   edo_hh[1] = edo_h * (-1274.0 / 720.0);\
   edo_hh[2] = edo_h * 2616.0 / 720.0;\
   edo_hh[3] = edo_h * (-2774.0 / 720.0);\
   edo_hh[4] = edo_h * 1901.0 / 720.0;\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[4][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[4][edo_index] * edo_hh[4] + \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
         edo_inclinatio[3][edo_index] = edo_inclinatio[4][edo_index];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_inclinatio[4]);\
}

/* Dr. F.A.B.F. de Moura */
#define EDO_INTEGRATOR_AB10(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[10], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[10] = { \
      NULL, NULL, NULL, NULL, NULL, \
      NULL, NULL, NULL, NULL, NULL };\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_inclinatio[4] = EDO_ALLOCARE();\
   edo_inclinatio[5] = EDO_ALLOCARE();\
   edo_inclinatio[6] = EDO_ALLOCARE();\
   edo_inclinatio[7] = EDO_ALLOCARE();\
   edo_inclinatio[8] = EDO_ALLOCARE();\
   edo_inclinatio[9] = EDO_ALLOCARE();\
\
   edo_hh[0] = edo_h * (-2082753.0 / 7257600.0);\
   edo_hh[1] = edo_h * (20884811.0 / 7257600.0);\
   edo_hh[2] = edo_h * (-94307320.0 / 7257600.0);\
   edo_hh[3] = edo_h * (252618224.0 / 7257600.0);\
   edo_hh[4] = edo_h * (-444772162.0 / 7257600.0);\
   edo_hh[5] = edo_h * (538363838.0 / 7257600.0);\
   edo_hh[6] = edo_h * (-454661776.0 / 7257600.0);\
   edo_hh[7] = edo_h * (265932680.0 / 7257600.0);\
   edo_hh[8] = edo_h * (-104995189.0 / 7257600.0);\
   edo_hh[9] = edo_h * (30277247.0 / 7257600.0);\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[4][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[5][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[6][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[7][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[8][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[9][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[9][edo_index] * edo_hh[9] + \
            edo_inclinatio[8][edo_index] * edo_hh[8] + \
            edo_inclinatio[7][edo_index] * edo_hh[7] + \
            edo_inclinatio[6][edo_index] * edo_hh[6] + \
            edo_inclinatio[5][edo_index] * edo_hh[5] + \
            edo_inclinatio[4][edo_index] * edo_hh[4] + \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
         edo_inclinatio[3][edo_index] = edo_inclinatio[4][edo_index];\
         edo_inclinatio[4][edo_index] = edo_inclinatio[5][edo_index];\
         edo_inclinatio[5][edo_index] = edo_inclinatio[6][edo_index];\
         edo_inclinatio[6][edo_index] = edo_inclinatio[7][edo_index];\
         edo_inclinatio[7][edo_index] = edo_inclinatio[8][edo_index];\
         edo_inclinatio[8][edo_index] = edo_inclinatio[9][edo_index];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_inclinatio[4]);\
   free(edo_inclinatio[5]);\
   free(edo_inclinatio[6]);\
   free(edo_inclinatio[7]);\
   free(edo_inclinatio[8]);\
   free(edo_inclinatio[9]);\
}

/* ------------------------------------
   Metodos previsor-corretor
----------------------------------- */

#define EDO_INTEGRATOR_ABM1(t, X, X_punctum) \
{\
   size_t edo_index;\
   EDO_CORPUS *edo_inclinatio = NULL, *edo_Xaux = NULL;\
\
   edo_inclinatio = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_Xaux[edo_index] = \
         (X)[edo_index] +  edo_inclinatio[edo_index] * edo_h;\
      t += edo_h;\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (X)[edo_index] += edo_inclinatio[edo_index] * edo_h;\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_ABM2(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[2], edo_hhh[3], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[2] = { NULL, NULL }, *edo_Xaux;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
   /* Coeficiente de Adans-Bashforth */\
   edo_hh[0] = edo_h * (-0.5);\
   edo_hh[1] = edo_h * 1.5;\
   /* Coeficiente de Adans-Moulton */\
   edo_hhh[0] = edo_h * 0.5;\
   edo_hhh[1] = edo_h * 0.5;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
\
   edo_finalis1 = edo_finalis;\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK2(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_Xaux[edo_index] = (X)[edo_index] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[1][edo_index] * edo_hhh[1] + \
            edo_inclinatio[0][edo_index] * edo_hhh[0];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_ABM3(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[3], edo_hhh[3], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[3] = { NULL, NULL, NULL }, *edo_Xaux;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
   /* Coeficiente de Adans-Bashforth */\
   edo_hh[0] = edo_h * 5.0 / 12.0;\
   edo_hh[1] = edo_h * (-4.0 / 3.0);\
   edo_hh[2] = edo_h * 23.0 / 12.0;\
   /* Coeficiente de Adans-Moulton */\
   edo_hhh[0] = edo_h * (-1.0 / 12.0);\
   edo_hhh[1] = edo_h * (8.0 / 12.0);\
   edo_hhh[2] = edo_h * (5.0 / 12.0);\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_Xaux[edo_index] = (X)[edo_index] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
      }\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[2][edo_index] * edo_hhh[2] + \
            edo_inclinatio[1][edo_index] * edo_hhh[1] + \
            edo_inclinatio[0][edo_index] * edo_hhh[0];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_ABM4(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[4], edo_hhh[4], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[4] = { NULL, NULL, NULL, NULL }, *edo_Xaux;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
   /* Coeficiente de Adans-Bashforth */\
   edo_hh[0] = edo_h * (-9.0 / 24.0);\
   edo_hh[1] = edo_h * (37.0 / 24.0);\
   edo_hh[2] = edo_h * (-59.0 / 24.0);\
   edo_hh[3] = edo_h * (55.0 / 24.0);\
   /* Coeficiente de Adans-Moulton */\
   edo_hhh[0] = edo_h * (1.0 / 24.0);\
   edo_hhh[1] = edo_h * (-5.0 / 24.0);\
   edo_hhh[2] = edo_h * (19.0 / 24.0);\
   edo_hhh[3] = edo_h * (9.0 / 24.0);\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_Xaux[edo_index] = (X)[edo_index] + \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
      }\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[3][edo_index] * edo_hhh[3] + \
            edo_inclinatio[2][edo_index] * edo_hhh[2] + \
            edo_inclinatio[1][edo_index] * edo_hhh[1] + \
            edo_inclinatio[0][edo_index] * edo_hhh[0];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_ABM5(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[5], edo_hhh[5], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[5] = { NULL, NULL, NULL, NULL, NULL }, *edo_Xaux;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_inclinatio[4] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
   /* Coeficiente de Adans-Bashforth */\
   edo_hh[0] = edo_h * 251.0 / 720.0;\
   edo_hh[1] = edo_h * (-1274.0 / 720.0);\
   edo_hh[2] = edo_h * 2616.0 / 720.0;\
   edo_hh[3] = edo_h * (-2774.0 / 720.0);\
   edo_hh[4] = edo_h * 1901.0 / 720.0;\
   /* Coeficiente de Adans-Moulton */\
   edo_hhh[0] = edo_h * (-19.0 / 720.0);\
   edo_hhh[1] = edo_h * (106.0 / 720.0);\
   edo_hhh[2] = edo_h * (-264.0 / 720.0);\
   edo_hhh[3] = edo_h * (646.0 / 720.0);\
   edo_hhh[4] = edo_h * 251.0 / 720.0;\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[4][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_Xaux[edo_index] = (X)[edo_index] + \
            edo_inclinatio[4][edo_index] * edo_hh[4] + \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
         edo_inclinatio[3][edo_index] = edo_inclinatio[4][edo_index];\
      }\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[4][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[4][edo_index] * edo_hhh[4] + \
            edo_inclinatio[3][edo_index] * edo_hhh[3] + \
            edo_inclinatio[2][edo_index] * edo_hhh[2] + \
            edo_inclinatio[1][edo_index] * edo_hhh[1] + \
            edo_inclinatio[0][edo_index] * edo_hhh[0];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_inclinatio[4]);\
   free(edo_Xaux);\
}

#define EDO_INTEGRATOR_ABM10(t, X, X_punctum) \
{\
   size_t edo_index;\
   double edo_hh[10], edo_hhh[10], edo_finalis1;\
   EDO_CORPUS \
      *edo_inclinatio[10] = { \
      NULL, NULL, NULL, NULL, NULL, \
      NULL, NULL, NULL, NULL, NULL }, *edo_Xaux;\
\
   edo_inclinatio[0] = EDO_ALLOCARE();\
   edo_inclinatio[1] = EDO_ALLOCARE();\
   edo_inclinatio[2] = EDO_ALLOCARE();\
   edo_inclinatio[3] = EDO_ALLOCARE();\
   edo_inclinatio[4] = EDO_ALLOCARE();\
   edo_inclinatio[5] = EDO_ALLOCARE();\
   edo_inclinatio[6] = EDO_ALLOCARE();\
   edo_inclinatio[7] = EDO_ALLOCARE();\
   edo_inclinatio[8] = EDO_ALLOCARE();\
   edo_inclinatio[9] = EDO_ALLOCARE();\
   edo_Xaux = EDO_ALLOCARE();\
   /* Coeficiente de Adans-Bashforth */\
   edo_hh[0] = edo_h * (-2082753.0 / 7257600.0);\
   edo_hh[1] = edo_h * (20884811.0 / 7257600.0);\
   edo_hh[2] = edo_h * (-94307320.0 / 7257600.0);\
   edo_hh[3] = edo_h * (252618224.0 / 7257600.0);\
   edo_hh[4] = edo_h * (-444772162.0 / 7257600.0);\
   edo_hh[5] = edo_h * (538363838.0 / 7257600.0);\
   edo_hh[6] = edo_h * (-454661776.0 / 7257600.0);\
   edo_hh[7] = edo_h * (265932680.0 / 7257600.0);\
   edo_hh[8] = edo_h * (-104995189.0 / 7257600.0);\
   edo_hh[9] = edo_h * (30277247.0 / 7257600.0);\
   /* Coeficiente de Adans-Moulton */\
   edo_hhh[0] = edo_h * (57281.0 / 7257600.0);\
   edo_hhh[1] = edo_h * (-583435.0 / 7257600.0);\
   edo_hhh[2] = edo_h * (2687864.0 / 7257600.0);\
   edo_hhh[3] = edo_h * (-7394032.0 / 7257600.0);\
   edo_hhh[4] = edo_h * (13510082.0 / 7257600.0);\
   edo_hhh[5] = edo_h * (-17283646.0 / 7257600.0);\
   edo_hhh[6] = edo_h * (16002320.0 / 7257600.0);\
   edo_hhh[7] = edo_h * (-11271304.0 / 7257600.0);\
   edo_hhh[8] = edo_h * (9449717.0 / 7257600.0);\
   edo_hhh[9] = edo_h * (2082753.0 / 7257600.0);\
\
   edo_finalis1 = edo_finalis;\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[0][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[1][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[2][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[3][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[4][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[5][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[6][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[7][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
\
   for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
      edo_inclinatio[8][edo_index] = X_punctum(edo_index, t, X);\
   edo_finalis = t + edo_h;\
   EDO_INTEGRATOR_RK4(t, X, X_punctum);\
   edo_finalis = edo_finalis1;\
\
   while(t < edo_finalis){\
      /* ----- Preditor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[9][edo_index] = X_punctum(edo_index, t, X);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_Xaux[edo_index] = (X)[edo_index] + \
            edo_inclinatio[9][edo_index] * edo_hh[9] + \
            edo_inclinatio[8][edo_index] * edo_hh[8] + \
            edo_inclinatio[7][edo_index] * edo_hh[7] + \
            edo_inclinatio[6][edo_index] * edo_hh[6] + \
            edo_inclinatio[5][edo_index] * edo_hh[5] + \
            edo_inclinatio[4][edo_index] * edo_hh[4] + \
            edo_inclinatio[3][edo_index] * edo_hh[3] + \
            edo_inclinatio[2][edo_index] * edo_hh[2] + \
            edo_inclinatio[1][edo_index] * edo_hh[1] + \
            edo_inclinatio[0][edo_index] * edo_hh[0];\
      }\
      t += edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         edo_inclinatio[0][edo_index] = edo_inclinatio[1][edo_index];\
         edo_inclinatio[1][edo_index] = edo_inclinatio[2][edo_index];\
         edo_inclinatio[2][edo_index] = edo_inclinatio[3][edo_index];\
         edo_inclinatio[3][edo_index] = edo_inclinatio[4][edo_index];\
         edo_inclinatio[4][edo_index] = edo_inclinatio[5][edo_index];\
         edo_inclinatio[5][edo_index] = edo_inclinatio[6][edo_index];\
         edo_inclinatio[6][edo_index] = edo_inclinatio[7][edo_index];\
         edo_inclinatio[7][edo_index] = edo_inclinatio[8][edo_index];\
         edo_inclinatio[8][edo_index] = edo_inclinatio[9][edo_index];\
      }\
      /* ----- Corretor ----- */ \
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         edo_inclinatio[9][edo_index] = X_punctum(edo_index, t, edo_Xaux);\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index){\
         (X)[edo_index] += \
            edo_inclinatio[9][edo_index] * edo_hhh[9] + \
            edo_inclinatio[8][edo_index] * edo_hhh[8] + \
            edo_inclinatio[7][edo_index] * edo_hhh[7] + \
            edo_inclinatio[6][edo_index] * edo_hhh[6] + \
            edo_inclinatio[5][edo_index] * edo_hhh[5] + \
            edo_inclinatio[4][edo_index] * edo_hhh[4] + \
            edo_inclinatio[3][edo_index] * edo_hhh[3] + \
            edo_inclinatio[2][edo_index] * edo_hhh[2] + \
            edo_inclinatio[1][edo_index] * edo_hhh[1] + \
            edo_inclinatio[0][edo_index] * edo_hhh[0];\
      }\
      EDO_FAC_ALIQUID();\
   }\
   free(edo_inclinatio[0]);\
   free(edo_inclinatio[1]);\
   free(edo_inclinatio[2]);\
   free(edo_inclinatio[3]);\
   free(edo_inclinatio[4]);\
   free(edo_inclinatio[5]);\
   free(edo_inclinatio[6]);\
   free(edo_inclinatio[7]);\
   free(edo_inclinatio[8]);\
   free(edo_inclinatio[9]);\
   free(edo_Xaux);\
}

/* ------------------------------------
   Metodos simpleticos
----------------------------------- */

#define EDO_INTEGRATOR_EULER_S(t, X, Y, X_punctum, Y_punctum) \
{\
   size_t edo_index;\
   while(t < edo_finalis){\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (X)[edo_index] += X_punctum(edo_index, Y) * edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (Y)[edo_index] += Y_punctum(edo_index, X) * edo_h;\
      t += edo_h;\
      EDO_FAC_ALIQUID();\
   }\
}

#define EDO_INTEGRATOR_VERLET(t, X, Y, X_punctum, Y_punctum) \
{\
   size_t edo_index;\
   double edo_hh; \
   edo_hh = edo_h * 0.5;\
\
   while(t < edo_finalis){\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (Y)[edo_index] += Y_punctum(edo_index, X) * edo_hh;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (X)[edo_index] += X_punctum(edo_index, Y) * edo_h;\
      for(edo_index = (size_t)0; edo_index < edo_dimensio; ++edo_index)\
         (Y)[edo_index] += Y_punctum(edo_index, X) * edo_hh;\
      t += edo_h;\
      EDO_FAC_ALIQUID();\
   }\
}

#endif /* EDO_H */
