#ifndef QUARTO_H
#define QUARTO_H

#include <string>

const int N = 4;
const int NP = N*N;

enum Height {SHORT, TALL};
extern const char HCODE[];
enum Color {BEIGE, SEPIA};
extern const char CCODE[];
enum Shape {CIRCLE, SQUARE};
extern const char SCODE[];
enum Top {HOLLOW, SOLID};
extern const char TCODE[];
extern const char *ALLCODE[];

enum Vaxis {A, B, C, D}; 
enum Haxis {H1, H2, H3, H4};

#endif
