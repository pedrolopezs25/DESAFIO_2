#include "Mensaje.h"

// ===== Constructores =====

Mensaje::Mensaje() {
    emisor = "";
    receptor = "";
    texto = "";
    leido = false;
}

// Un mensaje nuevo siempre empieza sin leer
Mensaje::Mensaje(string e, string r, string t, Fecha f) {
    emisor = e;
    receptor = r;
    texto = t;
    fechaEnvio = f;
    leido = false;
}

// ===== Getters =====

string Mensaje::getEmisor() const {
    return emisor;
}

string Mensaje::getReceptor() const {
    return receptor;
}

string Mensaje::getTexto() const {
    return texto;
}

Fecha Mensaje::getFechaEnvio() const {
    return fechaEnvio;
}

bool Mensaje::estaLeido() const {
    return leido;
}

// ===== Estado =====

void Mensaje::marcarLeido() {
    leido = true;
}

void Mensaje::setLeido(bool l) {
    leido = l;
}

// ===== Rango de fechas =====

bool Mensaje::estaEnRango(Fecha inicio, Fecha fin) const {
    if (inicio <= fechaEnvio && fechaEnvio <= fin) {
        return true;
    }
    return false;
}

// ===== Imprimir =====

// Muestra el mensaje asi:  [12/10/2026 18:26] juanito76: Hola!
ostream& operator<<(ostream& salida, const Mensaje& m) {
    salida << "[" << m.fechaEnvio << "] " << m.emisor << ": " << m.texto;
    return salida;
}

// ===== Memoria =====

// Los mensajes se crean con new, asi que contamos el objeto completo
int Mensaje::memoria() const {
    return sizeof(Mensaje) + emisor.size() + receptor.size() + texto.size();
}

