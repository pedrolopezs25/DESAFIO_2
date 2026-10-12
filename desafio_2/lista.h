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
    Lista(const Lista<T>& otra);
    ~Lista();

    Lista<T>& operator=(const Lista<T>& otra);

    void agregar(T elemento);
    void eliminar(int posicion);
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

// Constructor de copia: crea una lista nueva con su PROPIO arreglo
// y copia ahi los elementos de la otra lista.
template <typename T>
Lista<T>::Lista(const Lista<T>& otra) {
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    datos = new T[capacidad];

    for (int i = 0; i < cantidad; i++) {
        datos[i] = otra.datos[i];
    }
}

// Destructor: libera la memoria del arreglo
template <typename T>
Lista<T>::~Lista() {
    delete[] datos;
}

// Asignacion: lista1 = lista2;
// Borra el arreglo viejo y crea uno nuevo con los elementos de la otra.
template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
    if (this == &otra) {
        return *this;
    }

    delete[] datos;

    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    datos = new T[capacidad];

    for (int i = 0; i < cantidad; i++) {
        datos[i] = otra.datos[i];
    }

    return *this;
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

// Elimina el elemento de la posicion indicada.
// Los elementos que estan despues se corren un puesto a la izquierda.
template <typename T>
void Lista<T>::eliminar(int posicion) {
    if (posicion < 0 || posicion >= cantidad) {
        return;
    }

    for (int i = posicion; i < cantidad - 1; i++) {
        datos[i] = datos[i + 1];
    }

    cantidad--;
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

