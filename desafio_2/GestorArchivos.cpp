#include <iostream>
#include <fstream>
#include "GestorArchivos.h"

GestorArchivos::GestorArchivos(string c) {
    carpeta = c;
}

// ===================== Ayudantes =====================

// Parte una linea por el caracter |
// Ej: "3|ana|clave" -> ["3", "ana", "clave"]
// maxPartes: cuando ya hay maxPartes-1 partes, el resto de la linea va
// completo en la ultima (asi el texto de un mensaje puede tener |)
Lista<string> GestorArchivos::separar(string linea, int maxPartes) {
    Lista<string> partes;
    string actual = "";

    int largo = linea.size();
    for (int i = 0; i < largo; i++) {
        char c = linea[i];
        if (c == '|' && partes.getCantidad() < maxPartes - 1) {
            partes.agregar(actual);
            actual = "";
        } else if (c != '\r') {
            actual = actual + c;
        }
        Metricas::contar();
    }
    partes.agregar(actual);
    return partes;
}

// Convierte "dd/mm/aaaa hh:mm" (o "dd/mm/aaaa") en una Fecha
Fecha GestorArchivos::leerFecha(string texto) {
    int dia = stoi(texto.substr(0, 2));
    int mes = stoi(texto.substr(3, 2));
    int anio = stoi(texto.substr(6, 4));
    int hora = 0;
    int minuto = 0;

    if (texto.size() >= 16) {
        hora = stoi(texto.substr(11, 2));
        minuto = stoi(texto.substr(14, 2));
    }
    return Fecha(dia, mes, anio, hora, minuto);
}

// Devuelve el id del usuario con ese nombre, o -1 si no existe
int GestorArchivos::buscarId(Lista<Usuario>& usuarios, string nombre) {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        Metricas::contar();
        if (usuarios[i].getNombreUsuario() == nombre) {
            return i;
        }
    }
    return -1;
}

// ===================== Cargar =====================

bool GestorArchivos::cargarUsuarios(Lista<Usuario>& usuarios) {
    ifstream archivo(carpeta + "/usuarios.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir " << carpeta << "/usuarios.txt" << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 8);
        // p: 0 id, 1 nombre, 2 clave, 3 correo, 4 ciudad, 5 pais, 6 nacimiento, 7 inscripcion
        Usuario u(stoi(p[0]), p[1], p[2], p[3], p[4], p[5], leerFecha(p[6]), leerFecha(p[7]));
        usuarios.agregar(u);
    }
    archivo.close();
    return true;
}

void GestorArchivos::cargarAmistades(Lista<Usuario>& usuarios, MatrizAmistad& matriz) {
    ifstream archivo(carpeta + "/amistades.txt");
    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 2);
        int a = stoi(p[0]);
        int b = stoi(p[1]);
        // Si la linea esta repetida (o es a|a) no se agrega otra vez,
        // asi la lista de amigos no queda con ids repetidos
        if (a == b || matriz.sonAmigos(a, b)) {
            continue;
        }
        matriz.agregarAmistad(a, b);
        usuarios[a].agregarAmigo(b);
        usuarios[b].agregarAmigo(a);
    }
    archivo.close();
}

void GestorArchivos::cargarAlbumes(Lista<Usuario>& usuarios) {
    ifstream archivo(carpeta + "/albumes.txt");
    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 3);
        int idUsuario = stoi(p[0]);
        usuarios[idUsuario].agregarAlbum(Album(p[1], p[2]));
    }
    archivo.close();
}

void GestorArchivos::cargarFotos(Lista<Usuario>& usuarios) {
    ifstream archivo(carpeta + "/fotos.txt");
    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 6);
        // p: 0 idUsuario, 1 posicionAlbum, 2 nombre, 3 fecha, 4 tamanio, 5 likes
        int idUsuario = stoi(p[0]);
        int posAlbum = stoi(p[1]);
        Foto f(p[2], leerFecha(p[3]), stoi(p[4]), stoi(p[5]));
        usuarios[idUsuario].getAlbum(posAlbum).agregarFoto(f);
    }
    archivo.close();
}

