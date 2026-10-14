#include "Album.h"

// ===== Constructores =====

// Album vacio
Album::Album() {
    nombre = "";
    privacidad = "privado";
}

// Album con nombre y privacidad
Album::Album(string n, string p) {
    nombre = n;
    privacidad = p;
}

// ===== Getters =====

string Album::getNombre() const {
    return nombre;
}

string Album::getPrivacidad() const {
    return privacidad;
}

int Album::getCantidadFotos() const {
    return fotos.getCantidad();
}

// Devuelve la foto por referencia, para poder darle like
Foto& Album::getFoto(int posicion) {
    return fotos[posicion];
}

// ===== Setters =====

void Album::setNombre(string n) {
    nombre = n;
}

void Album::setPrivacidad(string p) {
    privacidad = p;
}

// ===== Fotos =====

void Album::agregarFoto(Foto f) {
    fotos.agregar(f);
}

// ===== Ruta =====

// Ejemplo: si rutaUsuario es "/users/udeabook/juanito76"
// devuelve "/users/udeabook/juanito76/albums/Cartagena2026"
string Album::getRuta(string rutaUsuario) const {
    return rutaUsuario + "/albums/" + nombre;
}

// ===== Privacidad =====

// Un amigo puede ver los albumes "publico" y "amigos", pero no los "privado"
bool Album::loPuedeVerUnAmigo() const {
    if (privacidad == "publico" || privacidad == "amigos") {
        return true;
    }
    return false;
}
