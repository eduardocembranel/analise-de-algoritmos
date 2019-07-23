#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <string>

class Matriz {
   public:
      Matriz();

      Matriz(int);

      Matriz(int, int);

      ~Matriz();

      int get(int, int) const;

      int getNumLinhas() const;

      int getNumColunas() const;

      void set(int, int, int);

      void mostra();

      static void multiplicaTrivial(Matriz *&, Matriz *&, Matriz *&);

      static void subtrai(Matriz *&, Matriz *&, Matriz *&);
      
      static void soma(Matriz *&, Matriz *&, Matriz *&);

      static void multiplicaStrassen(Matriz *&, Matriz *&, Matriz *&, int=64);

      bool salvaMatriz(const std::string &);

   private:
      int numLinhas;
      int numColunas;
      int *celulas;
      
      void inicializaMatriz(int, int);

      size_t indice(int, int) const;
};

#endif // !MATRIZ_HPP