#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <string>
#include "Fecha.h"
using namespace std;

class Solicitud {
private:
    string emisor;    // nombre de usuario de quien la envia
    Fecha fecha;      // cuando se envio

public:
    // Constructores
    Solicitud();
    Solicitud(string e, Fecha f);

    // Getters
    string getEmisor() const;
    Fecha getFecha() const;

    // Memoria dinamica extra (el texto del emisor)
    int memoriaExtra() const;
};

#endif
