#ifndef MENSAJE_H
#define MENSAJE_H

#include <iostream>
#include <string>
#include "Fecha.h"
using namespace std;

// Clase Mensaje: un texto que un usuario le envia a otro.
class Mensaje {
private:
    string emisor;      // nombre de usuario de quien lo envia
    string receptor;    // nombre de usuario de quien lo recibe
    string texto;       // maximo 512 caracteres
    Fecha fechaEnvio;
    bool leido;         // true = leido, false = no leido

public:
    // Constructores
    Mensaje();
    Mensaje(string e, string r, string t, Fecha f);

    // Getters
    string getEmisor() const;
    string getReceptor() const;
    string getTexto() const;
    Fecha getFechaEnvio() const;
    bool estaLeido() const;

    // Marca el mensaje como leido
    void marcarLeido();

    // Para cargar el estado desde el archivo
    void setLeido(bool l);

    // ¿La fecha del mensaje esta entre inicio y fin (ambas inclusive)?
    bool estaEnRango(Fecha inicio, Fecha fin) const;

    // Memoria total del mensaje: el objeto mas sus textos
    int memoria() const;

    // Funcion amiga para imprimir el mensaje con cout
    friend ostream& operator<<(ostream& salida, const Mensaje& m);
};

#endif
