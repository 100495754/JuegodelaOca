#include <iostream>

const int NUM_CASILLAS = 63;
const int PUENTE_1 = 6;
const int PUENTE_2 = 12;
const int DADOS_1 = 26;
const int DADOS_2 = 53;
const int POSADA = 19;
const int PRISIÓN = 52;
const int POZO = 31;
const int LABERINTO = 42;
const int MUERTE = 58;

const int PEN_POSADA = 1;
const int PEN_PRISION = 2;
const int PEN_POZO = 3;

bool esOca(int casilla) {
    int oca = 5;
    int i = 0;
    while (oca <= casilla) {
        if (casilla == oca) {
            return true;
        }
        if (i % 2 ==0) {oca +=4;}
        else {oca +=5;}
        i++;
        std::cout<<oca<<std::endl;
    }
    return false;
}
bool esPuente(int casilla) {
    if (casilla == PUENTE_1 || casilla==PUENTE_2) {return true;}
    return false;
}

int main() {
    if (esOca(27)) {
        std::cout<<"hola" <<std::endl;
    }
    int casilla;
    casilla = 12;
    if (esPuente(casilla)) {
        if (casilla == PUENTE_1) {casilla=PUENTE_2;}
        else{casilla=PUENTE_1;}
    }
    std::cout<<casilla<<std::endl;

    return 0;
}
