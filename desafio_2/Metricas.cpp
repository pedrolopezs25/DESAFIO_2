#include <iostream>
#include "Metricas.h"

// Los atributos static se crean una sola vez, aqui, fuera de la clase
int Metricas::iteraciones = 0;
int Metricas::memoriaLocal = 0;
int Metricas::usosExternos = 0;

void Metricas::reiniciar() {
    iteraciones = 0;
    memoriaLocal = 0;
    usosExternos = 0;
}

void Metricas::contar() {
    iteraciones++;
}

void Metricas::agregarMemoriaLocal(int bytes) {
    memoriaLocal = memoriaLocal + bytes;
}

void Metricas::registrarUsoExterno() {
    usosExternos++;
}

int Metricas::getIteraciones() {
    return iteraciones;
}

int Metricas::getMemoriaLocal() {
    return memoriaLocal;
}

int Metricas::getUsosExternos() {
    return usosExternos;
}

void Metricas::mostrar(string funcionalidad, int memoriaEstructuras) {
    int total = memoriaEstructuras + memoriaLocal;

    cout << endl;
    cout << "----- Consumo de recursos: " << funcionalidad << " -----" << endl;
    cout << "Iteraciones: " << iteraciones << endl;
    if (usosExternos > 0) {
        cout << "Uso de componente externo (libreria random): "
             << usosExternos << " vez/veces" << endl;
    }
    cout << "Memoria en uso: " << total << " bytes ("
         << total / 1024 << " KB)" << endl;
    cout << "-------------------------------------------" << endl;
}
