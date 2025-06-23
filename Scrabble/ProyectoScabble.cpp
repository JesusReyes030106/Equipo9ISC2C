#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#define TAM 9
using namespace std;

struct NodoJugador {
    char nombre[50];
    int puntaje;
    NodoJugador* siguiente;
};

// Prototipos
void agregarJugador(NodoJugador*&, const char*);
void mostrarJugadores(NodoJugador*);
void liberarMemoria(NodoJugador*&);
void inicializarTablero(char**&, int, int);
void mostrarTablero(char**, int, int);
bool esPalabra(const char*, const char*);
bool colocarPalabra(char**, int, int, int, int, bool, const char*);
void liberarTablero(char**&, int);

int main() {
    int filas = TAM, columnas = TAM;
    char** tablero = NULL;
    inicializarTablero(tablero, filas, columnas);

    const char* rutaDiccionario = "diccionario.txt";
    char opcion;

    // Agregar palabras al diccionario
    cout << "¿Agregar palabras al diccionario antes de jugar? (s/n) ";
    cin >> opcion; cin.ignore();
    while (opcion == 's' || opcion == 'S') {
        char nueva[100];
        cout << "Nueva palabra (MAYÚSCULAS sin acentos) ";
        cin.getline(nueva, 100);
        for (int i = 0; nueva[i]; ++i)
            nueva[i] = tolower(nueva[i]); // convertir a minúscula

        FILE* archivo = fopen(rutaDiccionario, "a");
        if (archivo) {
            fprintf(archivo, "%s\n", nueva);
            fclose(archivo);
            cout << "Palabra agregada\n";
        } else {
            cout << "Error al abrir el archivo\n";
        }
        cout << "¿Agregar otra palabra? (s/n) ";
        cin >> opcion; cin.ignore();
    }

    // Registro de jugadores
    NodoJugador* jugadores = NULL;
    int numJugadores;
    cout << "¿Cuántos jugadores? (1 o 2) ";
    cin >> numJugadores; cin.ignore();
    for (int i = 0; i < numJugadores; ++i) {
        char nombre[50];
        cout << "Nombre del jugador " << (i + 1) << " ";
        cin.getline(nombre, 50);
        agregarJugador(jugadores, nombre);
    }

    // Juego principal
    NodoJugador* actual = jugadores;
    int turno = 0;
    char palabra[20];

    while (true) {
        system("cls");
        mostrarTablero(tablero, filas, columnas);
        cout << "\nTurno de " << actual->nombre << "\n";
        cout << "Ingrese palabra o escriba SALIR para terminar ";
        cin >> palabra;

        if (strcmp(palabra, "SALIR") == 0)
            break;

        for (int i = 0; palabra[i]; ++i)
            palabra[i] = tolower(palabra[i]);

        if (!esPalabra(palabra, rutaDiccionario)) {
            cout << "La palabra '" << palabra << "' no está en el diccionario\n";
            system("pause");
            continue;
        }

        int fila, col, orientacion;
        cout << "Fila inicial (0-" << TAM - 1 << ") ";
        cin >> fila;
        cout << "Columna inicial (0-" << TAM - 1 << ") ";
        cin >> col;
        cout << "Orientación (0=HORIZONTAL, 1=VERTICAL) ";
        cin >> orientacion;

        if (colocarPalabra(tablero, filas, columnas, fila, col, orientacion == 0, palabra)) {
            actual->puntaje += strlen(palabra);
            turno = (turno + 1) % numJugadores;

            NodoJugador* temp = jugadores;
            for (int i = 0; i < turno; ++i)
                temp = temp->siguiente;
            actual = temp;
        } else {
            cout << "No se pudo colocar la palabra\n";
            system("pause");
        }
    }

    // Fin del juego
    mostrarJugadores(jugadores);
    liberarMemoria(jugadores);
    liberarTablero(tablero, filas);
    return 0;
}

void agregarJugador(NodoJugador*& cabeza, const char* nombre) {
    NodoJugador* nuevo = new NodoJugador;
    strncpy(nuevo->nombre, nombre, 49);
    nuevo->nombre[49] = '\0';
    nuevo->puntaje = 0;
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void mostrarJugadores(NodoJugador* c) {
    cout << "\nPuntajes finales\n";
    while (c) {
        cout << "- " << c->nombre << " " << c->puntaje << " pts\n";
        c = c->siguiente;
    }
}

void liberarMemoria(NodoJugador*& c) {
    while (c) {
        NodoJugador* temp = c;
        c = c->siguiente;
        delete temp;
    }
}

void inicializarTablero(char**& t, int f, int c) {
    t = new char*[f];
    for (int i = 0; i < f; ++i) {
        t[i] = new char[c];
        for (int j = 0; j < c; ++j)
            t[i][j] = ' ';
    }
}

void mostrarTablero(char** t, int f, int c) {
    cout << "   ";
    for (int j = 0; j < c; j++) cout << " " << j << "  ";
    cout << "\n";

    for (int i = 0; i < f; i++) {
        cout << "   ";
        for (int j = 0; j < c; j++) cout << "+---";
        cout << "+\n " << i << " ";
        for (int j = 0; j < c; j++) cout << "| " << t[i][j] << " ";
        cout << "|\n";
    }

    cout << "   ";
    for (int j = 0; j < c; j++) cout << "+---";
    cout << "+\n";
}

bool esPalabra(const char* palabra, const char* ruta) {
    FILE* f = fopen(ruta, "r");
    if (!f) return false;

    char linea[100];
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = '\0';
        if (strcmp(linea, palabra) == 0) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

bool colocarPalabra(char** t, int filas, int columnas, int f, int c, bool horiz, const char* palabra) {
    int len = strlen(palabra);
    if ((horiz && c + len > columnas) || (!horiz && f + len > filas))
        return false;

    for (int i = 0; i < len; ++i) {
        int r = f + (horiz ? 0 : i);
        int col = c + (horiz ? i : 0);
        if (t[r][col] != ' ' && t[r][col] != toupper(palabra[i]))
            return false;
    }

    for (int i = 0; i < len; ++i) {
        int r = f + (horiz ? 0 : i);
        int col = c + (horiz ? i : 0);
        t[r][col] = toupper(palabra[i]);
    }

    return true;
}

void liberarTablero(char**& t, int f) {
    for (int i = 0; i < f; ++i)
        delete[] t[i];
    delete[] t;
    t = NULL;
}
