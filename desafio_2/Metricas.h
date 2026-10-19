#ifndef METRICAS_H
#define METRICAS_H

#include <string>
using namespace std;

class Metricas {
private:
    static int iteraciones;
    static int memoriaLocal;
    static int usosExternos;

public:
    // Se llama al empezar cada funcionalidad: pone todo en cero
    static void reiniciar();

    // Se llama dentro de cada ciclo: suma una iteracion
    static void contar();

    // Suma los bytes de una variable local o un parametro por valor
    static void agregarMemoriaLocal(int bytes);

    // Se llama cada vez que se usa algo externo (por ejemplo, la libreria random)
    static void registrarUsoExterno();

    static int getIteraciones();
    static int getMemoriaLocal();
    static int getUsosExternos();

    // Muestra las dos metricas al final de una funcionalidad.
    // memoriaEstructuras = memoria de todos los objetos del sistema
    static void mostrar(string funcionalidad, int memoriaEstructuras);
};

#endif
