#ifndef MATRIZAMISTAD_H
#define MATRIZAMISTAD_H

// Clase MatrizAmistad: una tabla de N x N.
// matriz[i][j] es true si el usuario i y el usuario j son amigos.
class MatrizAmistad {
private:
    bool** matriz;   // arreglo dinamico de filas; cada fila es un arreglo de bool
    int n;           // cantidad de usuarios (filas y columnas)

public:
    MatrizAmistad(int cantidadUsuarios);
    MatrizAmistad(const MatrizAmistad& otra);
    ~MatrizAmistad();

    MatrizAmistad& operator=(const MatrizAmistad& otra);

    void agregarAmistad(int i, int j);
    bool sonAmigos(int i, int j) const;
    int contarAmigosEnComun(int i, int j) const;
    int getCantidadUsuarios() const;
};

#endif
