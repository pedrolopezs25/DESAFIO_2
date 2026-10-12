#ifndef LISTA_H
#define LISTA_H

// Clase Lista: un arreglo dinamico que crece cuando se llena.
// La hacemos nosotros porque el enunciado no permite usar vector.
// T puede ser cualquier tipo: int, Fecha, Usuario*, etc.
// Por ser plantilla, todo el codigo va en este archivo .h
template <typename T>
class Lista {
private:
    T* datos;        // arreglo dinamico
    int cantidad;    // cuantos elementos hay
    int capacidad;   // cuantos elementos caben

public:
    Lista();
    ~Lista();

    void agregar(T elemento);
    T& operator[](int posicion);
    int getCantidad() const;
    int getCapacidad() const;
};

// Constructor: empieza con espacio para 4 elementos
template <typename T>
Lista<T>::Lista() {
    capacidad = 4;
    cantidad = 0;
    datos = new T[capacidad];
}

// Destructor: libera la memoria del arreglo
template <typename T>
Lista<T>::~Lista() {
    delete[] datos;
}

// Agrega un elemento al final.
// Si el arreglo esta lleno, primero crea uno del doble de tamaño.
template <typename T>
void Lista<T>::agregar(T elemento) {
    if (cantidad == capacidad) {
        int nuevaCapacidad = capacidad * 2;
        T* nuevo = new T[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevo[i] = datos[i];
        }

        delete[] datos;
        datos = nuevo;
        capacidad = nuevaCapacidad;
    }

    datos[cantidad] = elemento;
    cantidad++;
}

// Permite usar la lista como un arreglo: lista[0], lista[1], ...
template <typename T>
T& Lista<T>::operator[](int posicion) {
    return datos[posicion];
}

template <typename T>
int Lista<T>::getCantidad() const {
    return cantidad;
}

template <typename T>
int Lista<T>::getCapacidad() const {
    return capacidad;
}

#endif

