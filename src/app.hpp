#ifndef APP_HPP
#define APP_HPP

#include <string>

#include "matriz.hpp"
#include "knapsackSolver.hpp"

class App {
   public:
      App();
      void loop();

   private:
      enum opcoesMenu {INDEFINIDO = -1, MATRIZ = 1, MOCHILA, SAIR};

      void mostraMenu();

      void mostraMenuMatriz();

      void mostraMenuMochila();

      void menuMatriz();

      void menuMochila();

      void limpaTela();

      void limpaBuffer();

      void pressionaParaRetornar();

      bool driverMultiplicacao(int, const std::string &);

      bool driverMochila(int, const std::string &);

      bool carregaMatrizes(Matriz *&, Matriz *&, const std::string &);

      int tempoEstimadoMatrizes(int, int);

      bool carregaMochila(KnapsackSolver *&, const std::string &);
};

#endif // !APP_HPP
