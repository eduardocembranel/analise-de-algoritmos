#ifndef KNAPSACKSOLVER_HPP
#define KNAPSACKSOLVER_HPP

class KnapsackSolver {
   public:
      enum class Algoritmo {BACKTRACKING, DP};

      KnapsackSolver();

      KnapsackSolver(int, int, int*, int*);

      ~KnapsackSolver();

      int *resolve(Algoritmo = Algoritmo::DP);

      int getN() const;

      //debug
      void mostra();

   private:
      int W;
      int n;
      int *pesos;
      int *valores;

      int *solucao;
      int valorMaximo;

      void dfs(int&, int&, int*, int);

      int *resolveComBacktracking();

      int *resolveComDP();

      int *obtemSolucao(int *);

      void obtemSolucaoAux(int *, int *, int, int);
      
};

#endif // !KNAPSACKSOLER_HPP
