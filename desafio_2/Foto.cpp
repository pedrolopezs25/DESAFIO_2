#include "Foto.h"

// ===== Constructores =====

// Foto vacia
Foto::Foto() {
    nombre = "";
    tamanio = 0;
    likes = 0;
}

// Foto con todos sus datos
Foto::Foto(string n, Fecha f, int t, int l) {
    nombre = n;
    fechaCaptura = f;
    tamanio = t;
    likes = l;
}

// ===== Getters =====

string Foto::getNombre() const {
    return nombre;
}

Fecha Foto::getFechaCaptura() const {
    return fechaCaptura;
}

int Foto::getTamanio() const {
    return tamanio;
}

int Foto::getLikes() const {
    return likes;
}

// ===== Setters =====

void Foto::setNombre(string n) {
    nombre = n;
}

void Foto::setFechaCaptura(Fecha f) {
    fechaCaptura = f;
}

void Foto::setTamanio(int t) {
    tamanio = t;
}

void Foto::setLikes(int l) {
    likes = l;
}

// ===== Likes =====

// Suma un like
void Foto::darLike() {
    likes++;
}

// Resta un like, pero nunca deja los likes en negativo
void Foto::quitarLike() {
    if (likes > 0) {
        likes--;
    }
}

// ===== Ruta =====

// Ejemplo: si rutaAlbum es "/users/X/juanito76/albums/Cartagena2026"
// y el nombre es "Malecon2612", devuelve
// "/users/X/juanito76/albums/Cartagena2026/Malecon2612.png"
string Foto::getRuta(string rutaAlbum) const {
    return rutaAlbum + "/" + nombre + ".png";
}

// ===== Memoria =====

// El objeto Foto ya se cuenta con sizeof(Foto) en el arreglo de su album.
// Aqui sumamos lo que no esta en sizeof: los caracteres del nombre.
int Foto::memoriaExtra() const {
    return nombre.size();
}
