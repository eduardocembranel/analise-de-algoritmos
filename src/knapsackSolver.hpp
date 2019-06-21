#ifndef KNAPSACKSOLVER_HPP
#define KNAPSACKSOLVER_HPP

class KnapsackSolver {
   public:
      enum class Algoritmo {BACKTRACKING, PROG_DINAMICA};
      KnapsackSolver();
      KnapsackSolver(int, int, int*, int*);
      ~KnapsackSolver();
      int* resolve(Algoritmo = Algoritmo::PROG_DINAMICA);

   private:
      int pesoMochila;
      int numObjetos;
      int *pesos;
      int *valores;
      int *solucao;

      void dfs(int&, int&, int&, int*, int);
      int* resolveComBacktracking();
      
};

#endif // !KNAPSACKSOLER_HPP
