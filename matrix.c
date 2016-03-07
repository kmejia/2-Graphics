#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
/*-------------- struct matrix *new_matrix() --------------
Inputs: int rows
int cols
Returns:
Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;
  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
    tmp[i]=(double *)malloc(cols * sizeof(double));
  }
  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;
  return m;
}
/*-------------- void free_matrix() --------------
  Inputs: struct matrix *m
  Returns:
  1. free individual rows
  2. free array holding row pointers
  3. free actual matrix
*/
void free_matrix(struct matrix *m) {
  int i;
  for (i=0;i<m->rows;i++) {
    free(m->m[i]);
  }
  free(m->m);
  free(m);
}
/*======== void grow_matrix() ==========
  Inputs: struct matrix *m
  int newcols
  Returns:
  Reallocates the memory for m->m such that it now has
  newcols number of collumns
  ====================*/
void grow_matrix(struct matrix *m, int newcols) {
  int i;
  for (i=0;i<m->rows;i++) {
    m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}
/*-------------- void print_matrix() --------------
  Inputs: struct matrix *m
  Returns:
  print the matrix
*/
void print_matrix(struct matrix *m) {
  printf("[ ");
  //  m[0][0] = 1;
  int c , r ;
  while (r < (m->rows)){
    c = 0;
    while (c <(m->cols)){
      printf(" %f ",m->m[r][c]);
      c++;
    }
    printf("\n");
    r++;
  }
  printf("]\n");
  // printf("%d",m[0][0]);
}
/*-------------- void ident() --------------
  Inputs: struct matrix *m <-- assumes m is a square matrix
  Returns:
  turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int row,col;
  //row=0;
  //col=0;
  for (row=0;row<(m->rows);row++){
    for (col=0;col<(m->cols);col++){
      if (row==col){
  	m->m[row][col]=1.0;
      }
      else{
  	m->m[row][col]=0.0;
      }
    }
  }
}
  // while (r < (m->rows)){
  //print_matrix(m);
  // c = 0;
  //while (c <(m->cols)){
  //   if(r==c) {(m->m[r][c]) =1;
  //}
  //else{(m->m[r][c]) =0;
  //}
  // c++;
  // }
  
  //r++;
    
/*-------------- void scalar_mult() --------------
  Inputs: double x
  struct matrix *m
  Returns:
  multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i,j;
  for(i=0; i<(m->rows); i++){
    for (j=0; j<(m->cols); j++){
      m->m[i][j] = x * m->m[i][j];
    }
  }
}
/*-------------- void matrix_mult() --------------
  Inputs: struct matrix *a
  struct matrix *b
  Returns:
  a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  struct matrix *ans = new_matrix(a->rows, b->cols);
  int i,j,k;//a's row,b's col and a's col
  //double x,n;
  double sum;//sum of i,j components
  for(i=0;i<(a->rows);i++) {
    for( j=0;j<(b->lastcol);j++) {
      sum=0;//resets every time
      for(k=0;k< (a->lastcol);k++){
	sum = (a->m[i][k]) *(b->m[k][j]) +sum;
      }
      ans->m[i][j] =sum;
      if ((ans->lastcol)<  (ans->cols)) {
	ans->lastcol++;
      }
      



    }
  }
  //  after the loop, turn ans into theb
  copy_matrix(ans,b);
}

/*-------------- void copy_matrix() --------------
  Inputs: struct matrix *a
  struct matrix *b
  Returns:
  copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int r, c;
  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}
/*======== struct matrix * make_translate() ==========
  Inputs: int x
  int y
  int z
  Returns: The translation matrix created using x, y and z
  as the translation offsets.
  ====================*/
struct matrix * make_translate(double x, double y, double z) {
  //int r=0;
  struct matrix *ans = new_matrix(4, 4);
  ident(ans);//ans starts out as the ID matrix
  //notes are below
/*   1000         x     x+a */
/*   0100         y     y+b */
/* [          ]  [ ] = [    ] */
/*   0010         z     z+c */
/*   0001         1      1 */
  ans->m[0][3] = x;
  ans->m[1][3] = y;
  ans->m[2][3] = z;

  return ans;
}
/*======== struct matrix * make_scale() ==========
  Inputs: int x
  int y
  int z
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
/*  a000   x           ax */
/*  0b00   y           by */
/* [00c0] [z]        =[cz] */
/*  0001   1            1 */
  struct matrix * ans = new_matrix(4, 4);
  ident(ans);
  ans->m[0][0] = x;
  ans->m[1][1] = y;
  ans->m[2][2] = z;
  ans->m[3][3] = 1;
  return ans;
}
/*======== struct matrix * make_rotX() ==========
  Inputs: double theta
  Returns: The rotation matrix created using theta as the
  angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
/*   should be
 [1  0  0   0] */
/* 0 cos -sin 0 */
/* 0 sin  cos  0 */
/* 0   0  0   1 */
//convert to radians
  double radian=(theta*M_PI) /180.0;
  struct matrix *ans =  new_matrix(4 ,4 );
  ident(ans);
  ans->m[0][0] = 1;
  ans->m[1][1] = cos(radian);
  ans->m[2][1] = sin(radian);
  ans->m[1][2] = -sin(radian);
  ans->m[2][2] = cos(radian);
  ans->m[3][3] = 1;
  return ans;  }
/*======== struct matrix * make_rotY() ==========
  Inputs: double theta
  Returns: The rotation matrix created using theta as the
  angle of rotation and Y as the axis of rotation.
  ====================*/
struct matrix * make_rotY(double theta) {
  double radian=(theta*M_PI) /180.0;

/* should be */
/* [cos 0 -sin 0] */
/* 0    1   0  0 */
/* sin  0  cos 0 */
/* 0    0   0  1 */
  struct matrix * ans  =new_matrix(4,4);
  ident(ans);
  ans->m[0][0]=cos(radian);
  ans->m[0][2]=sin(radian)*(-1);
  ans->m[2][0]=sin(radian);
  ans->m[2][2]=cos(radian);
  return ans;


  }
/*======== struct matrix * make_rotZ() ==========
Inputs: double theta
Returns: The rotation matrix created using theta as the
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
/* should be */
/* [cos  -sin 0 0] */
/* sin    cos 0 0 */
/* 0        0  1 0 */
/* 0        0 0 1 */
  double radian=(theta*M_PI) /180.0;
  struct matrix * ans  = new_matrix(4,4);
  ident(ans);
  ans->m[0][0]=cos(radian);
  ans->m[0][1]=sin(radian)*(-1);
  ans->m[1][0]=sin(radian);
  ans->m[1][1]=cos(radian);
  return ans;
}





