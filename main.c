#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
int main() {
/* screen s; */
/* struct matrix *edges; */
/* struct matrix *transform; */
/* edges = new_matrix(4, 4); */
/* // edges->m[0][0] = 2.9; */
/* //edges->m[0][1] = 7.3; */
/* //edges->m[2][3] = 1.9; */
/* // edges->m[2][2] = 69; */
/*  //print_matrix(edges); */
/*  //transform = new_matrix(4, 4); */
/*  //ident(edges); */
/*  scalar_mult(2.2 , edges); */
/*  print_matrix(edges); */
/* //free_matrix( transform ); */
/* free_matrix( edges ); */
//------------------------------------------------------------------

//  NOTE, weird bug or something where i cant print a matrix
  //after scalar mult and other transformations 
  //still draws and makes the pic anyway
  screen s;
  color c1;
  c1.red =255;
  c1.green =0;
  c1. blue =0;
  color c2;
  c2.red=147;
  c2.green=178;
  c2.blue =252;
  color c3;
  c3.red = 0;
  c3.green = 0;
  c3.blue = 255;
  color c4;
  c4.red=102;
  c4.green =225;
  c4.blue =255;
  
  clear_screen(s);
  struct matrix *edges;
  struct matrix *transform;
  //z-cor doesnt seem to matter...yet
  edges = new_matrix(4, 1);
  print_matrix(edges);
  
  add_edge(edges, 300, 250, 0,250+25,250+43,0);//middle
  add_edge(edges,250+25,250+43, 0, 250-25,250+43,0);
  add_edge( edges,250-25,250+43,0,200,250,0);
  add_edge( edges,200,250,0,250-25,250-43,0);
  add_edge( edges,250-25,250-43,0,250+25,250-43,0);
  add_edge( edges,250+25,250-43,0,300,250,0);
  add_point(edges, 200, 250, 0);//middle
  // print_matrix(edges);
  //print_matrix(edges);
  draw_lines(edges,s,c1);//white hexagon
  struct matrix *example = make_translate (200,200,0);//
  matrix_mult(example,edges);
  int i;
  int x =1 ;
  struct matrix *trans;
  struct matrix *trans2;
  for (x=1;x<100;x++){
  scalar_mult(0.96, edges);
  trans= make_translate(-450,-443,0);//translate ,250 243
  trans2=make_rotZ(x % 60);//rotate along z
   matrix_mult(trans,edges);

  draw_lines(edges,s,c4);
  matrix_mult(trans2,edges);
  trans= make_translate(450,443,0);//translate ,50 53
   matrix_mult(trans,edges);//
  draw_lines(edges,s,c1);
  //  add_edge(edges,250,0,0,500,250,0);
  // scalar_mult(1.2,edges);
  //matrix_mult(example,edges);//

  draw_lines(edges,s,c2);
  }
  //  print_matrix(edges);

  //print_matrix(trans);
  ///matrix_mult(trans,edges);
  //print_matrix(edges);

  //  draw_lines(edges,s,c1);
  
  
  display(s);
  save_extension(s, "kmejia.png");
  
  
  free_matrix( transform );
  free_matrix( edges );
} 
