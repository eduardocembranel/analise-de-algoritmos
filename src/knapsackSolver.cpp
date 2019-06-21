#include "knapsackSolver.hpp"
#include "util.hpp"

KnapsackSolver::KnapsackSolver() {

}

KnapsackSolver::KnapsackSolver(int capacidade, int n, int *pesos, int *valores) {
   pesoMochila = capacidade;
   numObjetos  = n;
   this->pesos = pesos;
   this->valores = valores;
   solucao = new int[numObjetos];
   inicializaArray(solucao, numObjetos, 0);
}

int* KnapsackSolver::resolve(Algoritmo alg) {
   if (alg == Algoritmo::BACKTRACKING) {
      return resolveComBacktracking();
   }
   return resolveComBacktracking();
}

int* KnapsackSolver::resolveComBacktracking() {
   int *objetos = new int[numObjetos];
   inicializaArray(objetos, numObjetos, 0);
   
   int valorOtimo = 0, pesoAtual = 0, valorAtual = 0;
   dfs(pesoAtual, valorAtual, valorOtimo, objetos, 0);

   delete objetos;
   return solucao;
}

void KnapsackSolver::dfs(int &pesoAtual, int &valorAtual, int &valorOtimo,
int *objetos, int profundidade) {
   if (valorAtual > valorOtimo) {
      valorOtimo = valorAtual;
      copiaArray(solucao, objetos, numObjetos);
   }

   if (profundidade != numObjetos) {
      if (pesoAtual + pesos[profundidade] <= pesoMochila) {
         pesoAtual += pesos[profundidade];
         valorAtual += valores[profundidade];
         objetos[profundidade] = 1;
         dfs(pesoAtual, valorAtual, valorOtimo, objetos, profundidade + 1);
         pesoAtual -= pesos[profundidade];
         valorAtual -= valores[profundidade];
         objetos[profundidade] = 0;
      }
      dfs(pesoAtual, valorAtual, valorOtimo, objetos, profundidade + 1);
   }
}

KnapsackSolver::~KnapsackSolver() {
   delete pesos;
   delete valores;
   delete solucao;
}