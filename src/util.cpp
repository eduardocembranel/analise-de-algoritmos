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
   std::cout << milisegundos << " milisegundo(s)\n" << std::endl;
}

void copiaArray(int *arr1, int *arr2, int n) {
   for (int i = 0; i < n; ++i) {
      arr1[i] = arr2[i];
   }
}

int **aloca2dArray(int l, int c) {
   int **array = new int*[l];
   for (int i = 0; i < l; ++i) {
      array[i] = new int[c];
   }
   return array;
}

int **desaloca2dArray(int **array, int l) {
   for (int i = 0; i < l; ++i) {
      free(array[i]);
   }
   free(array);
   return NULL;
}

bool par(int x) {
   return (x % 2 == 0);
}

void setBit(char &c, int pos) {
   c |= 1 << pos;
}

void unsetBit(char &c, int pos) {
   c &= ~(1 << pos);
}

int getBit(char c, int pos) {
   return (c >> pos & 1);
}