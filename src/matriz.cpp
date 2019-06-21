#include "matriz.hpp"

#include <iostream>

Matriz::Matriz() {
   inicializaMatriz(0, 0);
}

Matriz::Matriz(int dimensao) {
   inicializaMatriz(dimensao, dimensao);
}

Matriz::Matriz(int linhas, int colunas) {
   inicializaMatriz(linhas, colunas);
}

void Matriz::inicializaMatriz(int linhas, int colunas) {
   celulas = new int[linhas * colunas];
   this->numLinhas = linhas;
   this->numColunas = colunas;
}

void Matriz::mostra() {
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         std::cout << celulas[indice(i, j)] << " ";
      }
      std::cout << "\n";
   }
}

size_t Matriz::indice(int i, int j) {
   return i * numColunas + j;
}

size_t Matriz::indice(int i, int j, int n) {
   return i * n + j;
}

int* Matriz::getCelulas() {
   return celulas;
}

Matriz* Matriz::multiplica(Matriz *m2, Algoritmo alg) {
   if (alg == Algoritmo::TRIVIAL) {
      return multiplicaTrivial(m2);
   }
   return multiplicaStrassen(m2);
}

Matriz* Matriz::multiplicaTrivial(Matriz *m2) {
   Matriz *resultado = new Matriz(numLinhas, m2->getNumColunas());
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         int soma = 0;
         for (int k = 0; k < numLinhas; ++k) {
            soma += celulas[indice(i, k)] * m2->get(k, j);
         }
         resultado->set(i, j, soma);
      }
   }
   return resultado;
}

Matriz* Matriz::multiplicaStrassen(Matriz *b) {
   int n = numLinhas;
   Matriz *resultado = new Matriz(n);
   strassenAux(getCelulas(), b->getCelulas(), resultado->getCelulas(), n, n);
   return resultado;
}

void Matriz::strassenAux(int *a, int *b, int *c, int m, int n) {
   if (m == 2) {
      int a11 = a[indice(0, 0, n)];
      int a12 = a[indice(0, 1, n)];
      int a21 = a[indice(1, 0, n)];
      int a22 = a[indice(1, 1, n)];
      int b11 = b[indice(0, 0, n)];
      int b12 = b[indice(0, 1, n)];
      int b21 = b[indice(1, 0, n)];
      int b22 = b[indice(1, 1, n)];
     
      int m0 = (a11 + a22) * (b11 + b22);
      int m1 = (a21 + a22) * b11;
      int m2 = a11 * (b12 - b22);
      int m3 = a22 * (b21 - b11);
      int m4 = (a11 + a12) * b22;
      int m5 = (a21 - a11) * (b11 + b12);
      int m6 = (a12 - a22) * (b21 + b22);

      c[indice(0, 0, n)] += m0 + m3 - m4 + m6;
      c[indice(0, 1, n)] += m2 + m4;
      c[indice(1, 0, n)] += m1 + m3;
      c[indice(1, 1, n)] += m0 - m1 + m2 + m5;
   } else {
      m /= 2;
      strassenAux(a , b, c, m, n);
      strassenAux(a , b + m, c + m, m, n);
      strassenAux(a + m, b + m*n, c, m, n);
      strassenAux(a + m, b + m*(n + 1), c + m, m, n);
      strassenAux(a + m*n, b, c + m*n, m, n);
      strassenAux(a + m*n, b + m, c + m*(n + 1), m, n);
      strassenAux(a + m*(n + 1), b + m*n, c + m*n, m, n);
      strassenAux(a + m*(n + 1), b + m*(n + 1), c + m*(n + 1), m, n);
   }
}

Matriz* Matriz::subtrai(Matriz *m2) {
   Matriz *resultado = new Matriz(numLinhas, m2->getNumColunas());
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         int sub = celulas[indice(i, j)] - m2->get(i, j);
         resultado->set(i, j, sub);
      }
   }
   return resultado;
}

Matriz* Matriz::soma(Matriz *m2) {
   Matriz *resultado = new Matriz(numLinhas, m2->getNumColunas());
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         int soma = celulas[indice(i, j)] + m2->get(i, j);
         resultado->set(i, j, soma);
      }
   }
   return resultado;
}

int Matriz::getNumLinhas() const {
   return numLinhas;
}
int Matriz::getNumColunas() const {
   return numLinhas;
}

int Matriz::get(int linha, int coluna)  {
   return celulas[indice(linha, coluna)];
}

void Matriz::set(int linha, int coluna, int valor) {
  celulas[indice(linha, coluna)] = valor;
}

Matriz::~Matriz() {
   delete celulas;
}
