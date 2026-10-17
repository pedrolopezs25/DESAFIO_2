#ifndef FOTO_H
#define FOTO_H

#include <string>
#include "Fecha.h"
using namespace std;

// Clase Foto: una foto que esta dentro de un album.
class Foto {
private:
    string nombre;        // nombre del archivo, sin ".png". Ej: "Malecon2612"
    Fecha fechaCaptura;   // cuando se tomo la foto
    int tamanio;          // tamaño del archivo en KB
    int likes;            // cantidad de likes

public:
    // Constructores
    Foto();
    Foto(string n, Fecha f, int t, int l);

    // Getters
    string getNombre() const;
    Fecha getFechaCaptura() const;
    int getTamanio() const;
    int getLikes() const;

    // Setters
    void setNombre(string n);
    void setFechaCaptura(Fecha f);
    void setTamanio(int t);
    void setLikes(int l);

    // Likes
    void darLike();
    void quitarLike();

    // Ruta completa del archivo, a partir de la ruta del album
    string getRuta(string rutaAlbum) const;

    // Memoria dinamica extra (el texto del nombre)
    int memoriaExtra() const;
};

#endif

