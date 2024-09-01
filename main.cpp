#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

const bool DEBUG = true;
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
int tirarDadoManual(int casillaActual) {
    int avance;
    std::cout << "INTRODUCE EL VALOR DEL DADO: " << std::endl;
    std::cin >> avance ;
    std::cout << "VALOR DEL DADO: "<< avance << std::endl;
    std::cout << "PASAS A LA CASILLA: "<< casillaActual + avance << std::endl;
    return casillaActual + avance;

}
int quienEmpieza() {
    return 1 + rand() % 2;
}
int efectoPosicion(int casillaActual) {
    if (esOca(casillaActual)) {
        std::cout << "HAS CAIDO EN UNA OCA" << std::endl;
        casillaActual= siguienteOca(casillaActual);
        std::cout << "SALTAS A LA SIGUIENTE OCA EN LA CASILLA: "<< casillaActual << std::endl;
    }
    else if (esPuente(casillaActual)) {
        std::cout << "HAS CAIDO EN UN PUENTE" << std::endl;
        casillaActual= siguientePuente(casillaActual);
        std::cout << "DE PUENTE EN PUENTE ACABO EN: "<< casillaActual << std::endl;
    }
    else if (esDados(casillaActual)) {
        std::cout << "HAS CAIDO EN DADOS" << std::endl;
        casillaActual= siguienteDado(casillaActual);
        std::cout << "DE DADO EN DADO ACABO EN: "<< casillaActual << std::endl;
    }
    else if (esLaberinto(casillaActual)) {
        std::cout << "HAS CAIDO EN UN LABERINTO" << std::endl;
        casillaActual= siguienteLaberinto(casillaActual);
        std::cout << "ME PIERDO EN UN LABERINTO Y RETROCEDO 12, AHORA ESTOY EN: "<< casillaActual << std::endl;
    }
    else if (esMuerte(casillaActual)) {
        std::cout << "HAS CAIDO EN LA MUERTE" << std::endl;
        casillaActual= siguienteMuerte(casillaActual);
        std::cout << "HE MUERTO Y ACABO EN: "<< casillaActual << std::endl;
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


int do_turno(int jugador) {
    jugador = efectoPosicion(jugador);
    efectoTiradas(jugador,1);
    std::cout << "ESTAS EN: " << jugador <<std::endl;
    std::cout << "" << std::endl;
    return jugador;
}

void turno(int &jugador) {
    std::cout << "CASILLA ACTUAL: " << jugador <<std::endl;
    if (DEBUG) {
        jugador = tirarDadoManual(jugador);
        jugador = do_turno(jugador);
    }else {
        jugador += tirarDado();
        jugador = do_turno(jugador);
    }
}

int main() {
    srand(time(NULL));
    int jugador1 = 1, jugador2 = 1;
    bool final = false;
    int empieza = quienEmpieza();
    if (empieza == 1) {
        std::cout<<"**** Empieza el jugador 1 ****"<<std::endl;
        turno(jugador1);
        std::cout<<"** TURNO DEL JUGADOR 2 **"<<std::endl;
        turno(jugador2);

    }else {
        std::cout<<"**** Empieza el jugador 2 ****"<<std::endl;
        turno(jugador2);
        std::cout<<"** TURNO DEL JUGADOR 1 **"<<std::endl;
        turno(jugador1);
    }

    while (!final) {
        if (esMeta(jugador1)) {
            std::cout << "**** Jugador 1 ha ganado! ****" << std::endl;
            final = true;
            return 0;

        } else if (esMeta(jugador2)) {
            std::cout << "**** Jugador 2 ha ganado! ****" << std::endl;
            final = true;
            return 0;
        }

        if (empieza == 1) {
            std::cout<<"** TURNO DEL JUGADOR 1 **"<<std::endl;
            turno(jugador1);
            std::cout<<"** TURNO DEL JUGADOR 2 **"<<std::endl;
            turno(jugador2);
        }else {
            std::cout<<"** TURNO DEL JUGADOR 2 **"<<std::endl;
            turno(jugador2);
            std::cout<<"** TURNO DEL JUGADOR 1 **"<<std::endl;
            turno(jugador1);
        }
    }

    return 0;
}
