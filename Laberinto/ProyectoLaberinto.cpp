//librerias
#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define TAM 4 //tamaño definido de la matriz
using namespace std;

int **crearMatriz();
int laberinto(int **Mat, int *posRen, int*posCol);
void generarArchivos();
void mostrar(int **Mat);
void escribir (FILE *salida,int **Mat, int resultado, int posRen, int posCol);
void leer (int **Mat , FILE* entrada);
void liberarMatriz(int **Mat);
FILE* archivoEntrada();
FILE* archivoSalida ();


int main(){
    //declaracion de variables 
    FILE *entrada, *salida;
    int **Mat;
    int posRen, posCol;

    srand(time(NULL));// random para generación de numeros dentro de la matriz
    generarArchivos();//función para generar archivos(archivo de entrada)
    //Abre los archivos de entrada y salida respectivamente
    entrada=archivoEntrada();
    salida=archivoSalida();

    if(entrada==NULL|| salida ==NULL){// condicionale que termina el programa
        return 0;                     // si falla alguno de los archivos (entrada o salida)
    }
    
    Mat= crearMatriz(); // matriz con reserva de memoria dinámica
    leer(Mat, entrada); //llama a la función leer para llenar la matriz con  los datos de entrada que lee
    fclose (entrada); // cierra el archivo 

    cout<<"Matriz:"<<endl; 
    mostrar(Mat); //muestra/imprime la matriz
    
    int resultado=laberinto (Mat,&posRen,&posCol);//el resultado es la sumatoria requerida del laberinto y la posicion en la que termina 

    escribir (salida, Mat,resultado,posRen,posCol);//llamada a la función escribir 
    fclose(salida);//cierra el archivo
    liberarMatriz(Mat); //llama a la función que libera la matriz
    return 0;
}


//FUNCIONES 

int **crearMatriz(){
    int **Mat=(int **)calloc(TAM, sizeof(int *)); //reserva de memoria dinámica (filas)
    if (Mat == NULL){ //Condicional que verifica la reserva de memoria
        printf("Error al reservar memoria");
        exit(1); // si falla, termina el programa
    }
    for (int i=0; i<TAM;i++){ //Ciclo que recorre las filas de la matriz 
        Mat[i]=(int*) calloc (TAM, sizeof (int)); //reserva memoria para las columnas
        if (Mat[i]== NULL){ //Condicional que verifica la reserva de memoria
            printf ("Error!!\n");
            exit(1); // si falla, termina el programa
        }
    }
    return Mat; // retorma el puntero a la matriz 
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
    FILE* f=fopen ("entrada.txt", "r"); //Abre el archivo para lectura (read)
    if (f ==NULL){//Condicional que verifica si se abrió correctamente
        cout <<"Error al abrir el archivo!!"<<endl;
        return NULL; //Retorna error
    }
    return f; //Si no se cumple el condicional se retorna el puntero f al archivo abierto
}

FILE* archivoSalida(){ 
    FILE* f=fopen ("salida.txt", "w"); //Abre el archivo para escritura (wright)
    if (f ==NULL){//Condicional que verifica si se abrió correctamente
        cout <<"Error al abrir el archivo!!"<<endl;
        return NULL; //Retorna error
    }
    return f; //Si no se cumple el condicional se retorna el puntero f al archivo abierto
}

void leer(int **Mat, FILE* entrada){
    for (int i=0; i<TAM; i++){
        for (int j=0; j<TAM; j++){
            fscanf (entrada, "%d\t", &Mat[i][j]); // lee un numero del archivo y lo guarda en la matriz 
        }
    }
}

void mostrar (int **Mat){ //Función para mostrar en consola 
    cout<<"    "; //Espacio que antes de los numeros que indican las columnas para que queden alineados 
    for (int j=0;j<TAM; j++){ //Ciclo que recorre columas
        cout<<" "<<j+1<<"  "; //Imprime los números de las columas dejando un espacio entre cada numero
    }
    cout<<endl; // Salto de linea 
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl; // Linea de separacion entre los numeros de columnas y la matriz 
    for (int i=0; i<TAM; i++){ //Ciclo que recorre las filas
        cout<<" "<<i+1<<"|"; // Imprime el numero de filas y una linea que separa los numeros de la matriz 
        for (int j=0; j<TAM; j++){ 
            printf(" %2d ", Mat[i][j]);  //Imprime los valores de la columnas en la fila [i](al estar dentro del ciclo que recorre i )
        }
        cout <<"|"<<endl; //Al terminar cada fila, imprime una linea y hace salto de linea 
    }       
    cout<<"   "<<string(TAM*4, '-')<<" "<<endl; //Linea de separación final 
}

int laberinto(int **Mat,int*posRen, int*posCol){
    int sumatoria=0, chacales=0;

    for (int i = 0; i <TAM; i++) { //Ciclo que recorre la diagonal de la matriz
        if (Mat[i][i]==0){ //Condicional si la poscición encuentra el valor 0 en el recorrido 
            chacales++; //Suma 1 si se cumple el condicional 
            if(chacales==3){ //Si la variable chacales llega a 3
                //guarda las posiciones en las que termina el recorrido
                *posCol=i+1;  
                *posRen=i+1;
                return sumatoria; //Devuelve el resultado de la sumatoria 
            }//if
        }//if
               else{
                sumatoria+= Mat[i][i]; // Si el numero es diferente a cero, se agrega a la sumatoria 
            }//else
    }//for
        
        for (int i=TAM-2; i>=0; i--) { //Recorre la última columna si no llegó a los 3 ceros
           //Misma verificacion de los ceros en la diagonal para la columna 
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

void escribir(FILE *salida,int **Mat, int resultado, int posRen, int posCol){
    fprintf(salida, "Matriz\n");
    fprintf(salida, "    ");

    for(int j=0; j<TAM; j++){
        fprintf(salida, " %2d ", j+1);
    }
    fprintf(salida, "\n");

    //Formato y estética para el archivo
    fprintf(salida, "   °");
    for(int j=0; j<TAM; j++){
        fprintf(salida,"----");
    }
    fprintf(salida, "°\n");
    //Imprime filas y el numero de la fila correspondiente
    for (int i=0;i<TAM;i++){
        fprintf(salida, "%2d |", i+1);//Numero 
        for (int j=0; j<TAM; j++){
            fprintf(salida, " %2d ", Mat[i][j]);//Valor
        }
        fprintf(salida, "|\n");  
    }
    //Formato y estética para el archivo
        fprintf(salida, "   °");
    for (int j=0; j<TAM; j++){
        fprintf(salida, "----");
    }
    fprintf(salida,"°\n");
    //Imprime el resultado de la sumatoria y la posición
    fprintf(salida, "Laberinto: %d\t", resultado);
    fprintf(salida, "Posicion: renglon %d\tcolumna %d\n", posRen, posCol);
    //Imprime los resultados en la consola 
    cout<< "Laberinto: "<<resultado<<endl;
    cout<< "Renglon: "<<posRen<<endl;
    cout<<"Columna: "<<posCol<<endl;

}

void liberarMatriz(int **Mat){
    //Libera memoria de cada fila
    for (int i=0; i<TAM; i++){
        free (Mat[i]); //Liberia memoria que se asigno en [i]
    }
    //Libera la memoria del arreglo de punteros 
    free (Mat);
}
