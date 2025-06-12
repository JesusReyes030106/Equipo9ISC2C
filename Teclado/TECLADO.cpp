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
TECLA (*)= TECLA (->)
TECLA (3)= TECLA (SUPR)                                                                          
*/

#include <iostream> 

using namespace std;


int main(){
    string entrada;
    cout<<"Ingrese un mensaje:"<<endl;
    getline(cin,entrada); //Esto nos lee todo la linea escrita por el usuario

    string texto="";//Inicializamos el texto vacio
    int cursor=0; // Este sera la posicion actual de nuestro cursor 

    for(char c : entrada){//Leer recorriendo caracter por caracter la linea de entrada 
        if(c=='-'){
            cursor=0;
        }else{
            texto.insert(cursor,1,c);   //Si no hay un caso especial de tecleado se escribe tal cual
            cursor++;// Mueve el cursor mediante se vaya avanzando
        }

    }

    cout<<"Texto final:"<<texto;
    return 0;
}