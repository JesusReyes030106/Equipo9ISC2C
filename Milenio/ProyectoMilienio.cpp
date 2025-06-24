#include <iostream>
#include <string.h>
using namespace std;
/*diccionario:
'\0' -> es pasa saber donde termina y no leea basura :)
*/

// estructura para guardar los datos de cada caso
struct Caso {
    char titular[2100];
    char mensaje[2100];
    char limpioTitular[2100];
    char limpioMensaje[2100];
};

// Prototipos
void limpiar(char*, char*);
bool contieneSubsecuencia(char *texto, char *mensaje);

int main() {
    int casos;
    Caso datos[2100]; // arreglo de estructuras para guardar todos los casos
    cout << "Ingrese el número de casos: ";
    cin >> casos;
    cin.ignore();  // limpia ek salto de linea

    FILE *archivo = fopen("registro.txt", "a");  // archivo donde se va guardando el historial dme busquedas
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    for (int i = 0; i < casos; i++) {
        cout << "\nCaso " << i + 1 << endl;
        cout << "Ingrese el titular: ";
        cin.getline(datos[i].titular, 2100);
        cout << "Ingrese el mensaje: ";
        cin.getline(datos[i].mensaje, 2100);
        limpiar(datos[i].limpioTitular, datos[i].titular);
        limpiar(datos[i].limpioMensaje, datos[i].mensaje);
        cout << "Titular limpio: " << datos[i].limpioTitular << endl;
        cout << "Mensaje limpio: " << datos[i].limpioMensaje << endl;

        fprintf(archivo, "Caso %d:\n", i + 1);
        fprintf(archivo, "Titular original: %s\n", datos[i].titular);
        fprintf(archivo, "Titular limpio: %s\n", datos[i].limpioTitular);
        fprintf(archivo, "Mensaje original: %s\n", datos[i].mensaje);
        fprintf(archivo, "Mensaje limpio: %s\n", datos[i].limpioMensaje);

        // Verificar si el mensaje está contenido como subsecuencia
        if (contieneSubsecuencia(datos[i].limpioTitular, datos[i].limpioMensaje)) {
            cout << "SI\n";
            fprintf(archivo, "Resultado: SI\n\n");
        } else {
            cout << "NO\n";
            fprintf(archivo, "Resultado: NO\n\n");
        }
    }

    fclose(archivo);
    return 0;
}

void limpiar(char *dest, char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        char c = src[i];
        if (c >= 'A' && c <= 'Z') {
            dest[j++] = c + 32;
        } else if (c >= 'a' && c <= 'z') {
            dest[j++] = c;
        }
    }
    dest[j] = '\0';
}

// Verifica si mensaje es subsecuencia de texto(esta pasrte es para cuando el mesaje no esta secuencialmente en el titular) :|
bool contieneSubsecuencia(char *texto, char *mensaje) {
    int i = 0, j = 0;
    while (texto[i] != '\0' && mensaje[j] != '\0') {
        if (texto[i] == mensaje[j]) {
            j++;
        }
        i++;
    }
    return mensaje[j] == '\0';
}
