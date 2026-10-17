#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <string>
#include "Lista.h"
#include "Fecha.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "MatrizAmistad.h"
#include "Metricas.h"
using namespace std;

// Clase GestorArchivos: lee los datos desde los archivos .txt al iniciar
// y guarda los cambios al salir.
//
// Formato: un registro por linea, campos separados por |
//   usuarios.txt     id|nombre|clave|correo|ciudad|pais|nacimiento|inscripcion
//   amistades.txt    idA|idB
//   albumes.txt      idUsuario|nombreAlbum|privacidad
//   fotos.txt        idUsuario|posicionAlbum|nombreFoto|fechaCaptura|tamanio|likes
//   solicitudes.txt  idReceptor|idEmisor|fecha
//   mensajes.txt     idEmisor|idReceptor|fecha|leido|texto
// Las fechas se escriben dd/mm/aaaa hh:mm (o dd/mm/aaaa sin hora).
class GestorArchivos {
private:
    string carpeta;   // carpeta donde estan los .txt, ej: "datos"

    // Ayudantes
    Lista<string> separar(string linea, int maxPartes);
    Fecha leerFecha(string texto);
    int buscarId(Lista<Usuario>& usuarios, string nombre);

public:
    GestorArchivos(string c);

    // Cargar (al iniciar el programa)
    bool cargarUsuarios(Lista<Usuario>& usuarios);
    void cargarAmistades(Lista<Usuario>& usuarios, MatrizAmistad& matriz);
    void cargarAlbumes(Lista<Usuario>& usuarios);
    void cargarFotos(Lista<Usuario>& usuarios);
    void cargarSolicitudes(Lista<Usuario>& usuarios);
    void cargarMensajes(Lista<Usuario>& usuarios, Lista<Mensaje*>& mensajes);

    // Guardar (al salir): solo lo que puede cambiar en el programa
    void guardarAmistades(Lista<Usuario>& usuarios);
    void guardarFotos(Lista<Usuario>& usuarios);
    void guardarSolicitudes(Lista<Usuario>& usuarios);
    void guardarMensajes(Lista<Usuario>& usuarios, Lista<Mensaje*>& mensajes);
};

#endif
