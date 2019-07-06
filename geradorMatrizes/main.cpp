#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

void geraArquivo(int dimensao, std::ofstream &arquivo) {
   for (int k = 0; k < 2; ++k) {
      arquivo << "N = " << dimensao << "\n";
      for (size_t i = dimensao; i > 0; --i) {
         for (size_t j = dimensao; j > 0; --j) {
            int num = rand() % 100;
            if (num < 10) {
               arquivo << " ";
            }
            arquivo << num << " ";
         }
         arquivo << "\n";
      }
      arquivo << "\n";
   }
}

int main() {
   srand(time(0));
   std::ofstream arquivo;
   std::string nomeArquivo;
   size_t dimensao = 0;

   std::cout << "Nome para o arquivo: ";
   std::cin >> nomeArquivo;
   std::cout << "Dimensao para as matrizes: ";
   std::cin >> dimensao;
   arquivo.open(nomeArquivo);
   if (arquivo.is_open()) {
      std::cout << "Gerando arquivo...\n";
      geraArquivo(dimensao, arquivo);
      std::cout << "\nArquivo gerado com sucesso...\n";
      arquivo.close();
   } else {
      std::cerr << "\nerro inesperado...\n";
   }
   return 0;
}