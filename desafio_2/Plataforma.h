#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <string>
#include <random>
#include <chrono>
#include "Lista.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "MatrizAmistad.h"
#include "GestorArchivos.h"
#include "Metricas.h"
using namespace std;

// Clase Plataforma: es Ude@Book completo.
// Guarda todos los datos, muestra los menus y llama a cada funcionalidad.
class Plataforma {
private:
    GestorArchivos gestor;      // lee y guarda los archivos .txt
    Lista<Usuario> usuarios;    // todos los usuarios
    Lista<Mensaje*> mensajes;   // todos los mensajes (la Plataforma los borra al final)
    MatrizAmistad* matriz;      // se crea despues de saber cuantos usuarios hay
    int idActual;               // usuario con la sesion abierta (-1 = nadie)
    mt19937 generador;          // numeros aleatorios (libreria externa <random>)

    // Ayudantes
    int leerOpcion();
    int buscarUsuario(string nombre);
    int memoriaDelSistema();
    Fecha fechaDeHoy();

    // Menus y funcionalidades
    void iniciarSesion();
    void mostrarFotosAmigos();
    void elegirFotos(Lista<int> pesos);
    int pesoAmigo(int comunes);
    void menuUsuario();
    void verSolicitudes();
    void enviarSolicitud();
    int elegirAmigo();
    void visitarPerfil();
    void carrusel(Album& album, string rutaAlbum);
    void sugerencias();
    void enviarMensaje();
    void leerMensajesNuevos();
    bool leerFecha(string texto, Fecha& resultado);
    void buscarMensajes();

public:
    Plataforma(string carpeta);
    ~Plataforma();

    bool cargar();
    void ejecutar();
    void guardar();
};

#endif
