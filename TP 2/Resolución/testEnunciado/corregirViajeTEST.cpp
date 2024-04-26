#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(corregirViajeTEST, faltaElUltimo){
    viaje v = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
               medicion(T0+30, puntoGps(-34.591586, -58.401064)),
               medicion(T0+494, puntoGps(-34.563746, -58.436637)),
               medicion(T0+999, puntoGps(-34.549657, -58.437327)),
               medicion(T0+92, puntoGps(-34.594553, -58.402426)),
               medicion(T0+65, puntoGps(-34.590787, -58.402222)),
               medicion(T0+230, puntoGps(-34.584572, -58.416942)),
               medicion(T0+873, puntoGps(-34.559236, -58.427499)),
               medicion(T0+675, puntoGps(-34.578941, -58.424878)),
               medicion(T0+1051, puntoGps(0, 0))};

    viaje res = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
                 medicion(T0+30, puntoGps(-34.591586, -58.401064)),
                 medicion(T0+494, puntoGps(-34.563746, -58.436637)),
                 medicion(T0+999, puntoGps(-34.549657, -58.437327)),
                 medicion(T0+92, puntoGps(-34.594553, -58.402426)),
                 medicion(T0+65, puntoGps(-34.590787, -58.402222)),
                 medicion(T0+230, puntoGps(-34.584572, -58.416942)),
                 medicion(T0+873, puntoGps(-34.559236, -58.427499)),
                 medicion(T0+675, puntoGps(-34.578941, -58.424878)),
                 medicion(T0+1051, puntoGps(-34.545704, -58.441383))};
    vector<tiempo> errores = {T0+1051};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}


TEST(corregirViajeTEST, tresErrores){
    viaje v = {medicion(7, puntoGps(0,5)),
               medicion(10, puntoGps(1200,600)),
               medicion(20, puntoGps(1400,600)),
               medicion(30, puntoGps(1600,800)),
               medicion(40, puntoGps(1800,800)),
               medicion(50, puntoGps(2000,1000)),
               medicion(60, puntoGps(3,2)),
               medicion(70, puntoGps(0,0)),
               medicion(80, puntoGps(2600,800)),
               medicion(90, puntoGps(2600,600)),
               medicion(100, puntoGps(3000,500)),
               medicion(110, puntoGps(3200,600))};

    viaje res = {medicion(7, puntoGps(1260,600)),
                  medicion(10, puntoGps(1200,600)),
                  medicion(20, puntoGps(1400,600)),
                  medicion(30, puntoGps(1600,800)),
                  medicion(40, puntoGps(1800,800)),
                  medicion(50, puntoGps(2000,1000)),
                  medicion(60, puntoGps(2200,1200)),
                  medicion(70, puntoGps(2800,733.3333333333)),
                  medicion(80, puntoGps(2600,800)),
                  medicion(90, puntoGps(2600,600)),
                  medicion(100, puntoGps(3000,500)),
                  medicion(110, puntoGps(3200,600))};
    vector<tiempo> errores = {7,60,70};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}
