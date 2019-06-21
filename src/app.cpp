#include "app.hpp"
#include "matriz.hpp"
#include "util.hpp"
#include "knapsackSolver.hpp"

#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <fstream>
#include <chrono>

App::App() {

}

void App::loop() {
   int escolha = INDEFINIDO;
   while (escolha != SAIR) {
      mostraMenu();
      std::cin >> escolha;
      limpaBuffer(); 
      if (escolha == MATRIZ) {
         menuMatriz();
      } else if (escolha == MOCHILA) {
         menuMochila();
      } else if (escolha != SAIR) {
         std::cerr << "\nOpcao invalida!\n";
         pressionaParaRetornar();
      }
   }
}

void App::mostraMenu() {
   limpaTela();
   std::cout << "[ANALISE DE ALGORITMOS]\n\n"
             << "[1]Multiplicacao de matrizes\n"
             << "[2]Problema da mochila\n"
             << "[3]Sair\n"
             << ">> ";
}

void App::menuMatriz() {
   int escolha = INDEFINIDO;
   while (escolha != SAIR) {
      mostraMenuMatriz();
      std::cin >> escolha;
      limpaBuffer(); 
      if (escolha == 1 || escolha == 2) {
         std::cout << "\nInsira o caminho do arquivo de entrada: ";
         std::string caminhoArquivo;
         std::cin >> caminhoArquivo;
         limpaBuffer();
         if (!driverMultiplicacao(escolha, caminhoArquivo)) {
            std::cerr <<"\nerro ao abrir o arquivo\n\n";
         }
         pressionaParaRetornar();
      } else if (escolha != SAIR) {
         std::cerr << "\nOpcao invalida!\n";
         pressionaParaRetornar();
      }
   }
}

void App::menuMochila() {
   int escolha = INDEFINIDO;
   while (escolha != SAIR) {
      mostraMenuMochila();
      std::cin >> escolha;
      limpaBuffer(); 
      if (escolha == 1 || escolha == 2) {
         std::cout << "\nInsira o caminho do arquivo de entrada: ";
         std::string caminhoArquivo;
         std::cin >> caminhoArquivo;
         limpaBuffer();
         if (!driverMochila(escolha, caminhoArquivo)) {
            std::cerr <<"\nerro ao abrir o arquivo\n\n";
         }
         pressionaParaRetornar();
      } else if (escolha != SAIR) {
         std::cerr << "\nOpcao invalida!\n";
         pressionaParaRetornar();
      }
   }
}

void App::mostraMenuMatriz() {
   limpaTela();
   std::cout << "[MULTIPLICACAO DE MATRIZES]\n\n"
             << "[1]Algoritmo trivial\n"
             << "[2]Algoritmo de Strassen\n"
             << "[3]Sair\n"
             << ">> ";
}

void App::mostraMenuMochila() {
   limpaTela();
   std::cout << "[PROBLEMA DA MOCHILA]\n\n"
             << "[1]Algoritmo por tentativa e erro\n"
             << "[2]Algoritmo com Programacao Dinamica\n"
             << "[3]Sair\n"
             << ">> ";
}

void App::limpaTela() {
   system("clear");
}

void App::limpaBuffer() {
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void App::pressionaParaRetornar() {
   std::cout << "Pressione ENTER para retornar...";
   limpaBuffer();
}

bool App::driverMultiplicacao(int escolha, const std::string &caminhoArquivo) {
   std::ifstream arquivo(caminhoArquivo);
   if (arquivo.fail()) {
      return false;
   }

   
   eliminaAte(arquivo, '=');
   int dimensaoMat1;
   arquivo >> dimensaoMat1;
   Matriz *mat1 = new Matriz(dimensaoMat1);
   int valor;
   for (int i = 0; i < dimensaoMat1; ++i) {
      for (int j = 0; j < dimensaoMat1; ++j) {
         arquivo >> valor;
         mat1->set(i, j, valor);
      }
   }
   eliminaAte(arquivo, '=');
   int dimensaoMat2;
   arquivo >> dimensaoMat2;
   Matriz *mat2 = new Matriz(dimensaoMat2);
   for (int i = 0; i < dimensaoMat2; ++i) {
      for (int j = 0; j < dimensaoMat2; ++j) {
         arquivo >> valor;
         mat2->set(i, j, valor);
      }
   }

   auto start = std::chrono::high_resolution_clock::now();
   if (escolha == 1) {
      Matriz *mat3 = mat1->multiplica(mat2, Matriz::Algoritmo::TRIVIAL);
   } else {
      Matriz *mat3 = mat1->multiplica(mat2, Matriz::Algoritmo::STRASSEN);
   }
   auto stop = std::chrono::high_resolution_clock::now(); 
   int duracao = std::chrono::duration_cast<std::chrono::milliseconds>
      (stop - start).count();
   
   std::cout << "\nTempo de execucao: ";
   mostraTempoFormatado(duracao);

   delete mat1;
   delete mat2;
   arquivo.close();
   return true;
}

bool App::driverMochila(int escolha, const std::string &caminhoArquivo) {
   std::ifstream arquivo(caminhoArquivo);
   if (arquivo.fail()) {
      return false;
   }
   int capacidade, n;
   eliminaAte(arquivo, '=');
   arquivo >> capacidade;
   eliminaAte(arquivo, '=');
   arquivo >> n;

   int *pesos = new int[n];
   int *valores = new int[n];
   eliminaAte(arquivo, '{');
   for (int i = 0; i < n; ++i) {
      arquivo >> pesos[i];
      if (i != n - 1)
         eliminaAte(arquivo, ',');
   }
   eliminaAte(arquivo, '{');
   for (int i = 0; i < n; ++i) {
      arquivo >> valores[i];
      if (i != n - 1)
         eliminaAte(arquivo, ',');
   }

   KnapsackSolver *solver = new KnapsackSolver(capacidade, n, pesos, valores);
   int *solucao;

   auto start = std::chrono::high_resolution_clock::now();
   if (escolha == 1) {
      solucao = solver->resolve(KnapsackSolver::Algoritmo::BACKTRACKING);
   } else {
      solucao = solver->resolve(KnapsackSolver::Algoritmo::BACKTRACKING);
   }
   auto stop = std::chrono::high_resolution_clock::now(); 
   int duracao = std::chrono::duration_cast<std::chrono::milliseconds>
      (stop - start).count();
   
   std::cout << "\nTempo de execucao: ";
   mostraTempoFormatado(duracao);

   delete solver;   
   arquivo.close();
   return true;
}