#include "knapsackSolver.hpp"
#include "util.hpp"

//debug
#include <iostream>

KnapsackSolver::KnapsackSolver() {

}

KnapsackSolver::KnapsackSolver(int capacidade, int n, int *pesos, int *valores) {
   W = capacidade;
   this->n  = n;
   this->pesos = pesos;
   this->valores = valores;
   solucao = new int[n]();
   valorMaximo = 0;
}

int KnapsackSolver::getN() const {
   return n;
}

//para debug
void KnapsackSolver::mostra() {
   std::cout << "W = " << W << "\n";
   std::cout << "N = " << n << "\n";
   for (int i = 0; i < n; ++i) {
      std::cout << valores[i] << " ";
   }
   std::cout << "\n";
   for (int i = 0; i < n; ++i) {
      std::cout << pesos[i] << " ";
   }
   std::cout << "\n";
}

int *KnapsackSolver::resolve(Algoritmo alg) {
   if (alg == Algoritmo::BACKTRACKING) {
      return resolveComBacktracking();
   }
   return resolveComDP();
}

int *KnapsackSolver::resolveComBacktracking() {
   //variaveis auxiliares
   int *objetos = new int[n]();
   int pesoAtual = 0, valorAtual = 0;
   valorMaximo = 0;

   //busca em profundidade
   dfs(pesoAtual, valorAtual, objetos, n - 1);

   delete objetos;
   return solucao;
}

void KnapsackSolver::dfs(int &pesoAtual, int &valorAtual, int *objetos, int k) {
   //se a possibilidade atual tiver um valor maior q o obtido ate o momento
   //entao o novo maior valor sera o valor atual e a solucao sera o conjunto
   //de objetos atual
   if (valorAtual > valorMaximo) {
      valorMaximo = valorAtual;
      copiaArray(solucao, objetos, n);
   }

   //se ainda ha possibilidades a serem checadas
   if (k >= 0) {
      //possibilidade com o objeto (se o peso total nao exceder a capacidade)
      if (pesoAtual + pesos[k] <= W) {
         pesoAtual += pesos[k];
         valorAtual += valores[k];
         objetos[k] = 1;
         dfs(pesoAtual, valorAtual, objetos, k - 1);
         //backtracking
         pesoAtual -= pesos[k];
         valorAtual -= valores[k];
         objetos[k] = 0;
      }
      //possibilidade sem o objeto
      dfs(pesoAtual, valorAtual, objetos, k - 1);
   }
}

int *KnapsackSolver::resolveComDP() {
   //z[n+1][W+1]
   int *z = new int[(n + 1) * (W + 1)];

   //0 para todos elementos da primeira linha
   for (int i = 0; i <= W; ++i) {
      //z[0][i]
      z[i] = 0;
   }
   //0 para todos elementos da primeira coluna
   for (int i = 0; i <= n; ++i) {
      //z[i][0]
      z[i * (W + 1)] = 0;
   }

   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= W; ++j) {
         if (pesos[i - 1] <= j) {
            //z[i][j] = maximo(valores[i-1] + z[i-1][j-pesos[i-1]], z[i-1][j])
            z[i * (W + 1) + j] = std::max(valores[i - 1] + z[(i - 1) * (W + 1) 
            + j - pesos[i - 1]], z[(i - 1) * (W + 1) + j]);
         } else {
            //z[i][j] = z[i-1][W]
            z[i * (W + 1) + j] = z[(i - 1) * (W + 1) + j];
         }
      }
   }
   //valorMaximo = z[n][W]
   valorMaximo = z[n * ( W + 1) + W];
   return obtemSolucao(z);
}

int *KnapsackSolver::obtemSolucao(int *z) {
   int *x = new int[n]();
   obtemSolucaoAux(x, z, n - 1, W);
   copiaArray(solucao, x, n);
   delete z;
   delete x;
   return solucao;
}

void KnapsackSolver::obtemSolucaoAux(int *x, int *z, int k, int d) {
   if (k >= 0) {
      if (z[(k + 1) * (W + 1) + d] == z[k * (W + 1) + d]) {
         x[k] = 0;
         obtemSolucaoAux(x, z, k - 1, d);
      } else {
         x[k] = 1;
         obtemSolucaoAux(x, z, k - 1, d - pesos[k]);
      }
   }
}

KnapsackSolver::~KnapsackSolver() {
   delete pesos;
   delete valores;
   delete solucao;
}