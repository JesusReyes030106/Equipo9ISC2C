/*Ya no se fabrican teclados como antes , despues de unos pocos meses,
a pepe el suyo se le ha empezado a hacer cosas raras .En concreto cuando pulsas ciertas 
teclas el teclado parece interpretar que que se han pulsado otras 


Despues de un rato de analisis ha llegado a la conclusion de que la pulsacion de la 
tecla del gion (-), tiene el mismo resultado que si pulsa la tecla de INICIO y 
el cursor se va al principio de la linea .Algo parecido ocurre con el (+) que 
lleva al final de la linea como la tecla FIN.Y al pulsar * se consigue el mismo efecto 
que con la tecla de de la FLECHA DERECHA . Pero lo peor de todo es lo que ocurre 
con el 3 que HACE LO MISMO QUE LA TECLA SUPR que borra la tecla de la derecha del cursor

*/

/*CAMBIO DE FUNCIONES DE TECLAS 


TECLA (-)= TECLA (INICIO)  
TECLA (+)= TECLA (FIN)
TECLA (*)= TECLA (DERECHA)
TECLA (3)= TECLA (SUPR)                                                                          
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAX 1000//Tamaño de el texto ingresado

//Enumeración para los posibles comandos 
enum Comando{
    INICIO,    // '-'
    FIN,       // '+'
    DERECHA,   // '*'
    ELIMINAR,  // '3'
    INSERTAR   // cualquier otro carácter
};

//Estructura que representa el editor de texto
struct Editor{
    char* buffer;       // puntero dinámico al texto
    int cursor;         // posición actual del cursor
    int longitud;       // longitud actual del texto
 
};

//PROTOTIPOS DE LAS FUNCIONES 

//Empezar en 0 y agregar el uso de memoria dinamica a el texto a leer 
void inicializarEditor(Editor &ed);
void liberarEditor(Editor &ed);

//Si se topa con algun caso especial 
Comando interpretarComando(char c);
void moverCursorInicio(Editor &ed);
void moverCursorFin(Editor &ed);
void moverCursorDerecha(Editor &ed);
void eliminarCaracter(Editor &ed);
void insertarCaracter(Editor &ed, char c);
void procesar(char entrada[], Editor &ed);
void imprimirRecursivo(const char *texto, int indice);

//crear archivo y guardar la informacion 
void guardarArchivo(const Editor &ed, const char* filename);

int main(){
    Editor ed;
    inicializarEditor(ed);
    char linea[MAX];//Guarda nuestro texto a leer

    cout<<"Ingresa una palabra o comandos:";
    cin.getline(linea,MAX);

    procesar(linea,ed);

    cout<<"Resultado: ";
    imprimirRecursivo(ed.buffer, 0); // imprimir con función recursiva carcater por carcater 
    cout<<endl;

    //Guardar resultado en archivo "RESPUESTAS", agregando sin borrar contenido anterior
    guardarArchivo(ed,"RESPUESTAS");

    liberarEditor(ed);

    return 0;
}

void inicializarEditor(Editor &ed){
    ed.buffer=new char[MAX];
    ed.buffer[0]='\0';//Caracter nulo y asi no imprima basura 
    ed.cursor=0;
    ed.longitud=0;
   
}

void liberarEditor(Editor &ed){
    delete[]ed.buffer;//Libera la memoria dinamica del texto
    ed.buffer=nullptr;//indica que el puntero ya no apunta a una direccion valida y asi evitamos errores

    //reinicia los valores en 0 para cuando se vuelva ejecutar 
    ed.cursor=0;//reinicia posicion del cursor 
    ed.longitud=0;//Tambien se reinicia el tamaño del texto a 0
}

// Retorna la acción correspondiente para un carácter dado
Comando interpretarComando(char c){
    switch(c){
        case '-':return INICIO;
        case '+':return FIN;
        case '*':return DERECHA;
        case '3':return ELIMINAR;
        default:return INSERTAR;//insertar cualquier otro caracter (No caso especial)
    }
}

// Procesa la cadena de entrada caracter por caracter
void procesar(char entrada[],Editor &ed){
    for(int i=0;entrada[i]!='\0';i++){
        char c=entrada[i];//Va guardando los caracteres actuales 

        Comando cmd = interpretarComando(c);//con los datos guardados verifica si hay algun caso especial 

        switch(cmd){//dependiendo si hay algun caso especial o no realoza la funcion requerida 
            case INICIO:
                moverCursorInicio(ed);
                break;
            case FIN:
                moverCursorFin(ed);
                break;
            case DERECHA:
                moverCursorDerecha(ed);
                break;
            case ELIMINAR:
                eliminarCaracter(ed);
                break;
            case INSERTAR:
                insertarCaracter(ed,c);
                break;
        }
    }
}


void moverCursorInicio(Editor &ed){
    ed.cursor=0;
}

void moverCursorFin(Editor &ed){
    ed.cursor=ed.longitud;
}

void moverCursorDerecha(Editor &ed){
    if(ed.cursor<ed.longitud)
        ed.cursor++;
}

void eliminarCaracter(Editor &ed){
    if(ed.cursor<ed.longitud){
        for(int i=ed.cursor;i<ed.longitud-1;i++){
            ed.buffer[i]=ed.buffer[i+1];
            //se recorren a la izquierda y el ultimo caracter que estaria repitiendo se borra en longitud--
        }
        ed.longitud--;//elimino el caracter repetido
        ed.buffer[ed.longitud]='\0';// se pone para que el caracter siga siendo nulo despues del ultimo caracter valido
    }
}

void insertarCaracter(Editor &ed,char c){
    if(ed.longitud<MAX-1){//Verifica si aun hay espacio para añadir un caracter mas 

        //recorre desde el final hasta la pos del cursor y despues dezplaza esos caracteres un lugar a la derecha 
        for(int i=ed.longitud;i>ed.cursor;i--){
            ed.buffer[i]=ed.buffer[i-1];
        }
        ed.buffer[ed.cursor]=c;//Inserta el carcater en el espacio generado
        ed.longitud++;//como se agrego un carcater la longitud aumenta igual 1
        ed.buffer[ed.longitud]='\0';//indicamos que el ultimo caracter nuevo es el final de longitud 
        ed.cursor++;//cursor al final
    }
}

//Función recursiva para imprimir el resultado carácter por carácter
//indice:posicion a imprimir 
void imprimirRecursivo(const char*texto,int indice){
    if(texto[indice]=='\0')return;//si no hay nada que imprimir retorna 
    cout<<texto[indice];
    imprimirRecursivo(texto,indice+1);//aumenta la posicion para imprimir el siguiente carcater 
}

// Guardar el contenido del editor en archivo de texto,
// agrega al final sin borrar el contenido previo
void guardarArchivo(const Editor &ed,const char* filename){
    FILE *archivo=fopen(filename,"a");//"a" para abrir sin borrar
    if(archivo==NULL){
        cerr<<"Error:No se pudo crear o abrir el archivo para guardar\n";
        return;
    }
    fwrite(ed.buffer,sizeof(char),ed.longitud,archivo);//Escribe los carcateres del texto en el archivo
    fwrite("\n",sizeof(char),1,archivo);// agrega salto de línea para separar entradas
    fclose(archivo);
}
