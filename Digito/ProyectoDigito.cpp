#include <iostream>
using namespace std;

//Proyecto DIGITO / ISBN 
//Estatus - Funcional / Revisar Algunos puntos con la maestra
//Programador: Jesus

//Funcion que recibe los datos
void llenarVectorDigito(long long int, int []);

bool validarDigitoIsbn(int []);

int main(){

    long long int digito = 0;
    int vecDigito[13];

    cout << "Ingresa El digito / Isbn: " << endl;
    cin >> digito;

    llenarVectorDigito(digito, vecDigito);

    

    if(validarDigitoIsbn(vecDigito)){
        cout << "Codigo valido" << endl;
    }else{
        cout << "Codigo Invalido" << endl;
    }


    

    return 0;
}

void llenarVectorDigito(long long int digito, int vecDigito[]){
    int i = 12;

    while(digito != 0){
        vecDigito[i] = digito % 10;
        digito /= 10;
        i--;
    }
    /*Se usa el residuo de 10 para separa el ultimo digito
    se divide entre 10 para seguir con el siguiente y se guardan al reves
    para que queden ordenados*/
    
}

bool validarDigitoIsbn(int vecDigito[]){
    int sumatoria = 0, residuo = 0;
    for(int i = 0; i < 12; i++){
        /*Valida si la posicion es par o impar, si es par solo la suma 
        ya que se multiplicaria por 1, no tiene caso multiplicar,
        si no se multiplica por 3 y se suma*/
        if(i % 2 == 0){
            sumatoria += vecDigito[i];
        }
        else{
            sumatoria += vecDigito[i] * 3;
        }
    }
    //Calcula el residuo, primero saca el residuo de la sumatoria entre 10 y despues resta 10 - el valor obtenido
    residuo = 10 - (sumatoria % 10);
    //Si el residuo obtenido es mayor a 9 automaticamente se combierte en 0;
    if(residuo > 9) residuo = 0;
    // validar el valor obtenido con el codigo verificador, que es la utima posicion del vector
    if(residuo == vecDigito[12]){
        return true;
    }
    return false;
}