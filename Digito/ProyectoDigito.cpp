#include <iostream>
using namespace std;

//Proyecto DIGITO / ISBN 
//Estatus - Funcional / Revisar Algunos puntos con la maestra
//Programador: Jesus

union CodigoV{
    int validador;
 };

//Funcion que recibe los datos
int llenarVectorDigito(long long int, int [], int);
bool validarDigitoIsbn(int []);

CodigoV digitoValidador;

int main(){

    long long int digito = 0;
    int *vecDigito;
    cout << "Ingresa El digito / Isbn: " << endl;
    cin >> digito;

    if(cin.fail()){
        cout << "Error, ingresastes caracteres invalidos" << endl;
        return 0;
    }
    vecDigito = (int*)malloc(12*sizeof(int));

    llenarVectorDigito(digito, vecDigito, 12);

    if(validarDigitoIsbn(vecDigito)){
        cout << "Codigo valido" << endl;
    }else{
        cout << "Codigo Invalido" << endl;
    }

    free(vecDigito);

    return 0;
}

int llenarVectorDigito(long long int digito, int vecDig[], int i){
    if(digito == 0){
        return 0;
    }else{
        if(i == 12){
            digitoValidador.validador = digito % 10;
        }
        else{
            vecDig[i] = digito % 10;
        }
        digito /= 10;
        return llenarVectorDigito(digito, vecDig, i-1);
    }
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
    if(residuo == digitoValidador.validador){
        return true;
    }
    return false;
}