#ifndef SOLICITUD_H
#define SOLICITUD_H

#include <string>
#include "Fecha.h"
using namespace std;

// Clase Solicitud: una solicitud de amistad pendiente.
// Se guarda en la lista del usuario que la RECIBE,
// por eso solo necesita saber quien la envio.
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
