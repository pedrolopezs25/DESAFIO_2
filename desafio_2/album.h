#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Foto.h"
#include "Lista.h"
using namespace std;

// Clase Album: un album de fotos de un usuario.
// La privacidad puede ser "publico", "privado" o "amigos".
class Album {
private:
    string nombre;        // Ej: "Cartagena2026"
    string privacidad;    // "publico", "privado" o "amigos"
    Lista<Foto> fotos;    // las fotos del album

public:
    // Constructores
    Album();
    Album(string n, string p);

    // Getters
    string getNombre() const;
    string getPrivacidad() const;
    int getCantidadFotos() const;
    Foto& getFoto(int posicion);

    // Setters
    void setNombre(string n);
    void setPrivacidad(string p);

    // Fotos
    void agregarFoto(Foto f);

    // Ruta del album, a partir de la ruta del usuario
    string getRuta(string rutaUsuario) const;

    // ¿Lo puede ver un amigo del dueño?
    bool loPuedeVerUnAmigo() const;
};

#endif
