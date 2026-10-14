#include "Usuario.h"

// ===== Constructores =====

Usuario::Usuario() {
    id = -1;
    nombreUsuario = "";
    contrasena = "";
    correo = "";
    ciudad = "";
    pais = "";
}

Usuario::Usuario(int i, string nombre, string clave, string email,
                 string ciu, string pa, Fecha nacimiento, Fecha inscripcion) {
    id = i;
    nombreUsuario = nombre;
    contrasena = clave;
    correo = email;
    ciudad = ciu;
    pais = pa;
    fechaNacimiento = nacimiento;
    fechaInscripcion = inscripcion;
}

// ===== Getters y setter =====

int Usuario::getId() const {
    return id;
}

string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

string Usuario::getCorreo() const {
    return correo;
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

Fecha Usuario::getFechaNacimiento() const {
    return fechaNacimiento;
}

Fecha Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

void Usuario::setId(int i) {
    id = i;
}

// ===== Inicio de sesion =====

// No hay getter de la contrasena: solo se puede preguntar si es correcta
bool Usuario::contrasenaCorrecta(string clave) const {
    if (clave == contrasena) {
        return true;
    }
    return false;
}

// ===== Rutas =====

// Ej: "/users/udeabook/juanito76"
string Usuario::getRuta() const {
    return RUTA_BASE + "/" + nombreUsuario;
}

// Ej: "/users/udeabook/juanito76/albums/profile.png"
string Usuario::getRutaFotoPerfil() const {
    return getRuta() + "/albums/profile.png";
}

// ===== Amigos =====

void Usuario::agregarAmigo(int idAmigo) {
    amigos.agregar(idAmigo);
}

int Usuario::getCantidadAmigos() const {
    return amigos.getCantidad();
}

int Usuario::getAmigo(int posicion) {
    return amigos[posicion];
}

// ===== Albumes =====

void Usuario::agregarAlbum(Album a) {
    albumes.agregar(a);
}

int Usuario::getCantidadAlbumes() const {
    return albumes.getCantidad();
}

Album& Usuario::getAlbum(int posicion) {
    return albumes[posicion];
}

// ===== Solicitudes =====

void Usuario::agregarSolicitud(Solicitud s) {
    solicitudes.agregar(s);
}

int Usuario::getCantidadSolicitudes() const {
    return solicitudes.getCantidad();
}

Solicitud Usuario::getSolicitud(int posicion) {
    return solicitudes[posicion];
}

void Usuario::eliminarSolicitud(int posicion) {
    solicitudes.eliminar(posicion);
}

// ¿Este usuario ya tiene una solicitud pendiente enviada por "nombre"?
bool Usuario::tieneSolicitudDe(string nombre) {
    for (int i = 0; i < solicitudes.getCantidad(); i++) {
        if (solicitudes[i].getEmisor() == nombre) {
            return true;
        }
    }
    return false;
}

// ===== Mensajes =====

void Usuario::agregarMensajeEnviado(Mensaje* m) {
    mensajesEnviados.agregar(m);
}

void Usuario::agregarMensajeRecibido(Mensaje* m) {
    mensajesRecibidos.agregar(m);
}

int Usuario::getCantidadEnviados() const {
    return mensajesEnviados.getCantidad();
}

int Usuario::getCantidadRecibidos() const {
    return mensajesRecibidos.getCantidad();
}

Mensaje* Usuario::getMensajeEnviado(int posicion) {
    return mensajesEnviados[posicion];
}

Mensaje* Usuario::getMensajeRecibido(int posicion) {
    return mensajesRecibidos[posicion];
}
