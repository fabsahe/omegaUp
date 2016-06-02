#include <stdio.h>
#include <stdlib.h>
#define  T 1001


typedef struct NodoArbol {
    int valor;
    int fil, col;
    struct NodoArbol *izq, *der;
}A;

void insertar(A **r, int terna[], int *act, int *band ){
    if(*r ==NULL){
        *r = (A *) calloc(1, sizeof(A));
        (*r) -> valor = terna[*act];
        *band=1;
        if( *act!=0 ) return;
    	(*act)++;
    	if(terna[*act]!=-1)
    		insertar( &( (*r)->izq), terna, act, band);
   		(*act)++;
    	if(terna[*act]!=-1)   		
    		insertar( &( (*r)->der), terna, act, band);

    }
	else if( (*r)->valor==terna[0] ) {
    	(*act)++;
    	if(terna[*act]!=-1)    	
    		insertar( &( (*r)->izq), terna, act, band);
   		(*act)++;
   			if(terna[*act]!=-1)
    	insertar( &( (*r)->der), terna, act, band); 

	}
	else {
		if( (*r)->izq!=NULL )
			insertar( &((*r)->izq), terna, act, band);	
		if( (*r)->der!=NULL && *band==0 )
			insertar( &((*r)->der), terna, act, band);	
	}
}

void inRecorrido(A*n, int depth,int *c, int grafica[T][T]){

    if(n){
        inRecorrido(n->izq, depth+1, c, grafica);

        n->fil = depth;
        n->col = (*c)++;

        grafica[n->fil][n->col] = n->valor;
        inRecorrido(n->der, depth+1, c, grafica);
    }
}

void clearMatrix(int m[T][T]) {

    for (int i = 0; i < T; i++)
        for (int j = 0; j < T; j++) {
            m[i][j] = 0;
        }
}

void arbolGrafico(int grafica[T][T], int c){
    printf("Arbol\n\n");

    for(int i=0; i<T; i++){
        int b=1;
        for(int j=0; j<c; j++){
            if(grafica[i][j]!=0){
                printf("%d", grafica[i][j]);
                b=0;
            }
            else
                printf(" ");
        }
        printf("\n");

        if(b)
            break;
    }
}


int main() {
    A *r = NULL;
    int grafica[T][T] = {0}, col=0;
	int vec[3];
    int actual=0, n, i=0,j=0;
    int band=0, ancho=0, max[2]={0}; 
    scanf("%d", &n);
    for( i=0;i<n;i++ ) {
    	actual=0;
    	band=0;
    	scanf("%d %d %d", &vec[0], &vec[1], &vec[2]);
		insertar(&r, vec, &actual, &band );
	}

    clearMatrix(grafica);
	inRecorrido(r, 0, &col, grafica);
    //arbolGrafico(grafica, col);
	i=0;
	do {
		ancho=0;
		for(j=n-1;j>0;j--) {
			if( grafica[i][j]!=0 ) {
				ancho=j;
				break;
			}		
		}
		for(j=0;j<n;j++) {
			if( grafica[i][j]!=0 ) {
				ancho-=j;
				ancho++;
				break;
			}
		}		
		i++;
		if(ancho>max[1]) {
			max[0]=i;
			max[1]=ancho;
		}
	}while(ancho!=0);
	
	printf("%d %d", max[0], max[1]);	
    return  0;
}

