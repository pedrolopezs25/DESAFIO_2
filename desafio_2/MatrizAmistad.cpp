#include "MatrizAmistad.h"

// Crea la tabla de n x n con todas las casillas en false (nadie es amigo)
MatrizAmistad::MatrizAmistad(int cantidadUsuarios) {
    n = cantidadUsuarios;
    matriz = new bool*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = false;
            Metricas::contar();
        }
    }
}

// Constructor de copia: crea su propia tabla y copia casilla por casilla
MatrizAmistad::MatrizAmistad(const MatrizAmistad& otra) {
    n = otra.n;
    matriz = new bool*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = otra.matriz[i][j];
        }
    }
}

// Destructor: primero borra cada fila y luego el arreglo de filas
MatrizAmistad::~MatrizAmistad() {
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Asignacion: borra la tabla vieja y copia la otra
MatrizAmistad& MatrizAmistad::operator=(const MatrizAmistad& otra) {
    if (this == &otra) {
        return *this;
    }

    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    n = otra.n;
    matriz = new bool*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = otra.matriz[i][j];
        }
    }
    return *this;
}

// La amistad es mutua: se marca en las dos casillas
void MatrizAmistad::agregarAmistad(int i, int j) {
    matriz[i][j] = true;
    matriz[j][i] = true;
}

// Responde al instante, sin recorrer nada
bool MatrizAmistad::sonAmigos(int i, int j) const {
    return matriz[i][j];
}

// Recorre todas las columnas: cuenta las que tienen true en la fila i Y en la fila j
int MatrizAmistad::contarAmigosEnComun(int i, int j) const {
    int contador = 0;
    for (int k = 0; k < n; k++) {
        Metricas::contar();
        if (matriz[i][k] && matriz[j][k]) {
            contador++;
        }
    }
    return contador;
}

int MatrizAmistad::getCantidadUsuarios() const {
    return n;
}

int MatrizAmistad::memoria() const {
    int filas = n * sizeof(bool*);      // el arreglo de filas
    int casillas = n * n * sizeof(bool); // todas las casillas
    return sizeof(MatrizAmistad) + filas + casillas;
}
