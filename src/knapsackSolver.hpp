#ifndef KNAPSACKSOLVER_HPP
#define KNAPSACKSOLVER_HPP

#include <string>

class KnapsackSolver {
   public:
      enum class Algoritmo {BACKTRACKING, DP};

      KnapsackSolver();

      KnapsackSolver(int, int, int*, int*);

      ~KnapsackSolver();

      int *resolve(Algoritmo = Algoritmo::DP);

      bool salvaSolucao(const std::string &);

   private:
      int W;
      int n;
      int *pesos;
      int *valores;

      int *solucao;
      int valorMaximo;

      int *resolveComBacktracking();

      void dfs(int&, int&, int*, int);

      int *resolveComDP();

      int *obtemSubconjunto(char *); 
};

#endif // !KNAPSACKSOLER_HPP
