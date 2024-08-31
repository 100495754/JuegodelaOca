#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

const int NUM_CASILLAS = 63;
const int PUENTE_1 = 6;
const int PUENTE_2 = 12;
const int DADOS_1 = 26;
const int DADOS_2 = 53;
const int POSADA = 19;
const int PRISION = 52;
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

    return casilla == PUENTE_1 || casilla == PUENTE_2;
}

bool esDados(int casilla) {

    return casilla == DADOS_1 || casilla == DADOS_2;
}

bool esLaberinto(int casilla) {

    return casilla == LABERINTO;
}

bool esMuerte(int casilla) {

    return casilla == MUERTE;
}

bool esPosada(int casilla) {

    return casilla == POSADA;
}

bool esPrision(int casilla) {

    return casilla == PRISION;
}

bool esPozo(int casilla) {

    return casilla == POZO;
}

bool esMeta(int casilla) {

    return casilla >= NUM_CASILLAS;
}


int siguienteOca(int casilla) {
    if (esOca(casilla)) {
        casilla+=4;
        if (!esOca(casilla)) {
            casilla++;
        }
        return casilla;
    }
}
int siguientePuente(int casilla) {
    if (esPuente(casilla)) {
        if (casilla == PUENTE_1) {
            casilla=PUENTE_2;
        }
        else {casilla=PUENTE_1;}
        return casilla;
    }
}
int siguienteDado(int casilla) {
    if (esDados(casilla)) {
        if (casilla == DADOS_1) {
            casilla=DADOS_2;
        }
        else {casilla=DADOS_1;}
        return casilla;
    }
}
int siguienteLaberinto(int casilla) {
    if (esLaberinto(casilla)) {
        casilla-=12;
    }return casilla;
}
int siguienteMuerte(int casilla) {
    if (esMuerte(casilla)) {
        casilla=1;
    }return casilla;
}
int tirarDado() {
    return 1 + rand() % 6;//limiteInferior + rand() % (limiteSuperior+1-limiteInferior).
}
int quienEmpieza() {
    return 1 + rand() % 2;
}
int efectoPosicion(int casillaActual) {
    if (esOca(casillaActual)) {
        casillaActual= siguientePuente(casillaActual);
    }
    else if (esPuente(casillaActual)) {
        casillaActual= siguientePuente(casillaActual);
    }
    else if (esDados(casillaActual)) {
        casillaActual= siguienteDado(casillaActual);
    }
    else if (esLaberinto(casillaActual)) {
        casillaActual= siguienteLaberinto(casillaActual);
    }
    else if (esMuerte(casillaActual)) {
        casillaActual= siguienteMuerte(casillaActual);
    }
    return casillaActual;
}

int efectoTiradas(int casillaActual, int numeroDeTiradas) {
    if (casillaActual == POSADA) {
        numeroDeTiradas-=1;
    }
    else if (casillaActual == PRISION) {
        numeroDeTiradas-=2;
    }
    else if (casillaActual == POZO) {
        numeroDeTiradas-=3;
    }
    return numeroDeTiradas;
}


int main() {
    srand(time(NULL));
    if (quienEmpieza()==1) {
        std::cout<<"**** Empieza el jugador 1 ****"<<std::endl;
    }else {
        std::cout<<"**** Empieza el jugador 2 ****"<<std::endl;
    }
    return 0;
}
