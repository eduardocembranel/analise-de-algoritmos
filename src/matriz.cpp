#include "matriz.hpp"

#include <iostream>
#include <fstream>

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
   celulas = new int[linhas * colunas]();
   this->numLinhas = linhas;
   this->numColunas = colunas;
}

int Matriz::get(int linha, int coluna) const {
   return celulas[indice(linha, coluna)];
}


int Matriz::getNumLinhas() const {
   return numLinhas;
}
int Matriz::getNumColunas() const {
   return numLinhas;
}

void Matriz::set(int linha, int coluna, int valor) {
  celulas[indice(linha, coluna)] = valor;
}

void Matriz::mostra() {
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         std::cout << celulas[indice(i, j)] << " ";
      }
      std::cout << "\n";
   }
}

size_t Matriz::indice(int i, int j) const {
   return i * numColunas + j;
}

void Matriz::multiplicaTrivial(Matriz *&m1, Matriz *&m2, Matriz *&m3) {
   for (size_t i = 0; i < m1->getNumLinhas(); ++i) {
      for (size_t j = 0; j < m2->getNumColunas(); ++j) {
         int soma = 0;
         for (int k = 0; k < m1->getNumColunas(); ++k) {
            soma += m1->get(i, k) * m2->get(k, j);
         }
         m3->set(i, j, soma);
      }
   }
}

void Matriz::subtrai(Matriz *&m1, Matriz *&m2, Matriz *&m3) {
   for (size_t i = 0; i < m1->getNumLinhas(); ++i) {
      for (size_t j = 0; j < m1->getNumColunas(); ++j) {
         int sub = m1->get(i, j) - m2->get(i, j);
         m3->set(i, j, sub);
      }
   }
}

void Matriz::soma(Matriz *&m1, Matriz *&m2, Matriz *&m3) {
   for (size_t i = 0; i < m1->getNumLinhas(); ++i) {
      for (size_t j = 0; j < m2->getNumColunas(); ++j) {
         int soma = m1->get(i, j) + m2->get(i, j);
         m3->set(i, j, soma);
      }
   }
}

void Matriz::multiplicaStrassen(Matriz *&a, Matriz *&b, Matriz *&c,
int pontoCrossover) {
   if (a->getNumLinhas() <= pontoCrossover) {
      Matriz::multiplicaTrivial(a, b, c);
   } else {
      int k = a->getNumLinhas() / 2;

      //sub-matrizes de a
      Matriz *a11 = new Matriz(k);
      Matriz *a12 = new Matriz(k);
      Matriz *a21 = new Matriz(k);
      Matriz *a22 = new Matriz(k);

      //sub-matrizes de b
      Matriz *b11 = new Matriz(k);
      Matriz *b12 = new Matriz(k);
      Matriz *b21 = new Matriz(k);
      Matriz *b22 = new Matriz(k);

      //sub-matrizes de c
      Matriz *c11 = new Matriz(k);
      Matriz *c12 = new Matriz(k);
      Matriz *c21 = new Matriz(k);
      Matriz *c22 = new Matriz(k);

      //matrizes resultantes para as 7 recursoes
      Matriz *m1 = new Matriz(k);
      Matriz *m2 = new Matriz(k);
      Matriz *m3 = new Matriz(k);
      Matriz *m4 = new Matriz(k);
      Matriz *m5 = new Matriz(k);
      Matriz *m6 = new Matriz(k);
      Matriz *m7 = new Matriz(k);

      //temporarias
      Matriz *temp1 = new Matriz(k);
      Matriz *temp2 = new Matriz(k);

      //divide as matrizes de entrada em 4 sub-matrizes cada
      for (int i = 0; i < k; ++i) {
         for (int j = 0; j < k; ++j) {
            a11->set(i, j, a->get(i, j));
            a12->set(i, j, a->get(i, j + k));
            a21->set(i, j, a->get(i + k, j));
            a22->set(i, j, a->get(i + k, j + k));

            b11->set(i, j, b->get(i, j));
            b12->set(i, j, b->get(i, j + k));
            b21->set(i, j, b->get(i + k, j));
            b22->set(i, j, b->get(i + k, j + k));
         }
      }

      //obtem m1
      Matriz::soma(a11, a22, temp1);
      Matriz::soma(b11, b22, temp2);
      multiplicaStrassen(temp1, temp2, m1);

      //obtem m2
      Matriz::soma(a21, a22, temp1);
      multiplicaStrassen(temp1, b11, m2);

      //obtem m3
      Matriz::subtrai(b12, b22, temp1);
      multiplicaStrassen(a11, temp1, m3);

      //obtem m4
      Matriz::subtrai(b21, b11, temp1);
      multiplicaStrassen(a22, temp1, m4);

      //obtem m5
      Matriz::soma(a11, a12, temp1);
      multiplicaStrassen(temp1, b22, m5);

      //obtem m6
      Matriz::subtrai(a21, a11, temp1);
      Matriz::soma(b11, b12, temp2);
      multiplicaStrassen(temp1, temp2, m6);

      //obtem m7
      Matriz::subtrai(a12, a22, temp1);
      Matriz::soma(b21, b22, temp2);
      multiplicaStrassen(temp1, temp2, m7);
      
      //combina m1, m2, m3 ... m7 e obtem as 4 partes da matriz resultado
      //c11
      Matriz::soma(m1, m4, c11);
      Matriz::subtrai(c11, m5, c11);
      Matriz::soma(c11, m7, c11);

      //c12
      Matriz::soma(m3, m5, c12);

      //c21
      Matriz::soma(m2, m4, c21);

      //c22 
      Matriz::soma(m3, m1, c22);
      Matriz::subtrai(c22, m2, c22);
      Matriz::soma(c22, m6, c22);

      //junta as 4 partes (c11, c12, c21 e c22) na matriz c
      for (int i = 0; i < k; ++i) {
         for (int j = 0; j < k; ++j) {
            c->set(i, j, c11->get(i, j));
            c->set(i, j + k, c12->get(i, j));
            c->set(i + k, j, c21->get(i, j));
            c->set(i + k, j + k, c22->get(i, j));
         }
      }

      delete a11; delete a12; delete a21; delete a22;
      delete b11; delete b12; delete b21; delete b22;
      delete c11; delete c12; delete c21; delete c22;
      delete m1; delete m2; delete m3; delete m4;
      delete m5; delete m6; delete m7;
      delete temp1; delete temp2;
   }
}

bool Matriz::salvaMatriz(const std::string &arquivo) {
   std::ofstream buffer(arquivo);
   if (buffer.fail()) {
      return false;
   }
   buffer << "N = " << numLinhas << "\n";
   for (size_t i = 0; i < numLinhas; ++i) {
      for (size_t j = 0; j < numColunas; ++j) {
         buffer << celulas[indice(i, j)] << " ";
      }
      buffer << "\n";
   }
   buffer.close();
   return true;
}

Matriz::~Matriz() {
   delete celulas;
}
