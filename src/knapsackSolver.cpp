#include <cmath> //para std::ceil
#include <fstream>

#include "knapsackSolver.hpp"
#include "util.hpp"

typedef long long int ll;

KnapsackSolver::KnapsackSolver() {

}

KnapsackSolver::KnapsackSolver(int W, int n, int *pesos, int *valores) {
   this->W = W;
   this->n  = n;
   this->pesos = pesos;
   this->valores = valores;
   solucao = new int[n]();
   valorMaximo = 0;
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
   int pesoAtual = 0, valorAtual = 0; valorMaximo = 0;

   //busca em profundidade
   dfs(pesoAtual, valorAtual, objetos, n);

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
   if (k > 0) {
      //possibilidade com o objeto (se o peso total nao exceder a capacidade)
      if (pesoAtual + pesos[k - 1] <= W) {
         pesoAtual += pesos[k - 1];
         valorAtual += valores[k - 1];
         objetos[k - 1] = 1;
         dfs(pesoAtual, valorAtual, objetos, k - 1);
         //backtracking
         pesoAtual -= pesos[k - 1];
         valorAtual -= valores[k - 1];
         objetos[k - 1] = 0;
      }
      //possibilidade sem o objeto
      dfs(pesoAtual, valorAtual, objetos, k - 1);
   }
}

int *KnapsackSolver::resolveComDP() {
   //matriz base da DP (usamos apenas 2 linhas: atual e anterior)
   int **z = aloca2dArray(2, W + 1);

   //primeira linha eh inicializada com 0
   for (int j = 0; j <= W; ++j) {
      z[0][j] = 0;
   }

   //vetor keep de tamanho: ⌈(n + 1) * (W + 1) / 8⌉
   //keep armazena caracteres (byte a byte), e cada char contem
   //8 bits (0 ou 1). Cada bit pode ser importante no final 
   //do procedimento para obter o subconjunto de item da solucao
   //por isso nao podemos descarta-los
   ll keepSize = std::ceil((ll)(n + 1) * (W + 1) / 8.0);
   char *keep = new char[keepSize];

   for (int i = 1; i <= n; ++i) {
      //se estamos na linha impar, a linha anterior sera a linha 0
      //se estamos na linha par, a linha anterior sera a linha 1
      //precisamos separar a logica para cada situacao
      if (!par(i)) {
         for (int j = 0; j <= W; ++j) {
            if ((pesos[i - 1] <= j) &&
            (valores[i - 1] + z[0][j - pesos[i - 1]]  > z[0][j])) {
               z[1][j] = valores[i - 1] + z[0][j - pesos[i - 1]];
               setBit(keep[((ll)i*(W + 1) + j) / 8], ((ll)i*(W + 1) + j) % 8);
            } else {
               z[1][j] = z[0][j];
               unsetBit(keep[((ll)i*(W + 1) + j) / 8], ((ll)i*(W + 1) + j) % 8);
            }
         }
      } else {
         for (int j = 0; j <= W; ++j) {
            if ((pesos[i - 1] <= j) &&
            (valores[i - 1] + z[1][j - pesos[i - 1]]  > z[1][j])) {
               z[0][j] = valores[i - 1] + z[1][j - pesos[i - 1]]; 
               setBit(keep[((ll)i*(W + 1) + j) / 8], ((ll)i*(W + 1) + j) % 8);
            } else {
               z[0][j] = z[1][j];
               unsetBit(keep[((ll)i*(W + 1) + j) / 8], ((ll)i*(W + 1) + j) % 8);
            }
         }
      }
   }
   valorMaximo = par(n) ? z[0][W] : z[1][W];
   z = desaloca2dArray(z, 2);
   return obtemSubconjunto(keep);
}

int *KnapsackSolver::obtemSubconjunto(char *keep) {
   for (int i = n, j = W; i >= 1; --i) {
      ll posKeep = ((ll)i * (W + 1) + j) / 8;
      ll posBit  = ((ll)i * (W + 1) + j) % 8;
      if (getBit(keep[posKeep], posBit) == 1) {
         solucao[i - 1] = 1;
         j -= pesos[i - 1];
      } else {
         solucao[i - 1] = 0;
      }
   }
   delete keep;
   return solucao;
}

bool KnapsackSolver::salvaSolucao(const std::string &arquivo) {
   std::ofstream buffer(arquivo);
   if (buffer.fail()) {
      return false;
   }
   buffer << "Valor total = " << valorMaximo << "\n";
   buffer << "Vetor solucao = {";
   for (size_t i = 0; i < n; ++i) {
      buffer << solucao[i];
      if (i < n - 1) {
         buffer << ", ";
      }
   }
   buffer << "}";
   buffer.close();
   return true;
}

KnapsackSolver::~KnapsackSolver() {
   delete pesos;
   delete valores;
   delete solucao;
}