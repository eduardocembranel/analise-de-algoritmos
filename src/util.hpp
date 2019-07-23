#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>

void eliminaAte(std::ifstream &, char c);

void mostraTempoFormatado(int);

void copiaArray(int*, int*, int);

int **aloca2dArray(int, int);

int **desaloca2dArray(int**, int);

bool par(int);

void setBit(char &, int);

void unsetBit(char &, int);

int getBit(char, int);

#endif // !UTIL_HPP
