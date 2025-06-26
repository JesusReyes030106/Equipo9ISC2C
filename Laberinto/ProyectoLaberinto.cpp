//librerias
#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAM 4 //tamaño definido de la matriz
using namespace std;

struct Laberinto{
 int **matriz;
 int resultado;
 int posRen;
 int posCol;

};

Laberinto crearMatriz();
void generarArchivos();
void mostrar(const Laberinto &lab);
int laberinto(Laberinto &lab);
void escribir (FILE *salida,const Laberinto &labl);
void leer (Laberinto &lab, FILE* entrada);
void liberarMatriz(Laberinto &lab);

FILE* archivoEntrada();
FILE* archivoSalida ();


int main(){
    FILE *entrada, *salida;
    Laberinto lab;

    srand(time(NULL));
    generarArchivos();
    //Abre los archivos de entrada y salida respectivamente
    entrada=archivoEntrada();
    salida=archivoSalida();

    if(entrada==NULL|| salida ==NULL){
        return 0;                    
    }
    
    lab= crearMatriz(); 
    leer(lab, entrada); 
    fclose (entrada); 

    cout<<"Matriz:"<<endl; 
    mostrar(lab); 
    
    lab.resultado=laberinto (lab);

    escribir (salida, lab);
    fclose(salida);
    liberarMatriz(lab);
    return 0;
}


//FUNCIONES 

Laberinto crearMatriz(){
    Laberinto lab;
    lab.matriz=(int **)calloc(TAM, sizeof(int *)); //reserva de memoria dinámica (filas)
    if (lab.matriz == NULL){ 
        printf("Error al reservar memoria");
        exit(1); 
    }
    for (int i=0; i<TAM;i++){ 
        lab.matriz[i]=(int*) calloc (TAM, sizeof (int)); //reserva memoria para las columnas
        if (lab.matriz[i]== NULL){ 
            printf ("Error!!\n");
            exit(1); 
        }
    }
    return lab; 
}

void generarArchivos(){
    FILE*f= fopen("entrada.txt", "w"); // Se crea el archivo y se abre para escrituta (wright)
    
    if(f==NULL){//Condicional que verifica si se abrió correctamente
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);// El programa termina si no se logra abrir el archivo
    }

    for(int i=0; i<TAM; i++){ //Ciclo que recorre los renglones
        for(int j=0; j<TAM; j++){ //ciclo que recorre las columnas dentro del ciclo anterior 
            int num=rand()%2; //generador de numeros aletorios dentro del rango definido 
            fprintf(f, "%d\t",num); //imprime los numeros de forma alineada con la tabulación
        }
        fprintf(f,"\n"); // salto de linea para formato
    }
    fclose(f);//cierra el archivo 
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

void leer(Laberinto &lab, FILE* entrada){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            fscanf (entrada, "%d\t", &lab.matriz[i][j]); // lee un numero del archivo y lo guarda en la matriz 
        }
    }
}

void mostrar (const Laberinto &lab){ //Función para mostrar en consola 
    cout<<"    "; 
    for (int j=0;j<TAM; j++){ 
        cout<<" "<<j+1<<"  "; //Imprime los números de las columas dejando un espacio entre cada numero
    }
    cout<<endl; // Salto de linea 
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl; 
    for (int i=0; i<TAM; i++){ 
        cout<<" "<<i+1<<"|"; // Imprime el numero de filas y una linea que separa los numeros de la matriz 
        for (int j=0; j<TAM; j++){ 
            printf(" %2d ", lab.matriz[i][j]);  //Imprime los valores de la columnas en la fila [i](al estar dentro del ciclo que recorre i )
        }
        cout <<"|"<<endl; 
    }       
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl; 
}

int laberinto(Laberinto &lab){
    int sumatoria=0, chacales=0;

    for (int i = 0; i <TAM; i++) { //Ciclo que recorre la diagonal de la matriz
        if (lab.matriz[i][i]==0){ 
            chacales++; 
            if(chacales==3){ 
                lab.posRen=i+1;  
                lab.posCol=i+1;
                return sumatoria; 
            }
        } else{
                sumatoria+= lab.matriz[i][i]; 
            }
    }
        for (int i=TAM-2; i>=0; i--) { //Recorre la última columna si no llegó a los 3 ceros
            if (lab.matriz[i][TAM-1]==0) {
                chacales ++;
                if (chacales==3){
                lab.posRen=TAM;
                lab.posCol=i+1;
                return sumatoria;
            }
        } else{
            sumatoria +=lab.matriz[i][TAM-1];
        }
    }
    lab.posCol=TAM; 
    lab.posRen=1;
    return sumatoria;
}

void escribir(FILE *salida, const Laberinto &lab){
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
        fprintf(salida, "%2d |", i+1);//Numero 
        for (int j=0; j<TAM; j++){
            fprintf(salida, " %2d ", lab.matriz[i][j]);
        }
        fprintf(salida, "|\n");  
    }
        fprintf(salida, "   °");
    for (int j=0; j<TAM; j++){
        fprintf(salida, "----");
    }
    fprintf(salida,"°\n");
    //Imprime el resultado de la sumatoria y la posición
    fprintf(salida, "Laberinto: %d\t", lab.resultado);
    fprintf(salida, "Posicion: renglon %d\tcolumna %d\n", lab.posRen, lab.posCol);
    //Imprime los resultados en la consola 
    cout<< "Laberinto: "<<lab.resultado<<endl;
    cout<< "Renglon: "<<lab.posRen<<endl;
    cout<<"Columna: "<<lab.posCol<<endl;

}

void liberarMatriz(Laberinto &lab){
    //Libera memoria de cada fila
    for (int i=0; i<TAM; i++){
        free (lab.matriz[i]); //Liberia memoria que se asigno en [i]
    }
    //Libera la memoria del arreglo de punteros 
    free (lab.matriz);
    lab.matriz=NULL;
}
