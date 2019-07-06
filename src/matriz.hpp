#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <vector>

class Matriz {
   public:
      enum class Algoritmo {TRIVIAL, STRASSEN};

      Matriz();

      Matriz(int);

      Matriz(int, int);

      ~Matriz();

      int get(int, int);
      
      int *getCelulas(); 

      void set(int, int, int);

      void mostra();

      int getNumLinhas() const;

      int getNumColunas() const;  

      Matriz* multiplica(Matriz*, Algoritmo = Algoritmo::TRIVIAL);

      Matriz* multiplicaTrivial(Matriz*);

      Matriz* multiplicaStrassen(Matriz*);

      Matriz* subtrai(Matriz*);
      
      Matriz* soma(Matriz*);

   public:
      int numLinhas;
      int numColunas;
      int *celulas;
      
      void inicializaMatriz(int, int);

      size_t indice(int, int);

      size_t indice(int, int, int);

      void strassenAux(int*, int*, int*, int, int);
};

#endif // !MATRIZ_HPP