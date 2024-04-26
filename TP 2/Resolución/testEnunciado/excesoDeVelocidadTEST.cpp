#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

TEST(excesoDeVelocidadTEST, noSuperaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 1000, 0)),
               medicion(unaHora*2, desviarPunto(P, 2000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, superaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 100000, 0)),
               medicion(unaHora*2, desviarPunto(P, 200000, 0))}; // 100 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}


// agregamos un test con el viaje desordenado para que cubra todas las lineas de ordenarViaje(v)

TEST(excesoDeVelocidadTEST, noSuperaLaVelocidadViajeDesordenado){
    viaje v = {medicion(0.0, P),
               medicion(unaHora*2, desviarPunto(P, 2000, 0)),
               medicion(unaHora, desviarPunto(P, 1000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}
/**
TEST(excesoDeVelocidadTEST, SuperaLaVelocidad2){
    const gps P1 = puntoGps(-33, -34);
    viaje v = {medicion(unaHora, P1),//90km/h
                 medicion(unaHora*2, desviarPunto(P, 90000, 0)),
                 medicion(unaHora*3, desviarPunto(P, 2000, 0)),
                 medicion(unaHora*4, desviarPunto(P, 2000, 0)),
                 medicion(unaHora*5, desviarPunto(P, 2000, 0)),
                 medicion(unaHora*6, desviarPunto(P, 2000, 0)),
               medicion(unaHora*7, desviarPunto(P, 2000, 0))}; // 1 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}
**/