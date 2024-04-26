#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

//eliminamos el test de la cátedra que no funcionaba, estos son los nuestros


TEST(cantidadDeSaltosTEST, viajeDesordenadoCasiTodosSaltos){
    grilla g = construirGrilla(puntoGps(3000.0,0.0),puntoGps(0.0,3000.0), 6, 6);



    viaje v = {medicion(1.5, puntoGps(250, 0)),
               medicion(1.7, puntoGps(2750, 2750)),
               medicion(1.8, puntoGps(2250, 2750)),
               medicion(1.9, puntoGps(1250, 2750)),
               medicion(1.6, puntoGps(1250, 250))};

    EXPECT_EQ(cantidadDeSaltos(g,v),3);
}

TEST(cantidadDeSaltosTEST, viajeDesordenadoTodosSonSaltos){
    grilla g = construirGrilla(puntoGps(5000.0,1000.0),puntoGps(1000.0,7000.0), 4, 6);



    viaje v = {medicion(1.5, puntoGps(4500, 1500)),
               medicion(1.7, puntoGps(2500, 5500)),
               medicion(1.8, puntoGps(4500, 6500)),
               medicion(1.9, puntoGps(2500, 3500)),
               medicion(2.0, puntoGps(1500, 5500)),
               medicion(1.6, puntoGps(3500, 3500))};

    EXPECT_EQ(cantidadDeSaltos(g,v),5);
}

TEST(cantidadDeSaltosTEST, viajeDesordenadoSinSaltos){
    grilla g = construirGrilla(puntoGps(5000.0,1000.0),puntoGps(1000.0,7000.0), 4, 6);



    viaje v = {medicion(1.5, puntoGps(1500, 2500)),
               medicion(1.7, puntoGps(2500, 3500)),
               medicion(1.8, puntoGps(3500, 3500)),
               medicion(1.9, puntoGps(4500, 3500)),
               medicion(2.0, puntoGps(4500, 4500)),
               medicion(1.6, puntoGps(1500, 3500))};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}