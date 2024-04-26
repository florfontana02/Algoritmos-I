#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
// auxiliares propios 
tiempo minimo(viaje v) {
    tiempo min = get<0>(v[0]);
    
    for(int i=0;i<v.size();i++)
        if (get<0>(v[i]) <= min) 
        min=get<0>(v[i]);
return min;
}

tiempo maximo(viaje v) {
    tiempo max = get<0>(v[0]);
    for(int i=0;i<v.size();i++)
        if (get<0>(v[i]) >= max)
        max=get<0>(v[i]);
return max;
}

void ordenarViaje(viaje &v){

    for (int i = 0 ; i <v.size() ; i++) {    
        for(int j = i; j < v.size(); j++){ 
            if(v[i] > v[j]){
                  swap(v[i], v[j]);
        }
    }

}
}
//esto devuelve los dos puntos correctos mas cercanos
tuple<tuple<tiempo, gps>,tuple<tiempo, gps>> losDosMasCercanos(tiempo t, viaje losPuntosCorrectos){

    int diff1 = INT_MAX; //es el valor maximo que puede tomar un entero, aprox +2147483647.
    tuple<tiempo, gps> elMasCercano, elSegundoMasCercano;

    for(int i=0; i<losPuntosCorrectos.size();i++){
        if(abs(t-get<0>(losPuntosCorrectos[i])) < diff1){
            diff1 = abs(t-get<0>(losPuntosCorrectos[i]));
            elMasCercano = losPuntosCorrectos[i];
        }
    }
    int diff2 = INT_MAX;
    for(int j=0; j<losPuntosCorrectos.size();j++){
        if(abs(t-get<0>(losPuntosCorrectos[j])) < diff2 && abs(t-get<0>(losPuntosCorrectos[j])) != diff1) {
            diff2 = abs(t-get<0>(losPuntosCorrectos[j]));
            elSegundoMasCercano = losPuntosCorrectos[j];
        }
    }
    tuple<tuple<tiempo, gps>,tuple<tiempo, gps>> losMasCercanos = make_tuple(elMasCercano,elSegundoMasCercano);
    return losMasCercanos;
}

void corregirPunto(viaje& v, int i,viaje losPuntosCorrectos){
    tuple<tiempo, gps> p = v[i]; //este es el punto a corregir
    //busco los dos mas cercanos temporalmente
    tuple<tuple<tiempo, gps>,tuple<tiempo, gps>> losMasCercanos = losDosMasCercanos(get<0>(v[i]),losPuntosCorrectos);
    tuple<tiempo, gps> c1 = get<0>(losMasCercanos); //este es el mas cercano
    tuple<tiempo, gps> c2 = get<1>(losMasCercanos); //este es el segundo mas cercano
    
    double latc1 = get<0>(get<1>(c1));
    double longc1 = get<1>(get<1>(c1));
    double latc2 = get<0>(get<1>(c2));
    double longc2 = get<1>(get<1>(c2));

    double proporcionTiempo = sqrt(pow(get<0>(p)-get<0>(c1),2))/(get<0>(c2) - get<0>(c1));
    double deltaLatTotal = latc2 - latc1;
    double deltaLongTotal = longc2 - longc1;

    double latp = latc1 + proporcionTiempo * deltaLatTotal;
    double longp = longc1 + proporcionTiempo * deltaLongTotal;

    get<1>(v[i]) = make_tuple(latp,longp);
    


}
//auxiliares de la catedra
const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

