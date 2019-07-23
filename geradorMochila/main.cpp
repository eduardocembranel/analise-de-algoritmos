#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

void geraArquivo(int n, int W, std::ofstream &arquivo) {
   arquivo << "W = " << W << "\n";
   arquivo << "n = " << n << "\n";
   arquivo << "w = {";
   for (int i = 0; i < n; ++i) {
      int wi = (rand() % (4 * W / n)) + 1;
      arquivo << wi;
      if (i != n - 1) {
         arquivo << ", ";
      } else {
         arquivo << "}\n";
      }
   }
   arquivo << "c = {";
   for (int i = 0; i < n; ++i) {
      int ci = rand() % n;
      arquivo << ci;
      if (i != n - 1) {
         arquivo << ", ";
      } else {
         arquivo << "}\n";
      }
   }
}

int main() {
   srand(time(0));
   std::ofstream arquivo;
   std::string nomeArquivo;
   int n = 0;
   int W = 0;

   std::cout << "Nome para o arquivo: ";
   std::cin >> nomeArquivo;
   std::cout << "W: ";
   std::cin >> W;
   std::cout << "n: ";
   std::cin >> n;
   arquivo.open(nomeArquivo);
   if (arquivo.is_open()) {
      std::cout << "Gerando arquivo...\n";
      geraArquivo(n, W, arquivo);
      std::cout << "\nArquivo gerado com sucesso...\n";
      arquivo.close();
   } else {
      std::cerr << "\nerro inesperado...\n";
   }
   return 0;
}