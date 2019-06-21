#include "util.hpp"

#include <iostream>

void eliminaAte(std::ifstream &arquivo, char c) {
   if (arquivo.is_open()) {
      char aux = EOF;
      do {
         arquivo >> aux;
      } while (aux != EOF && aux != c);
   }
}

void mostraTempoFormatado(int milisegundos) {
   int dias = milisegundos / 86400000;
   int sobra = milisegundos % 86400000;
   int horas = sobra / 3600000;
   sobra = sobra % 3600000;
   int minutos = sobra / 60000;
   sobra = sobra % 60000;
   int segundos = sobra / 1000;
   milisegundos = sobra % 1000;

   if (dias < 10)
      std::cout << "0";
   std::cout << dias << " dia(s), ";
   if (horas < 10)
      std::cout << "0";
   std::cout << horas << " hora(s), ";
   if (minutos < 10)
      std::cout << "0";
   std::cout << minutos << " minuto(s), ";
   if (segundos < 10)
      std::cout << "0";
   std::cout << segundos << " segundo(s), ";
   if (milisegundos < 10)
      std::cout << "0";
   std::cout << milisegundos << " milisegundo(s)\n\n";
}

void inicializaArray(int *v, int n, int elem) {
   for (size_t i = 0; i < n; ++i) {
      v[i] = elem;
   }
}

void copiaArray(int *arr1, int *arr2, int n) {
   for (int i = 0; i < n; ++i) {
      arr1[i] = arr2[i];
   }
}
