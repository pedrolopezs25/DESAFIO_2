#include "Fecha.h"

// ===== Constructores =====

// Fecha por defecto: 01/01/2000 00:00
Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
    hora = 0;
    minuto = 0;
}

// Fecha sin hora (la hora queda en 00:00)
Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
    hora = 0;
    minuto = 0;
}

// Fecha completa
Fecha::Fecha(int d, int m, int a, int h, int min) {
    dia = d;
    mes = m;
    anio = a;
    hora = h;
    minuto = min;
}

// Constructor de copia: crea una fecha igual a otra
Fecha::Fecha(const Fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
    hora = otra.hora;
    minuto = otra.minuto;
}

// ===== Getters =====

int Fecha::getDia() const {
    return dia;
}

int Fecha::getMes() const {
    return mes;
}

int Fecha::getAnio() const {
    return anio;
}

int Fecha::getHora() const {
    return hora;
}

int Fecha::getMinuto() const {
    return minuto;
}

// ===== Setters =====

void Fecha::setDia(int d) {
    dia = d;
}

void Fecha::setMes(int m) {
    mes = m;
}

void Fecha::setAnio(int a) {
    anio = a;
}

void Fecha::setHora(int h) {
    hora = h;
}

void Fecha::setMinuto(int min) {
    minuto = min;
}

// ===== Operadores =====

// Una fecha es menor si es mas antigua.
// Se compara primero el año; si es igual, el mes; y asi sucesivamente.
bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) {
        return anio < otra.anio;
    }
    if (mes != otra.mes) {
        return mes < otra.mes;
    }
    if (dia != otra.dia) {
        return dia < otra.dia;
    }
    if (hora != otra.hora) {
        return hora < otra.hora;
    }
    return minuto < otra.minuto;
}

// Dos fechas son iguales si todos sus datos son iguales
bool Fecha::operator==(const Fecha& otra) const {
    if (anio == otra.anio && mes == otra.mes && dia == otra.dia &&
        hora == otra.hora && minuto == otra.minuto) {
        return true;
    }
    return false;
}

// Menor o igual: es menor, o es igual
bool Fecha::operator<=(const Fecha& otra) const {
    if (*this < otra || *this == otra) {
        return true;
    }
    return false;
}

// Asignacion: copia los datos de otra fecha en esta
Fecha& Fecha::operator=(const Fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
    hora = otra.hora;
    minuto = otra.minuto;
    return *this;
}

// ===== Imprimir =====

// Muestra la fecha asi: dd/mm/aaaa hh:mm
ostream& operator<<(ostream& salida, const Fecha& f) {
    if (f.dia < 10) {
        salida << "0";
    }
    salida << f.dia << "/";

    if (f.mes < 10) {
        salida << "0";
    }
    salida << f.mes << "/" << f.anio << " ";

    if (f.hora < 10) {
        salida << "0";
    }
    salida << f.hora << ":";

    if (f.minuto < 10) {
        salida << "0";
    }
    salida << f.minuto;

    return salida;
}
