#include <iostream>
#include <string.h>
#include <stdio.h>
#define TAM 2100 // Máximos caracteres a utilizar en los mensajes
using namespace std;
/*diccionario:
'\0' -> es pasa saber donde termina y no leea basura :)
*/

// estructura para guardar los datos de cada caso en una lista enlazada
struct NodoCaso {
    char titularOriginal[TAM];    
    char mensajeOriginal[TAM];     
    char titularLimpio[TAM];       
    char mensajeLimpio[TAM];       
    NodoCaso* siguiente;
};

// Prototipos
void limpiarTexto(char*, char*);  
bool esSubsecuencia(char*, char*);  
NodoCaso* leerCasosDesdeArchivo(FILE*, int&);
void procesarCasos(NodoCaso*, FILE*);
void liberarLista(NodoCaso*);

int main() {
    int cantidadCasos;
    FILE* archivoEntrada = fopen("caso.txt", "r"); // abre el archivo de entrada con los casos(SOLO LECTURA)
    if (archivoEntrada == NULL) {
        cout << "No se pudo abrir el archivo 'caso.txt'." << endl;
        return 1;
    }

    NodoCaso* lista = leerCasosDesdeArchivo(archivoEntrada, cantidadCasos); // lee los casos y construye la lista
    fclose(archivoEntrada); // cierra el archivo de entrada

    FILE* archivoSalida = fopen("resultados.txt", "w"); // abre el archivo de salida para guardar resultados
    if (archivoSalida == NULL) {
        cout << "No se pudo abrir el archivo 'resultados.txt'." << endl;
        return 1;
    }

    procesarCasos(lista, archivoSalida); // procesamiento de cada caso
    fclose(archivoSalida); // cierra el archivo de salida

    liberarLista(lista); // Liberar memoria dinámica (buena practica )
    return 0;
}

// función para leer los casos desde el archivo y construir la lista enlazada
NodoCaso* leerCasosDesdeArchivo(FILE* archivoEntrada, int& cantidadCasos) {
    fscanf(archivoEntrada, "%d\n", &cantidadCasos); // lee la cantidad de casos desde el archivo
    NodoCaso* cabeza = nullptr;
    NodoCaso* actual = nullptr;

    // lectura de cada caso desde el archivo
    for (int i = 0; i < cantidadCasos; i++) {
        NodoCaso* nuevo = new NodoCaso;

        fgets(nuevo->titularOriginal, TAM, archivoEntrada);
        // quitar salto de línea para evitar problemas cuando se lea el titular
        for (int j = 0; nuevo->titularOriginal[j] != '\0'; j++) {
            if (nuevo->titularOriginal[j] == '\n' || nuevo->titularOriginal[j] == '\r') {
                nuevo->titularOriginal[j] = '\0';
                break;
            }
        }

        fgets(nuevo->mensajeOriginal, TAM, archivoEntrada);
        for (int j = 0; nuevo->mensajeOriginal[j] != '\0'; j++) {
            if (nuevo->mensajeOriginal[j] == '\n' || nuevo->mensajeOriginal[j] == '\r') {
                nuevo->mensajeOriginal[j] = '\0';
                break;
            }
        }
        nuevo->siguiente = nullptr;
        if (cabeza == nullptr) {
            cabeza = nuevo;
            actual = nuevo;
        } else {
            actual->siguiente = nuevo;
            actual = nuevo;
        }
    }

    return cabeza;
}

// procesamiento de cada caso(Analizar cada caso)
void procesarCasos(NodoCaso* cabeza, FILE* archivoSalida) {
    int indice = 1;
    NodoCaso* actual = cabeza;

    while (actual != nullptr) {
        limpiarTexto(actual->titularLimpio, actual->titularOriginal);
        limpiarTexto(actual->mensajeLimpio, actual->mensajeOriginal);

        cout << "\nCaso " << indice << endl;
        cout << "Titular limpio: " << actual->titularLimpio << endl;
        cout << "Mensaje limpio: " << actual->mensajeLimpio << endl;

        fprintf(archivoSalida, "Caso %d:\n", indice);
        fprintf(archivoSalida, "Titular original: %s\n", actual->titularOriginal);
        fprintf(archivoSalida, "Titular limpio: %s\n", actual->titularLimpio);
        fprintf(archivoSalida, "Mensaje original: %s\n", actual->mensajeOriginal);
        fprintf(archivoSalida, "Mensaje limpio: %s\n", actual->mensajeLimpio);

        // Verificar si el mensaje está contenido como subsecuencia
        if (esSubsecuencia(actual->titularLimpio, actual->mensajeLimpio)) {
            cout << "Resultado: SI\n";
            fprintf(archivoSalida, "Resultado: SI\n\n");
        } else {
            cout << "Resultado: NO\n";
            fprintf(archivoSalida, "Resultado: NO\n\n");
        }

        actual = actual->siguiente;
        indice++;
    }
}

// función para limpiar un texto: convierte a minúsculas y elimina caracteres no alfabéticos
void limpiarTexto(char* destino, char* origen) {
    int posicion = 0;
    for (int i = 0; origen[i] != '\0'; i++) {
        char caracter = origen[i];
        if (caracter >= 'A' && caracter <= 'Z') {
            destino[posicion++] = caracter + 32;
        } else if (caracter >= 'a' && caracter <= 'z') {
            destino[posicion++] = caracter;
        }
    }
    destino[posicion] = '\0';
}

// Verifica si mensaje es subsecuencia de texto(esta pasrte es para cuando el mesaje no esta secuencialmente en el titular) :|
bool esSubsecuencia(char* texto, char* mensaje) {
    int i = 0, j = 0;
    while (texto[i] != '\0' && mensaje[j] != '\0') {
        if (texto[i] == mensaje[j]) {
            j++;
        }
        i++;
    }
    return mensaje[j] == '\0';
}

// función para liberar la memoria de la lista enlazada
void liberarLista(NodoCaso* cabeza) {
    while (cabeza != nullptr) {
        NodoCaso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
