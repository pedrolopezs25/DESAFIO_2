// Programa pequeño para probar la clase Fecha antes de usarla en el proyecto.
#include <iostream>
#include "Fecha.h"

using namespace std;

int main() {
    Fecha a;                          // constructor por defecto
    Fecha b(8, 10, 2026);             // solo día, mes y año
    Fecha c(12, 10, 2026, 18, 26);    // con hora y minuto
    Fecha d(c);                       // constructor de copia

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;

    cout << "b < c ?  " << (b < c) << endl;    // 1 = verdadero
    cout << "c < b ?  " << (c < b) << endl;    // 0 = falso
    cout << "c == d ? " << (c == d) << endl;
    cout << "c <= d ? " << (c <= d) << endl;

    d.setMinuto(5);
    cout << "d despues de setMinuto(5) = " << d << endl;
    cout << "c sigue igual = " << c << endl;

    return 0;
}
