#include <iostream>
#include "Plataforma.h"

using namespace std;

int main() {
    Plataforma plataforma("datos");

    if (!plataforma.cargar()) {
        cout << "No se pudieron cargar los datos. Revise la carpeta 'datos'." << endl;
        return 1;
    }

    plataforma.ejecutar();
    return 0;
}