void GestorArchivos::cargarSolicitudes(Lista<Usuario>& usuarios) {
    ifstream archivo(carpeta + "/solicitudes.txt");
    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 3);
        int idReceptor = stoi(p[0]);
        int idEmisor = stoi(p[1]);
        string nombreEmisor = usuarios[idEmisor].getNombreUsuario();
        usuarios[idReceptor].agregarSolicitud(Solicitud(nombreEmisor, leerFecha(p[2])));
    }
    archivo.close();
}

// El archivo viene ordenado por fecha, asi las listas de cada usuario
// quedan ordenadas sin tener que ordenarlas
void GestorArchivos::cargarMensajes(Lista<Usuario>& usuarios, Lista<Mensaje*>& mensajes) {
    ifstream archivo(carpeta + "/mensajes.txt");
    string linea;
    while (getline(archivo, linea)) {
        Metricas::contar();
        if (linea == "") {
            continue;
        }
        Lista<string> p = separar(linea, 5);
        // p: 0 idEmisor, 1 idReceptor, 2 fecha, 3 leido, 4 texto
        int idEmisor = stoi(p[0]);
        int idReceptor = stoi(p[1]);

        Mensaje* m = new Mensaje(usuarios[idEmisor].getNombreUsuario(),
                                 usuarios[idReceptor].getNombreUsuario(),
                                 p[4], leerFecha(p[2]));
        if (p[3] == "1") {
            m->setLeido(true);
        }

        mensajes.agregar(m);
        usuarios[idEmisor].agregarMensajeEnviado(m);
        usuarios[idReceptor].agregarMensajeRecibido(m);
    }
    archivo.close();
}

// ===================== Guardar =====================

// Cada amistad se escribe una sola vez (solo cuando i < j)
void GestorArchivos::guardarAmistades(Lista<Usuario>& usuarios) {
    ofstream archivo(carpeta + "/amistades.txt");
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        for (int k = 0; k < usuarios[i].getCantidadAmigos(); k++) {
            Metricas::contar();
            int j = usuarios[i].getAmigo(k);
            if (i < j) {
                archivo << i << "|" << j << endl;
            }
        }
    }
    archivo.close();
}

// Se guardan las fotos porque los likes pueden cambiar
void GestorArchivos::guardarFotos(Lista<Usuario>& usuarios) {
    ofstream archivo(carpeta + "/fotos.txt");
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        for (int a = 0; a < usuarios[i].getCantidadAlbumes(); a++) {
            Album& album = usuarios[i].getAlbum(a);
            for (int f = 0; f < album.getCantidadFotos(); f++) {
                Metricas::contar();
                Foto& foto = album.getFoto(f);
                archivo << i << "|" << a << "|" << foto.getNombre() << "|"
                        << foto.getFechaCaptura() << "|" << foto.getTamanio() << "|"
                        << foto.getLikes() << endl;
            }
        }
    }
    archivo.close();
}

void GestorArchivos::guardarSolicitudes(Lista<Usuario>& usuarios) {
    ofstream archivo(carpeta + "/solicitudes.txt");
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        for (int s = 0; s < usuarios[i].getCantidadSolicitudes(); s++) {
            Metricas::contar();
            Solicitud sol = usuarios[i].getSolicitud(s);
            int idEmisor = buscarId(usuarios, sol.getEmisor());
            archivo << i << "|" << idEmisor << "|" << sol.getFecha() << endl;
        }
    }
    archivo.close();
}

void GestorArchivos::guardarMensajes(Lista<Usuario>& usuarios, Lista<Mensaje*>& mensajes) {
    ofstream archivo(carpeta + "/mensajes.txt");
    for (int i = 0; i < mensajes.getCantidad(); i++) {
        Metricas::contar();
        Mensaje* m = mensajes[i];
        int idEmisor = buscarId(usuarios, m->getEmisor());
        int idReceptor = buscarId(usuarios, m->getReceptor());

        archivo << idEmisor << "|" << idReceptor << "|" << m->getFechaEnvio() << "|";
        if (m->estaLeido()) {
            archivo << "1";
        } else {
            archivo << "0";
        }
        archivo << "|" << m->getTexto() << endl;
    }
    archivo.close();
}
