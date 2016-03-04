#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
int main() {
screen s;
struct matrix *edges;
struct matrix *transform;
edges = new_matrix(4, 4);
// edges->m[0][0] = 2.9;
//edges->m[0][1] = 7.3;
//edges->m[2][3] = 1.9;
// edges->m[2][2] = 69;
 //print_matrix(edges);
 //transform = new_matrix(4, 4);
 //ident(edges);
 scalar_mult(2.2 , edges);
 print_matrix(edges);
//free_matrix( transform );
free_matrix( edges );
} 
