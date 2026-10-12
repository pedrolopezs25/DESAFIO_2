#include "Fecha.h"

// ---------- Constructores ----------

Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
    hora = 0;
    minuto = 0;
}

Fecha::Fecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = 0;
    this->minuto = 0;
}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minuto) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = hora;
    this->minuto = minuto;
}

Fecha::Fecha(const Fecha& otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
    hora = otra.hora;
    minuto = otra.minuto;
}

// ---------- Getters ----------

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
int Fecha::getHora() const { return hora; }
int Fecha::getMinuto() const { return minuto; }

// ---------- Setters ----------

void Fecha::setDia(int dia) { this->dia = dia; }
void Fecha::setMes(int mes) { this->mes = mes; }
void Fecha::setAnio(int anio) { this->anio = anio; }
void Fecha::setHora(int hora) { this->hora = hora; }
void Fecha::setMinuto(int minuto) { this->minuto = minuto; }

// ---------- Comparación ----------

// Ejemplo: 12/10/2026 18:26  ->  202610121826
long long Fecha::clave() const {
    return anio * 100000000LL + mes * 1000000LL + dia * 10000LL + hora * 100LL + minuto;
}

bool Fecha::operator<(const Fecha& otra) const {
    return clave() < otra.clave();
}

bool Fecha::operator==(const Fecha& otra) const {
    return clave() == otra.clave();
}

bool Fecha::operator<=(const Fecha& otra) const {
    return clave() <= otra.clave();
}

// ---------- Mostrar en pantalla ----------

// Muestra la fecha con el formato  dd/mm/aaaa hh:mm
std::ostream& operator<<(std::ostream& salida, const Fecha& f) {
    if (f.dia < 10) salida << '0';
    salida << f.dia << '/';
    if (f.mes < 10) salida << '0';
    salida << f.mes << '/' << f.anio << ' ';
    if (f.hora < 10) salida << '0';
    salida << f.hora << ':';
    if (f.minuto < 10) salida << '0';
    salida << f.minuto;
    return salida;
}
