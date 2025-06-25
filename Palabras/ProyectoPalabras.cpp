#include <iostream>
#include <string.h>
using namespace std;

//Proyecto Palabras
//Estatus - Funcional - Terminado
//Programador: Jesus

struct Valores{
    int tipo;
    char palabra[20];
    char pista[100];
    char inicio[5];
    char fin[5];
};

struct SalidaArc{
    char palabra[25];
    int puntaje;
};

void juegoPalabras(Valores*, int, FILE *);
void cargarJuego(FILE*, Valores **, int *);
int puntajePalabra(char *, Valores *);
void mostrarValoresSalida(FILE *);


int main() {
    FILE *palabrasJuego, *salida;
    Valores *estPalabras;
    int tam = 0;
    palabrasJuego = NULL;
    cargarJuego(palabrasJuego, &estPalabras, &tam);
    juegoPalabras(estPalabras, tam, salida);
    cout << endl << endl;
    mostrarValoresSalida(salida);
    free(estPalabras); 
    return 0;
}

void cargarJuego(FILE *archivo, Valores **juegoT, int *tam) {
    Valores temp;
    *juegoT = NULL;
    archivo = fopen("info.dat", "rb");
    if (archivo == NULL) {
        cout << "Error, no se abrio el archivo" << endl;
        return;
    }

    while (fread(&temp, sizeof(Valores), 1, archivo)) {
        Valores *nuevoJuego = (Valores*)realloc(*juegoT, (*tam + 1) * sizeof(Valores));

        *juegoT = nuevoJuego;
        (*juegoT)[*tam] = temp;
        (*tam)++;
    }
    fclose(archivo);
}

int puntajePalabra(char *palabraIngresada, Valores *valoresEvaluar) {
    int puntaje = 0;

    // Si la palabra es exactamente igual
    if (strcmp(palabraIngresada, (*valoresEvaluar).palabra) == 0) {
        return 10;
    }

    int lenIngresada = strlen(palabraIngresada);
    int lenInicio = strlen((*valoresEvaluar).inicio);
    int lenFin = strlen((*valoresEvaluar).fin);

    // Validar inicio
    bool inicioValido = true;
    for (int i = 0; i < lenInicio; i++) {
        if (palabraIngresada[i] != (*valoresEvaluar).inicio[i]) {
            inicioValido = false;
            break;
        }
    }
    if (inicioValido) {
        puntaje += 3;
    }

    // Validar fin
    bool finValido = true;
    for (int i = 0; i < lenFin; i++) {
        if (palabraIngresada[lenIngresada - lenFin + i] != (*valoresEvaluar).fin[i]) {
            finValido = false;
            break;
        }
    }
    if (finValido) {
        puntaje += 2;
    }

    return puntaje;
}

void juegoPalabras(Valores *palabras, int tam, FILE * salida) {
    char tipos[][15] = {"SUSTANTIVO", "VERBO", "ADJETIVO"};
    int puntaje = 0, punTotal = 0;
    char palabraIng[25];
    SalidaArc valoresSalida;
    salida = fopen("salida.dat","wb"); //Limpia los valores del archivo
    fclose(salida);

    salida = fopen("salida.dat","ab");
    for (int i = 0; i < tam; i++) {
        cout << "Adivina un: " << tipos[palabras[i].tipo - 1] << endl;
        cout << "Pista: " << palabras[i].pista << endl;
        cout << "Ingresa una palabra: ";
        cin >> palabraIng;

        puntaje = puntajePalabra(palabraIng, &palabras[i]);
        strcpy(valoresSalida.palabra, palabraIng);
        valoresSalida.puntaje = puntaje;
        fwrite(&valoresSalida,sizeof(SalidaArc),1,salida);
        cout << "Puntaje: " << puntaje << endl << endl;
        punTotal += puntaje;
    }
    fclose(salida);

    cout << "El puntaje total es de: " << punTotal << endl;
}

void mostrarValoresSalida(FILE * salida){
    SalidaArc valoresSalida;
    salida = fopen("salida.dat","rb");
    if(salida == NULL){
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    while(fread(&valoresSalida, sizeof(SalidaArc),1,salida)){
        cout << "Palabra ingresada: " << valoresSalida.palabra << " | " << "Puntaje: " << valoresSalida.puntaje << endl;
    }
}

