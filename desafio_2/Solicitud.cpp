#include "Solicitud.h"

Solicitud::Solicitud() {
    emisor = "";
}

Solicitud::Solicitud(string e, Fecha f) {
    emisor = e;
    fecha = f;
}

string Solicitud::getEmisor() const {
    return emisor;
}

Fecha Solicitud::getFecha() const {
    return fecha;
}

int Solicitud::memoriaExtra() const {
    return emisor.size();
}

