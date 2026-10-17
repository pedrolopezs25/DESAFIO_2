#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Fecha.h"
#include "Lista.h"
#include "Album.h"
#include "Mensaje.h"
#include "Solicitud.h"
#include "Metricas.h"
using namespace std;

// Parte fija de la ruta, igual para todos los usuarios
const string RUTA_BASE = "/users/udeabook";

// Clase Usuario: una persona registrada en Ude@Book.
class Usuario {
private:
    // Datos personales
    int id;                    // posicion del usuario (0, 1, 2, ...)
    string nombreUsuario;      // unico
    string contrasena;
    string correo;
    string ciudad;
    string pais;
    Fecha fechaNacimiento;
    Fecha fechaInscripcion;

    // Lo que tiene cada usuario
    Lista<int> amigos;                  // ids de sus amigos
    Lista<Album> albumes;
    Lista<Solicitud> solicitudes;       // solicitudes recibidas
    Lista<Mensaje*> mensajesEnviados;   // ordenados por fecha
    Lista<Mensaje*> mensajesRecibidos;  // ordenados por fecha

public:
    // Constructores
    Usuario();
    Usuario(int i, string nombre, string clave, string email,
            string ciu, string pa, Fecha nacimiento, Fecha inscripcion);

    // Getters de datos personales
    int getId() const;
    string getNombreUsuario() const;
    string getCorreo() const;
    string getCiudad() const;
    string getPais() const;
    Fecha getFechaNacimiento() const;
    Fecha getFechaInscripcion() const;

    // Setter
    void setId(int i);

    // Inicio de sesion
    bool contrasenaCorrecta(string clave) const;

    // Rutas
    string getRuta() const;
    string getRutaFotoPerfil() const;

    // Amigos
    void agregarAmigo(int idAmigo);
    int getCantidadAmigos() const;
    int getAmigo(int posicion);

    // Albumes
    void agregarAlbum(Album a);
    int getCantidadAlbumes() const;
    Album& getAlbum(int posicion);

    // Solicitudes
    void agregarSolicitud(Solicitud s);
    int getCantidadSolicitudes() const;
    Solicitud getSolicitud(int posicion);
    void eliminarSolicitud(int posicion);
    bool tieneSolicitudDe(string nombre);

    // Mensajes
    void agregarMensajeEnviado(Mensaje* m);
    void agregarMensajeRecibido(Mensaje* m);
    int getCantidadEnviados() const;
    int getCantidadRecibidos() const;
    Mensaje* getMensajeEnviado(int posicion);
    Mensaje* getMensajeRecibido(int posicion);

    // Memoria dinamica extra: textos y todas sus listas
    // (los mensajes NO se cuentan aqui: los cuenta la Plataforma una sola vez)
    int memoriaExtra();
};

#endif
