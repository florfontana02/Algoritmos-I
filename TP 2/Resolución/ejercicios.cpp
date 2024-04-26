#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t;
    tiempo minT, maxT;
    minT = minimo(v);
    maxT = maximo(v);
    t = maxT - minT;

    return t;
}
 
 //como en minimo y en maximo tenemos 2 ciclos for, separados, la complejidad de peor caso es O(n)


/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d=0;
    ordenarViaje(v);
    for (int i = 0; i< v.size()-1;i++){
        d = d + distEnKM(get<1>(v[i]),get<1>(v[i+1]));
    }
    return d;
}
// como ordenarViaje contiene un ciclo for dentro de otro, concluimos que la complejidad de peor caso es O(n^2)

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    ordenarViaje(v);
    for (int i = 0; i< v.size()-1;i++){
        double dist = distEnKM(get<1>(v[i]),get<1>(v[i+1]));
        double tiempoEnHoras= (get<0>(v[i+1]) - get<0>(v[i]))/3600;
        double velocidad =  dist/tiempoEnHoras;
        if (80 < velocidad)
        resp = true ;
        
    }
    return resp;
}


// como ordenarViaje contiene un ciclo for dentro de otro, concluimos que la complejidad de peor caso es O(n^2)
/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp=0;
    for (int i = 0; i< f.size();i++){
        ordenarViaje(f[i]);
        if  (!(get<0>(f[i][0]) > tf || get<0>(f[i][f[i].size()-1]) < t0))
            resp++;
    }
    return resp;
}

/************************************ EJERCICIO recorridoNoCubierto ********************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    int t;
     for (int i = 0; i < r.size();i++){
         t=0;
         for (int j = 0; j < v.size(); j++){
            if (distEnKM(r[i],get<1>(v[j])) < u){ //o sea si el punto de v lo cubre
                t++; 
            }

         }
         if (t == 0){
            resp.push_back(r[i]);
         }
     }

    return resp;
} 
// como recorridoNoCubiero contiene un ciclo for dentro de otro, y el primero itera sobre la longitud de r (m) y 
// el segundo sobre la longitud de v (n) concluimos que su complejidad de peor caso es O(n * m).
  

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {

    grilla resp;
    double alturaGrilla = get<0>(esq1) - get<0>(esq2);
    double baseGrilla = get<1>(esq2) - get<1>(esq1);
    double alturaCelda = (alturaGrilla ) / n;
    double baseCelda = (baseGrilla ) / m;
    double latEsq1deCelda,longEsq1deCelda,latEsq2deCelda,longEsq2deCelda;
    gps esq1deCelda, esq2deCelda;
    nombre nombredeCelda;
    celda laCelda;

            for (int i = 1; i <= n ; i++) {
                for (int j = 1; j <= m ; j++){
                    latEsq1deCelda = get<0>(esq1) - alturaCelda * (i - 1);
                    longEsq1deCelda = get<1>(esq1) + baseCelda * (j - 1);
                    esq1deCelda = make_tuple(latEsq1deCelda, longEsq1deCelda);

                    latEsq2deCelda = latEsq1deCelda - alturaCelda;
                    longEsq2deCelda = longEsq1deCelda + baseCelda;
                    esq2deCelda = make_tuple(latEsq2deCelda, longEsq2deCelda);

                    nombredeCelda = make_tuple(i, j);
                    laCelda = make_tuple(esq1deCelda, esq2deCelda, nombredeCelda);
                    resp.push_back(laCelda);
                }
        }


    return resp;
}
/************************************* EJERCICIO cantidadDeSaltos ******************************/

int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0;
    ordenarViaje(v);
    vector<nombre> celdasDelViaje;

    //estos for crean una secuencia con los nombres de cada celda de los puntos del viaje ordenado
    for(int i=0;i<v.size();i++){
        for(int j=0;j<g.size();j++){
            double latEsq2DeCelda = get<0>(get<1>(g[j]));
            double latEsq1DeCelda = get<0>(get<0>(g[j]));
            double latPuntoViaje = get<0>(get<1>(v[i]));

            double longEsq1DeCelda = get<1>(get<0>(g[j]));
            double longEsq2DeCelda = get<1>(get<1>(g[j]));
            double longPuntoViaje = get<1>(get<1>(v[i]));

                //lat(celda1) < lat(p) ≤ lat(celda0) ∧ lng(celda0) ≤ lng(p) < lng(celda1)
            if ((latEsq2DeCelda < latPuntoViaje) && (latPuntoViaje <= latEsq1DeCelda) && (longEsq1DeCelda <= longPuntoViaje) && (longPuntoViaje < longEsq2DeCelda )){
                   celdasDelViaje.push_back(get<2>(g[j]));
               }
        }
    }
    //aca hacemos la sumatoria de los saltos
    for(int x=0;x<celdasDelViaje.size()-1;x++){

        double distanciaEntreCeldas = sqrt(pow(get<0>(celdasDelViaje[x])-get<0>(celdasDelViaje[x+1]),2)+ pow(get<1>(celdasDelViaje[x])-get<1>(celdasDelViaje[x+1]),2));

        if (distanciaEntreCeldas > 1){
            resp = resp + 1;
        }
    }
    
    return resp;

}


/************************************* EJERCICIO corregirViaje ************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    viaje losPuntosCorrectos;
    int contador = 0;
    //hacemos un vector con los puntos correctos
    for(int i=0; i<v.size();i++){
        contador = 0;
        for(int j=0; j<errores.size();j++){
        if (get<0>(v[i]) == errores[j]){
            contador++;
        }
        }
        if (contador == 0){
            losPuntosCorrectos.push_back(v[i]);
        }
    }


    for(int i=0; i<v.size();i++){
            for(int j=0; j<errores.size();j++){
            if (get<0>(v[i]) == errores[j])
                corregirPunto(v,i,losPuntosCorrectos);
            }
        }
}

