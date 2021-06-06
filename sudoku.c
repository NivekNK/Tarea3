#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j,k,l;

    //por columnas
  for (i=0;i<9;i++){
    int*A = (int*) calloc(10, sizeof(int));
    for (j=0;j<9;j++){
      int num = n->sudo[j][i];
      if (num==0){  
        continue;
        }
      if (A[num]==0){
        A[num]=1;
        }
      else{
         return 0;
        }
    }
  }
//se revisa x filas
  for (i=0;i<9;i++){
    //se crea el arreglo de verificacion
    int*A= (int*) calloc(10, sizeof(int));
    for (j=0;j<9;j++){
      int num = n->sudo[i][j];
      if (num==0){
         continue;
      } 
      if(A[num]==0){ 
        A[num]=1;
        }else {
          return 0;
        } 
    }
  }

//por casillas
  for(i=0;i<9;i=i+3){
    for(j=0;j<9;j=j+3){
      int *A= (int *) calloc(10, sizeof(int));
      for(k=i;k<i+3;k++){
        for(l=j;l<j+3;l++){
          int num = n->sudo[k][l];
          if(num==0){
             continue;
             }
          if(A[num]==0){ 
            A[num]=1;
            }
          else{
             return 0;
             }
        }
      }
    }
  }
  return 1;
}
  
 /* int A[10]={0,0,0,0,0,0,0,0,0,0},i,j,k,flag=100,l=0;
  printf("aqui se duplica 1\n");
  //se verifica por filas
  for(i=0;i<9 && flag!=0 && l!=0 ;i++){
    for(j=0;j<9;j++){
      if(A[n->sudo[i][j]]==0){
        A[n->sudo[i][j]]=1;
      }else{
        flag=0;
      }
    }
    for(k=0;k<10;k++){
      A[k]=0;
    }
  }

  for(k=0;k<10;k++){
      A[k]=0;
    }

  //se verifica por columnas
  for(i=0;i<9 && flag==1 && l!=0 ;i++){
    for(j=0;j<9;j++){
      if(A[n->sudo[j][i]]==0){
        A[n->sudo[j][i]]=1;
      }else{
        flag=0;
      }
    }
   for(k=0;k<10;k++){
      A[k]=0;
      }
  }
  printf("aqui se duplica 2\n");

  return  0;*/



List* get_adj_nodes(Node* n){
    List* list=createList();
    //poner k en cero dsp
    int j,i;
    
   
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[0][j]==0){
             Node *aux = createNode();
             aux=copy(n);
             aux->sudo[0][j]=i+1;
             if(is_valid(aux)==1){
               pushBack(list,aux);
             }
             break;
        }
      }
    }
   
    
    /*while(k<9){
         for(j=0;j<9;j++){
        if(n->sudo[k][j]==0){
         //valores que se insertan
         while(insert<10){
           Node *aux = createNode();
             aux=copy(n);
             aux->sudo[k][j]=insert;
             pushBack(list,aux);
             insert++;
         }
         insert=1;
         }
       }
      k++;
    }*/

    


    return list;
}


int is_final(Node* n){
    int i,j,cont=0;
  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
         if(n->sudo[i][j]==0){
          cont++;
         }
    }
  }
  if(cont!=0){
    return 0;
  }else{
    return 1;
  }
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/