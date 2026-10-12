// Prueba del paso 3b: copiar listas y eliminar elementos.
#include <iostream>
#include "Lista.h"

using namespace std;

void mostrar(Lista<int>& lista) {
    for (int i = 0; i < lista.getCantidad(); i++) {
        cout << lista[i] << " ";
    }
    cout << "(cantidad=" << lista.getCantidad() << ")" << endl;
}

int main() {
    Lista<int> a;
    for (int i = 1; i <= 5; i++) {
        a.agregar(i * 10);
    }
    cout << "a: ";
    mostrar(a);

    // 1. Constructor de copia
    Lista<int> b(a);
    b[0] = 999;
    cout << "b (copia de a, con b[0]=999): ";
    mostrar(b);
    cout << "a no cambia: ";
    mostrar(a);

    // 2. Operador =
    Lista<int> c;
    c.agregar(1);
    c = a;
    c.agregar(60);
    cout << "c (despues de c = a y agregar 60): ";
    mostrar(c);
    cout << "a no cambia: ";
    mostrar(a);

    // 3. Eliminar
    a.eliminar(1);
    cout << "a despues de eliminar la posicion 1: ";
    mostrar(a);
    a.eliminar(0);
    cout << "a despues de eliminar la posicion 0: ";
    mostrar(a);
    a.eliminar(50);
    cout << "a despues de eliminar la posicion 50 (no existe): ";
    mostrar(a);

    return 0;
}

