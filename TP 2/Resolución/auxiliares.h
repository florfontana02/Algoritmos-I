#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

tiempo minimo(viaje v);
tiempo maximo(viaje v);
void ordenarViaje(viaje &v);
tuple<tuple<tiempo, gps>,tuple<tiempo, gps>> losDosMasCercanos(tiempo t, viaje losPuntosCorrectos);
void corregirPunto(viaje& v, int i,viaje losPuntosCorrectos);
double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

#endif //TRANSPORTEURBANO_AUXILIARES_H
