#ifndef FECHA_H
#define FECHA_H

#include <iostream>

// Representa un momento en el tiempo: día, mes, año, hora y minuto.
// La usan Usuario (nacimiento, inscripción), Foto (captura),
// Mensaje (envío) y Solicitud (envío).
class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

    // Convierte la fecha en un solo número para poder compararla.
    long long clave() const;

public:
    // Constructores (sobrecarga de constructores)
    Fecha();
    Fecha(int dia, int mes, int anio);
    Fecha(int dia, int mes, int anio, int hora, int minuto);
    Fecha(const Fecha& otra);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

    // Setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void setHora(int hora);
    void setMinuto(int minuto);

    // Operadores sobrecargados para comparar fechas
    bool operator<(const Fecha& otra) const;
    bool operator==(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;

    // Función amiga: permite escribir  cout << fecha;
    friend std::ostream& operator<<(std::ostream& salida, const Fecha& f);
};

#endif
