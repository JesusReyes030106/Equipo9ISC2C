#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAM 8
using namespace std;

void generarArchivos();
void mostrar(int Mat [TAM][TAM]);
void escribir (FILE *salida,int Mat[TAM][TAM], int resultado, int posRen, int posCol);
int laberinto(int Mat[TAM][TAM], int *posRen, int*posCol);
FILE* archivoEntrada();
FILE* archivoSalida ();
void leer (int Mat [TAM][TAM], FILE* entrada);

int main(){
    FILE *entrada, *salida;
    srand(time(NULL));
    generarArchivos();
    entrada=archivoEntrada();
    salida=archivoSalida();

	int Mat[TAM][TAM];
    int posRen, posCol;
    leer(Mat, entrada);
    fclose (entrada);

    cout<<"Matriz:"<<endl;
    mostrar(Mat);
    
    int resultado=laberinto (Mat,&posRen,&posCol);
    escribir (salida, Mat,resultado,posRen,posCol);
    fclose(salida);
    return 0;
}

void generarArchivos(){
    FILE*f= fopen("entrada.txt", "w");
    if(f==NULL){
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }
    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM; j++){
            int num=rand()%100;
            fprintf(f, "%d\t",num);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

FILE* archivoEntrada (){
    FILE* f=fopen ("entrada.txt", "r");
    if (f ==NULL){
        cout <<"Error al abrir el archivo!!"<<endl;
        return NULL;
    }
    return f;
}


FILE* archivoSalida(){
    FILE* f=fopen ("salida.txt", "w");
    if (f ==NULL){
        cout <<"Error al abrir el archivo!!"<<endl;
        return NULL;
    }
    return f;
}

void leer(int Mat[TAM][TAM], FILE* entrada){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            fscanf (entrada, "%d\t", &Mat[i][j]);

            if(Mat[i][j]<0 ){
                Mat[i][j]=0;
            }
            if(Mat[i][j]>99){
                Mat[i][j]=99;
            }
        }
    }
}

void mostrar (int Mat[TAM][TAM]){
    cout<<"    ";
    for (int j=0;j<TAM; j++){
        cout<<" "<<j+1<<"  ";
    }
    cout<<endl;
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl;
    for (int i=0; i<TAM; i++){
        cout<<" "<<i+1<<"|";
        for (int j=0; j<TAM; j++){ 
            printf(" %2d ", Mat[i][j]);
        }
        cout <<"|"<<endl;
    }       
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl;
}

int laberinto(int Mat [TAM][TAM],int*posRen, int*posCol){
    int sumatoria=0, chacales=0;

    for (int i = 0; i <TAM; i++) {
        if (Mat[i][i]==0){
            chacales++;
            if(chacales==3){
                *posCol=i+1;
                *posRen=i+1;
                return sumatoria;
            }//if
        }//if
               else{
                sumatoria+= Mat[i][i];
            }//else
    }//for

        
        for (int i=TAM-2; i>=0; i--) {
            if (Mat[i][TAM-1]==0) {
                chacales ++;
                if (chacales==3){
                *posCol=TAM;
                *posRen=i+1;
                return sumatoria;
            }//if
        } //if 
        else{
            sumatoria +=Mat[i][TAM-1];
        }//ekse
    }//for
       *posCol=TAM;
    *posRen=1;
    return sumatoria;
}

void escribir(FILE *salida,int Mat[TAM][TAM], int resultado, int posRen, int posCol){
    fprintf(salida, "Matriz\n");
    fprintf(salida, "    ");
    for(int j=0; j<TAM; j++){
        fprintf(salida, " %2d ", j+1);
    }
    fprintf(salida, "\n");
    fprintf(salida, "   °");
    for(int j=0; j<TAM; j++){
        fprintf(salida,"----");
    }
        fprintf(salida, "°\n");
    for (int i=0;i<TAM;i++){
        fprintf(salida, "%2d |", i+1);
        for (int j=0; j<TAM; j++){
            fprintf(salida, " %2d ", Mat[i][j]);
        }
      fprintf(salida, "|\n");  
    }
        fprintf(salida, "   °");
    for (int j=0; j<TAM; j++){
        fprintf(salida, "----");
    }
fprintf(salida,"°\n");

    fprintf(salida, "Laberinto: %d\t", resultado);
    fprintf(salida, "Posicion: renglon %d\tcolumna %d\n", posRen, posCol);
    cout<< "Laberinto: "<<resultado<<endl;
    cout<< "Renglon: "<<posRen<<endl;
    cout<<"Columna: "<<posCol<<endl;
}

