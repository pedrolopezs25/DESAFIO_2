#ifndef METRICAS_H
#define METRICAS_H

#include <string>
using namespace std;

// Clase Metricas: mide el consumo de recursos de cada funcionalidad.
// - Cuenta las iteraciones (vueltas de los ciclos).
// - Suma la memoria de las variables locales y parametros por valor.
// - Muestra los resultados al final.
//
// Sus atributos y metodos son "static": pertenecen a la clase y no a un objeto.
// Asi cualquier clase puede escribir Metricas::contar(); sin tener que
// recibir un objeto Metricas por parametro.
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
