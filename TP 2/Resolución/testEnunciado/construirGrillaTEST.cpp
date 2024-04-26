#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(construirGrillaTEST, nombresCorrectosDistanciaParNParMImparArg){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                  make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                  make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                  make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                  make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                  make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
                  };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
}


//test nuestro
int apariciones(celda &c, grilla &g){
    int count = 0;
    for (int i = 0; i < g.size();i++){
        if (g[i]==c)
            count++;
    }
    return count;
}

bool sonGrillasIguales(grilla &g1, grilla &g2){

    int grillaSize = g1.size();
    if (g1.size()!= g2.size()) {
        grillaSize = grillaSize - 1;
    }
    for (int i = 0; i < g1.size();i++){
        if (apariciones(g1[i],g1) != apariciones(g2[i],g2) )
            grillaSize = grillaSize - 1;
    }

    return (grillaSize == g1.size());
}


TEST(construirGrillaTEST, comparaTodasLasCeldasConAuxiliarNuestro){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                   make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                   make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                   make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                   make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                   make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
    };



    grilla g = construirGrilla(esq1,esq2,n,m);
    string ourFirstGrid;



    EXPECT_TRUE(sonGrillasIguales(g,gres));
}